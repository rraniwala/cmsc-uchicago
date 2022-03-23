"""
CS 121: Analyzing Election Tweets

YOUR NAME

Basic algorithms module

Algorithms for efficiently counting and sorting distinct 'entities',
or unique values, are widely used in data analysis.
"""

import math
from util import sort_count_pairs

# Task 1.1
def count_tokens(tokens):
    '''
    Counts each distinct token (entity) in a list of tokens.

    Inputs:
        tokens: list of tokens (must be immutable)

    Returns: dictionary that maps tokens to counts
    '''

    token_dict = {}

    for token in tokens:
        if not token in token_dict:
            token_dict[token] = 1
        else:
            token_dict[token] += 1

    return token_dict


# Task 1.2
def find_top_k(tokens, k):
    '''
    Find the k most frequently occuring tokens.

    Inputs:
        tokens: list of tokens (must be immutable)
        k: a non-negative integer

    Returns: list of the top k tokens ordered by count.
    '''

    #Error checking (DO NOT MODIFY)
    if k < 0:
        raise ValueError("In find_top_k, k must be a non-negative integer")

    token_dict = count_tokens(tokens)

    sorted_token_list = sort_count_pairs(token_dict.items())
    final_tokens = []

    for i in range(k):
        if i < len(sorted_token_list):
            final_tokens.append(sorted_token_list[i][0])

    return final_tokens


# Task 1.3
def find_min_count(tokens, min_count):
    '''
    Find the tokens that occur *at least* min_count times.

    Inputs:
        tokens: a list of tokens  (must be immutable)
        min_count: a non-negative integer

    Returns: set of tokens
    '''

    #Error checking (DO NOT MODIFY)
    if min_count < 0:
        raise ValueError("min_count must be a non-negative integer")

    token_dict = count_tokens(tokens)
    token_set = set()

    for key, value in token_dict.items():
        if value >= min_count:
            token_set.add(key)

    return token_set


# Task 1.4
def find_idf(document_collection, term):
    """
    Finds the idf of a term in a document collection

    Inputs:
        document_collection: The collection of documents being examined
        term: The term for whose idf we are calculating

    Returns: The idf of the term in the document collection
    """

    total_documents = 0
    docs_with_term = 0

    for document in document_collection:
        total_documents += 1

        for item in document:
            if item == term:
                docs_with_term += 1
                break

    return math.log(total_documents/docs_with_term)


def find_tf(term, document):
    """
    Finds the tf of a given term in a given document

    Inputs:
        term: The term being examined
        document: The document being examined

    Returns: The tf of the term in the document
    """

    term_dict = count_tokens(document)
    term_count = term_dict[term]
    max_occurences = 0

    for value in term_dict.values():

        if max_occurences < value:
            max_occurences = value

    return 0.5 + 0.5*(term_count/max_occurences)






def find_salient(docs, threshold):
    '''
    Compute the salient words for each document.  A word is salient if
    its tf-idf score is strictly above a given threshold.

    Inputs:
      docs: list of list of tokens
      threshold: float

    Returns: list of sets of salient words
    '''

    salient_list = []
    idf_dict = {}
    for document in docs:
        tf_dict = {}
        salient_set = set()

        for term in document:
            if not term in idf_dict:
                idf_dict[term] = find_idf(docs, term)

            if not term in tf_dict:
                tf_dict[term] = find_tf(term, document)
                if idf_dict[term] * tf_dict[term] > threshold:
                    salient_set.add(term)

        salient_list.append(salient_set)

    return salient_list
