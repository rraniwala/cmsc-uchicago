def add_list (lst):
    """
    Adds up all the numbers in a list.

    Inputs:
      lst (list of integers): A list of numbers

    Returns: (int) the sum of all the numbers in lst
    """

    total = 0
    for l in lst:
        total += l

    return total

def multiply (a, b):
    """
    Calculates a times b using iterative addition

    Inputs:
        a (float): a floating point number
        b (int): an integer

    Returns: (float) the product of a and b
    """

    total = 0
    for i in range(b):
        total += a

    return total
