'''
Importing libraries needed for scraping (requests, BeautifulSoup), data entry (pandas), and data writing (os, sys)
'''
import requests
from bs4 import BeautifulSoup
import os
import sys
import pandas as pd

#Set to the directory your input file is located. The output file will be written to the same directory
os.chdir('/Users/rraniwala/Desktop')

#Name of the output file can be changed here
output = "TestResult.csv"

original = sys.stdout

#Reads the input file and copies each line to a list to iterate through
filepath = sys.argv[1]
input = open(filepath, 'r')
copyrights = []
for line in input:
    copyrights.append(line.strip())

new_results = []
count = 0
data_dict = {}

#Iterates through each reference number 
for copyright in copyrights:
    #Checks to see if a given reference number is valid; otherwise continues to the next entry
    if copyright[0:2] != "RE" and copyright[0:2] != "VA" and copyright[0:2] != "TX" and copyright[0:2 != "V2"]:
        continue

    new_results = []

    #Use of a while loop here allows the program to continuously ping the desired search website until it successfully hits
    while len(new_results) < 4:
        '''
        Here, the front page URL is passed through requests to get the HTML document. We then pass the resulting document through a
        BeautifulSoup object in order to make it searchable. We finally take all tags under the first 'form' tag that have an 'input'
        label with a value 'HIDDEN', and proceed to extract PID and SEQ numbers in the subsequent for loop to construct our seaRCH URL
        '''
        URL = "https://cocatalog.loc.gov/cgi-bin/Pwebrecon.cgi?DB=local&PAGE=First"
        page = requests.get(URL)
        search = str(copyright)
        PID = ""
        SEQ = ""
        soup = BeautifulSoup(page.content, "html.parser")
        results = soup.form.find_all('input', type='HIDDEN')
        for result in results:
            if result.attrs['name'] == 'PID':
                PID = result.attrs['value']
            elif result.attrs['name'] == 'SEQ':
                SEQ = result.attrs['value']

        '''
        Here, we construct our search URL using our reference number and the PID/SEQ numbers we obtained earlier. We then print this
        website URL, along with the entry number, to the terminal so we can track our progress. We then ping the website using requests
        to get our desired HTML document and subsequently pass it through a BeautifulSoup object to make it searchable. We check to see 
        if our resulting object is empty and if its form page is empty; if either is the case, our new_results variable stays empty and
        we iterate through the while loop again. Otherwise, we find all 'tr' tags under the first 'form' tag and can proceed
        '''
        new_URL = "https://cocatalog.loc.gov/cgi-bin/Pwebrecon.cgi?Search_Arg=" + search + "&Search_Code=REGS&PID=" + PID + "&SEQ=" + SEQ + "&CNT=25&HIST=1"
        print(count, new_URL)
        new_page = requests.get(new_URL)
        new_soup = BeautifulSoup(new_page.content, "html.parser")
        if new_soup is not None and new_soup.form is not None:
            new_results = new_soup.form.find_all('tr')

    '''
    Here, we construct a new BeautifulSoup object from the fourth entry of new_results, as this entry is an HTML tag containing all of
    the labels and data we wish to extract. From this new object, we search through the first 'tr' tag to find all 'th' and 'td' tags,
    as these are the tags of the labels and objects we wish to extract
    '''
    refined_results = BeautifulSoup(str(new_results[3]), "html.parser")
    data = refined_results.tr.find_all(['th', 'td'])
    prev = ""

    #Iterates through each label and data value obtained from the page
    for d in data:
        #Checks to see if the data entry is empty
        if d.contents != []:
            #Cleans our data and label strings
            if str(d.contents[-1])[0] == '\n':
                d.contents[-1] = d.contents[-1][1:]
            elif str(d.contents[-1])[0] == '<':
                start_ind = str(d.contents[-1]).index('>')
                end_ind = str(d.contents[-1]).index('</')
                d.contents[-1] = str(d.contents[-1])[start_ind+2:end_ind]
            d.contents[-1] = d.contents[-1].lstrip()

            #Checks to see if our data entry is an empty string; if so, skips the entry
            if d.contents[-1] == "":
                continue

            '''
            Checks to see if the entry is a label or a data value. If the entry is a label, we set 'prev' equal to the label and 
            check to see if we have encountered the label before. If not, we add the label to our dictionary and add empty values 
            for all previous entries, as any previous entry would not have had this label. Otherwise, we check to see if we need 
            to add empty values to previous items. We then catch the error case where the program does not encounter a label before 
            a data value, rendering 'prev' as an empty string. In this case, we continue past the data value as it is likely not a
            descriptor of the copyright object. We then assume our entry is a data value and add it to our dictionary to the
            appropriate label, assigned to 'prev' in a previous iteration.
            '''
            if d.contents[-1][-1] == ":":
                prev = d.contents[-1]
                if d.contents[-1] not in data_dict:
                    data_dict[d.contents[-1]] = [[] for i in range(count+1)]
                else:
                    current_length = len(data_dict[d.contents[-1]])
                    while current_length < count + 1:
                        data_dict[d.contents[-1]].append([])
                        current_length += 1
            elif prev not in data_dict:
                continue
            else:
                data_dict[prev][count].append(d.contents[-1])

    #Allows us to keep track of the object we are currently on and manage empty data values
    count += 1

#Appends empty data values to labels that need them
for key in data_dict:
    current_length = len(data_dict[key])
    while len(data_dict[key]) < count:
        data_dict[key].append([])
        current_length += 1

#Puts the data into a pandas DataFrame and then writes the DataFrame to a csv file
clean_data = pd.DataFrame(data_dict)
clean_data.to_csv(output)