import numpy as np

def get_columns(rows):
    """
    Finds the names of all the columns across a list of rows,
    where every row is represented as a dictionary (with each
    key representing a column name).

    Args:
        rows (list of dicts): List of dictionaries representing rows

    Returns: A set of column names
    """

    column_names = set()

    for row in rows:
        for key in row.keys():
            column_names.add(key)

    return column_names


def fill_missing(rows, default_values=None):
    """
    Fills in missing values in a list of rows, where every row is 
    represented as a dictionary (with each key representing a 
    column name). This function modifies the dictionaries
    in-place.

    The default_values parameter, if present, is a dictionary
    that specifies the default value of one or more columns.
    If a column doesn't appear in the dictionary (or if the
    default_values parameter is None), then the default value
    for that column will be None.

    Args:
        rows (list of dicts): List of dictionaries representing rows
        default_values (dict or None): Default values for columns.

    Returns: Nothing (must modify the rows parameter in-place)
    """

    for row in rows:
        for col in get_columns(rows):
            if col not in row.keys():
                if default_values == None or col not in default_values.keys():
                    row[col] = None
                else:
                    row[col] = default_values[col]

class Adventurer:  
    """
    Class for representing an adventurer.
    
    Attributes:
        name: (str) the name of the adventurer
        bag: (Bag) the adventuer's bag
        cash: (int) the amount of cash the adventurer is 
            carrying
    """

    def __init__(self, name, bag, cash):
        self.name = name
        self.bag = bag
        self.cash = cash

class Bag:
    """
    Class for representing an adventurer's bag.
    
    Attributes:
        material: (str) the material the bag is made from
        price: (int) the price of the bag
    
    Methods:
        add_item(item):
            adds an item to the bag
        get_visible_items(): list of Item
            returns the visible items in the bag
        get_total_value(): integer
            computes the total value of the items in the bag
    """
    
    def __init__(self, material, price):
        self.material = material
        self.price = price
        self.__items = []
    
    def add_item(self, item):
        """
        Adds an item to the bag.
        
        Input:
            item: an Item object
        
        Returns: nothing
        """

        self.__items.append(item)

    def get_visible_items(self):
        """
        Returns the sublist of items that are visible.

        Inputs: none

        Returns: list of Item objects
        """

        return [item for item in self.__items if item.is_visible]

    def get_total_value(self):
        """
        Computes the total value of the bag and its contents,
        including the price of the bag, and the price of all
        items in the bag (even invisible items).

        Inputs: none

        Returns: integer
        """

        return self.price + sum([item.price for item in self.__items])

class Item:
    """
    Class for representing an item an adventurer can own.
    
    Attributes:
        name: (str) the name of the item
        price: (int) the price of the item
        is_visible: (bool) whether the item is visible
    """

    def __init__(self, name, price, is_visible):
        self.name = name
        self.price = price
        self.is_visible = is_visible

def stop_at_customs(adventurers, max_value, banned):
    """
    Given a list of customers, return the sublist of the
    adventurers who are stopped for failing the customs check.
    To pass the customs check, an adventurer must not be
    carrying more than max_value in value (including cash and 
    the value of their bag, counting the price of the bag
    itself and all the items in it, even invisible items), and
    none of the *visible* items in their bag can be in the set
    of banned items.

    Inputs:
        adventurers: list of Adventurer objects
        max_value: (int) maximum allowed value of goods
        banned: (set of strings) the names of the banned items
    
    Returns: list of Adventurer objects
    """

    banned_list = []

    for adventurer in adventurers:
        if adventurer.bag.get_total_value()+adventurer.cash > max_value:
            banned_list.append(adventurer)
        else:
            for item in adventurer.bag.get_visible_items():
                if item.name in banned:
                    banned_list.append(adventurer)
                    break
    
    return banned_list

def fill_missing(data):
    """
    Replace in the missing data with the mean of its row in place.

    Input:
        data: a 2D NumPy array that has missing data marked with zeros.

    Return: 
        no return value
    """

    for i in range(data.shape[0]):
        for j in range(data.shape[1]):
            if data[i][j] == -1:
                data[i][j] = (sum(data[i, 0:j]) + sum(data[i, j+1:data.shape[1]])) / (data.shape[1] - 1)

def helper_moore_neighborhood(position, R, data):
    """
    Returns the Moore neighborhood of radius R around the position.

    Input:
        position (int, int): a tuple representing the i, j position
        R (int): the radius
        data (numpy array): a 2D numpy array that we are working with

    Output: A tuple of tuples representing the Moore neighborhood coordinates,
        where the first tuple represents the lower and upper i bounds and
        the second represents the lower and upper j bounds
    """

    tuple_x = (max(position[0]-R, 0), min(position[0]+R+1, data.shape[0]))
    tuple_y = (max(position[1]-R, 0), min(position[1]+R+1, data.shape[1]))

    return (tuple_x, tuple_y)

def moore_neighborhood(data, R):
    """
    Generate a new array that has the same shape as the data array, 
    and in which the (i, j)th entry of the new array is the mean of the values 
    in the Moore neighborhood of radius R around (i, j)th entry in 
    the input array.

    Input: 
        data: a 2D NumPy array 
           R: a non-negative integer, the Moore neighborhood of radius R

    Return:
        neighbor_data: a 2D array 
    """

    neighbor_data = np.zeros((data.shape[0], data.shape[1]))

    for i in range(neighbor_data.shape[0]):
        for j in range(neighbor_data.shape[1]):
            tuple_x, tuple_y = helper_moore_neighborhood((i, j), R, data)
            neighbor_data[i][j] = data[tuple_x[0]:tuple_x[1], tuple_y[0]:tuple_y[1]].mean()

    return neighbor_data

        
