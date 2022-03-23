"""
CS 121
Short Exercises #2
"""

def peep(p, e):
    """
    Determine whether or not peep = pp^e

    Inputs:
      p (int): first digit
      e (int): second digit

    Returns: True if peep = pp^e, False otherwise
    """

    ### EXERCISE 1 -- Replace pass with your code
    peep = p*1000+e*100+e*10+p
    ppe = (p*10 + p)**e
    print(peep)
    print(ppe)
    return peep == ppe

def has_more_helper(lst, target):
  """
  Counts the number of times a target occurs in a list

  Inputs:
    lst: the list being read
    target: the value being searched for

  Returns: Number of times the target value occurs
  """
  num = 0
  for i in lst:
    if i == target:
      num+=1
  return num

def has_more(lst1, lst2, target):
    """
    Determine which list contains more of the target value

    Inputs:
      lst1 (list): first list
      lst2 (list): second list
      target: the target value

    Returns: True if lst1 contains more of target, False otherwise
    """

    ### EXERCISE 2 -- Replace pass with your code
    num1 = has_more_helper(lst1, target)
    num2 = has_more_helper(lst2, target)
    
    if num1 > num2:
      return True
    else:
      return False

def make_star_strings(lst):
    """
    Create a list of star strings

    Input:
      lst (list of nonnegative integers): the list

    Returns: A list of strings of stars (*)
    """
    ### EXERCISE 3 -- Replace pass with your code
    lst_stars = []


    for i in lst:
      stars = ""
      for j in range(i):
        stars += "*"
      lst_stars.append(stars)

    return lst_stars

def replace(lst, replacee, replacer):
    """
    Replace one element in a list with another

    Input:
      lst (list): the list
      replacee: the element to replace
      replacer: the element to replace replacee with

    Returns: None, modifies lst in-place
    """

    ### EXERCISE 4 -- Replace pass with your code
    for i in range(len(lst)):
      if lst[i] == replacee:
        lst[i] = replacer
    print(lst)
    return None

def rows_and_columns_contain(lst, target):
    """
    Determines whether every row and every column of a list
      of lists contains a target value

    lst (list of lists): the list of lists
    target: the target value

    Returns: True if every row and every column of lst contains
      target, False otherwise
    """

    ### EXERCISE 5 -- Replace pass with your code
    col = 0
    for i in lst:
      if not (i.count(target) > 0):
        return False
    for i in range(len(lst[1])):
      for j in range(len(lst)):
        if lst[j][i] == target:
          col+=1
          break
    if col >= len(lst[1]):
      return True

    return False
      
