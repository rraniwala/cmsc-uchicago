"""
Short Exercises #6
"""


from tree import Tree


# Exercise 1
def sum_cubes(n):
    """
    Recursively calculates the sum of the first n positive cubes.

    Input:
        n: positive integer.
    
    Returns: (integer) the value of the sum 1^3 + 2^3 + ... + n^3.
    
    This function may not use any loops or list comprehensions.
    """

    if n == 1:
        return 1

    else:
        return sum_cubes(n-1) + n ** 3


# Exercise 2
def sublists(lst):
    """
    Computes all sublists of the input list.

    Input:
        lst: list of values
    
    Returns: (list of list of values) list of all sublists of lst.
    """
    final = []
    if len(lst) == 0:
        return [[]]

    new_lst = sublists(lst[1:])
    final += new_lst

    for element in new_lst:
        final += [[lst[0]] + element]

    return final
    
# Exercise 3
def min_depth_leaf(tree):
    """
    Computes the minimum depth of a leaf in the tree (length of shortest
    path from the root to a leaf).

    Input:
        tree: a Tree instance.
    
    Returns: (integer) the minimum depth of a leaf in the tree.
    """
    if tree.num_children() == 0:
        return 0

    else:
        tree.print()
        subtree_heights = [min_depth_leaf(child) for child in tree.children]
        return 1 + min(subtree_heights)

    


# Exercise 4
def prune_tree(tree, keys_to_prune):
    '''
    Returns a new tree with that is identical to the original tree, except
    that any node whose key is in keys_to_prune is removed, along with its
    descendants. If the key of the root is in keys_to_prune, then
    YOUR TEXT HERE

    Inputs:
        tree: a Tree instance.
        keys_to_prune: set of keys.
    
    Returns: (Tree) the pruned tree.
    '''
    new_tree = Tree(tree.key, tree.value)
    for child in tree.children:
        if child.key not in keys_to_prune:
            new_tree.add_child(prune_tree(child, keys_to_prune))
            
    return new_tree