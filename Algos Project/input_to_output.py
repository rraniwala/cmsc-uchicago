import os
import sys
import zipfile
import output

os.chdir('/Users/rraniwala/Downloads')

for f in os.listdir(sys.argv[1]):
    filepath = 'all_inputs/' + f
    print(filepath)
    inputfile = open(filepath, 'r')
    outputfilename = f[:-3]
    outputfilename = outputfilename + '.out'
    best = output.main(filepath)
    original = sys.stdout 
    with open(outputfilename, 'w') as outputfile:
        sys.stdout = outputfile
        print(best[1])
        for i in best[2]:
            print(str(i), end = " ")
        sys.stdout = original