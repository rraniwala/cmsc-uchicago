"""
CS 121: Analyzing Election Tweets

YOUR NAME

Analyze module

Functions to analyze tweets.
"""

import unicodedata
import sys

from basic_algorithms import find_top_k, find_min_count, find_salient

##################### DO NOT MODIFY THIS CODE #####################

def keep_chr(ch):
    '''
    Find all characters that are classifed as punctuation in Unicode
    (except #, @, &) and combine them into a single string.
    '''
    return unicodedata.category(ch).startswith('P') and \
        (ch not in ("#", "@", "&"))

PUNCTUATION = " ".join([chr(i) for i in range(sys.maxunicode)
                        if keep_chr(chr(i))])

# When processing tweets, ignore these words
STOP_WORDS = ["a", "an", "the", "this", "that", "of", "for", "or",
              "and", "on", "to", "be", "if", "we", "you", "in", "is",
              "at", "it", "rt", "mt", "with"]

# When processing tweets, words w/ a prefix that appears in this list
# should be ignored.
STOP_PREFIXES = ("@", "#", "http", "&amp")


#####################  MODIFY THIS CODE #####################


############## Part 2 ##############

def make_entity_list(tweets, entity_desc):
    """
    Creates a list of all the entities in a given
    list of tweets that matches the critera of the
    entity description.

    Inputs:
        tweets: a list of tweets
        entity_desc: a triple such as ("hashtags", "text", True),
          ("user_mentions", "screen_name", False), etc.

    Returns: list of entities
    """
    entity_list = []

    for tweet in tweets:
        key =  tweet['entities'][entity_desc[0]]

        for entity in key:
            value = entity[entity_desc[1]]
            if not entity_desc[2]:
                value = value.lower()
            entity_list.append(value)

    return entity_list

# Task 2.1
def find_top_k_entities(tweets, entity_desc, k):
    '''
    Find the k most frequently occuring entitites.

    Inputs:
        tweets: a list of tweets
        entity_desc: a triple such as ("hashtags", "text", True),
          ("user_mentions", "screen_name", False), etc.
        k: integer

    Returns: list of entities
    '''

    return find_top_k(make_entity_list(tweets, entity_desc), k)

# Task 2.2
def find_min_count_entities(tweets, entity_desc, min_count):
    '''
    Find the entitites that occur at least min_count times.

    Inputs:
        tweets: a list of tweets
        entity_desc: a triple such as ("hashtags", "text", True),
          ("user_mentions", "screen_name", False), etc.
        min_count: integer

    Returns: set of entities
    '''

    return find_min_count(make_entity_list(tweets, entity_desc), min_count)



############## Part 3 ##############

# Pre-processing step and representing n-grams

# YOUR HELPER FUNCTIONS HERE
def preprocessing(tweet, case_sensitive, stop_words):
    """
    Preprocess a tweet to turn the tweet into a list of words,
    remove leading and trailing punctuation,
    handle case sensitivity,
    handle stop words,
    and remove URLs, hashtags, and mentions.

    Inputs:
        tweet (string): The text of the tweet that is being preprocessed
        case_sensitive (boolean): Whether or not the task is case-sensitive
        stop_words (boolean): Whether a task requires the elimination of stop words

    Returns: A preprocessed tweet as a list of words
    """

    list_words_raw = tweet.split()
    list_words = []
    for i, word in enumerate(list_words_raw):
        list_words_raw[i] = word.strip(PUNCTUATION)
        if not case_sensitive:
            list_words_raw[i] = list_words_raw[i].lower()
        if not list_words_raw[i] == "":
            if (not stop_words) or (list_words_raw[i] not in STOP_WORDS):
                if not list_words_raw[i].startswith(STOP_PREFIXES):
                    list_words.append(list_words_raw[i])

    return list_words

def find_ngrams(preprocessed_tweet, n):
    """
    Creates a list of ngrams given a preprocessed tweet

    Inputs:
        preprocessed_tweet (list): a list of words
        n (int): the length of the ngrams

    Returns: A list of ngrams of length n from the preprocessed tweet
    """

    list_ngrams = []
    for i in range(len(preprocessed_tweet) -n + 1):
        list_ngrams.append(tuple(preprocessed_tweet[i:i+n]))

    return list_ngrams


def compile_total_ngrams(tweets, n, case_sensitive, stop_words):
    '''
    Compiles a list of all ngrams given a collection of tweets.

    Inputs:
        tweets: a list of tweets
        n: integer
        case_sensitive: boolean
        stop_words: boolean

    Returns: list of n-grams
    '''
    total_ngrams = []
    ngrams_per_tweet = []
    for tweet in tweets:
        processed_tweet = preprocessing(tweet["abridged_text"], case_sensitive, stop_words)
        list_ngrams = find_ngrams(processed_tweet, n)
        ngrams_per_tweet.append(list_ngrams)
        total_ngrams.extend(list_ngrams)

    return (total_ngrams, ngrams_per_tweet)

# Task 3.1
def find_top_k_ngrams(tweets, n, case_sensitive, k):
    '''
    Find k most frequently occurring n-grams.

    Inputs:
        tweets: a list of tweets
        n: integer
        case_sensitive: boolean
        k: integer

    Returns: list of n-grams
    '''
    total_ngrams = compile_total_ngrams(tweets, n, case_sensitive, True)

    return find_top_k(total_ngrams[0], k)


# Task 3.2
def find_min_count_ngrams(tweets, n, case_sensitive, min_count):
    '''
    Find n-grams that occur at least min_count times.

    Inputs:
        tweets: a list of tweets
        n: integer
        case_sensitive: boolean
        min_count: integer

    Returns: set of n-grams
    '''

    total_ngrams = compile_total_ngrams(tweets, n, case_sensitive, True)

    return find_min_count(total_ngrams[0], min_count)


# Task 3.3
def find_salient_ngrams(tweets, n, case_sensitive, threshold):
    '''
    Find the salient n-grams for each tweet.

    Inputs:
        tweets: a list of tweets
        n: integer
        case_sensitive: boolean
        threshold: float

    Returns: list of sets of strings
    '''

    total_ngrams = compile_total_ngrams(tweets, n, case_sensitive, False)
    return find_salient(total_ngrams[1], threshold)
