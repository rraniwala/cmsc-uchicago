import numpy as np
import copy


def compute_matching(x, y):
    """
    Returns a new array which is "true" everywhere x == y and 
    false otherwise. 

    Input:
        x: n-dimensional array
        y: n-dimensional array

    Returns: Boolean-valued n-dimensional array with the same shape as 
             x and y
    """

    return x == y


def compute_matching_indices(x, y):
    """
    Returns a new array consisting of the indices where
    x == y.

    Input: 
        x: 1-dimensional array
        y: 1-dimensional array

    Returns: a sorted array of the indices where x[i] == y[i]

    Note that the returned array must be one-dimensional! 

    """

    lst = []

    for i in range(x.size):
        if x[i] == y[i]:
            lst.append(i)
    return np.array(lst)


def powers(N, p):
    """
    Return the first N powers of p. For example:
    powers(5, 2) --> [1, 2, 4, 8, 16]
    powers(5, 4) --> [1, 4, 16, 64, 256]

    Input:
       N: number of powers to return 
       p: base that we are raising to the given powers
    
    Returns: an array consisting of powers of p
    """

    base_array = np.ones(N) * p

    power_array = np.arange(0, N, 1)

    return base_array ** power_array


def clip_values(x, min_val=None, max_val=None):
    """
    Return a new array with the values clipped. 

    If min_val is set, all values < min_val will be set to min_val
    If max_val is set, all values > max_val will be set to max_val

    Remember to return a new array, NOT to modify the input array. 

    Inputs: 
        x: the n-dimensional array to be clipped
        min_val : the minimum value in the returned array (if not None)
        max_val : the maximum value in the returned array (if not None)

    returns: an array with the same dimensions of X with values clipped
             to (min_val, max-val)

    """

    new_array = copy.deepcopy(x)

    if min_val != None:
        new_array[(new_array < min_val)] = min_val
    
    if max_val != None:
        new_array[(new_array > max_val)] = max_val

    return new_array


def find_closest_value(x):
    """
    Returns the index and corresponding value in the one-dimensional 
    array x that is closest to the mean 

    Examples:
    find_closest_value(np.array([1.0, 2.0, 3.0])) -> (1, 2.0)
    find_closest_value(np.array([5.0, 1.0, 8.0])) -> (0, 5.0)

    Inputs: 
        x: 1-dimensional array of values

    Returns: the index and the scalar value in x that is 
        closest to the mean

    """

    x2 = x - x.mean()

    least_distance = x[0]

    return_tuple = (0, least_distance)

    for i in range(x2.size):
        if abs(x2[i]) < least_distance:
            least_distance = abs(x2[i])
            return_tuple = (i, x[i])

    return return_tuple


def select_row_col(x, row_idx=None, col_idx=None):
    """
    Select a subset of rows or columns in the two-dimensional array x. 

    Inputs:
        x: input two-dimensional array 
        row_idx: a list of row index we are selecting, None if not specified
        col_idx: a list of column index we are selecting, None if not specified

    Returns: a two-dimensional array where we have selected based on the 
        specified row_idx and col_idx
    """

    if row_idx == None:
        if col_idx == None:
            return x
        else:
            return x[:, col_idx]
    elif col_idx == None:
        return x[row_idx, :]
    else:
        x2 = x[:, col_idx]
        return x2[row_idx, :]




