'''
Linear regression

Rishabh Raniwala

Main file for linear regression and model selection.
'''

import numpy as np
from sklearn.model_selection import train_test_split
import util


class DataSet(object):
    '''
    Class for representing a data set.
    '''

    def __init__(self, dir_path):
        '''
        Class for representing a dataset, performs train/test
        splitting.

        Inputs:
            dir_path: (string) path to the directory that contains the
              file
        '''

        parameters_dict = util.load_json_file(dir_path, "parameters.json")
        self.feature_idx = parameters_dict["feature_idx"]
        self.name = parameters_dict["name"]
        self.target_idx = parameters_dict["target_idx"]
        self.training_fraction = parameters_dict["training_fraction"]
        self.seed = parameters_dict["seed"]
        self.labels, data = util.load_numpy_array(dir_path, "data.csv")

        # do standardization before train_test_split
        if(parameters_dict["standardization"] == "yes"):
            data = self.standardize_features(data)

        self.training_data, self.testing_data = train_test_split(data,
            train_size=self.training_fraction, test_size=None,
            random_state=self.seed)

    # data standardization
    def standardize_features(self, data):
        '''
        Standardize features to have mean 0.0 and standard deviation 1.0.
        Inputs:
          data (2D NumPy array of float/int): data to be standardized
        Returns (2D NumPy array of float/int): standardized data
        '''
        mu = data.mean(axis=0)
        sigma = data.std(axis=0)
        return (data - mu) / sigma

class Model(object):
    '''
    Class for representing a model.
    '''

    def __init__(self, dataset, feature_idx):
        '''
        Construct a data structure to hold the model.
        Inputs:
            dataset: an dataset instance
            feature_idx: a list of the feature indices for the columns (of the
              original data array) used in the model.
        '''

        # REPLACE pass WITH YOUR CODE
        self.feature_idx = feature_idx
        self.target_idx = dataset.target_idx
        self.__data = dataset.training_data[:, self.feature_idx]
        self.__target = dataset.training_data[:, self.target_idx]

        self.data_with_ones = util.prepend_ones_column(self.__data)

        self.beta = util.linear_regression(self.data_with_ones, self.__target)

        self.R2 = helper_R2(self.beta, self.__data, self.__target)


def helper_R2(beta, variable_data, target_data):
    """
    Computes the R2 value given a beta vector, an input matrix, and
    a target vector.

    Inputs:
        beta: a beta vector
        variable_data: input matrix
        target_data: target vector

    Output:
        R2 (float): R2 value given the inputs
    """
    yhat = util.apply_beta(beta, util.prepend_ones_column(variable_data))
    sum_ybar_variance = 0
    sum_yhat_variance = 0
    target_mean = target_data.mean()

    for i in range(len(yhat)):
        sum_yhat_variance += (target_data[i] - yhat[i]) ** 2
        sum_ybar_variance += (target_data[i] - target_mean) ** 2

    return 1 - (sum_yhat_variance / sum_ybar_variance)

def compute_single_var_models(dataset):
    '''
    Computes all the single-variable models for a dataset

    Inputs:
        dataset: (DataSet object) a dataset

    Returns:
        List of Model objects, each representing a single-variable model
    '''

    # Replace [] with the list of models
    return [Model(dataset, [feature_idx]) 
        for feature_idx in dataset.feature_idx]


def compute_all_vars_model(dataset):
    '''
    Computes a model that uses all the feature variables in the dataset

    Inputs:
        dataset: (DataSet object) a dataset

    Returns:
        A Model object that uses all the feature variables
    '''

    # Replace None with a model object
    return Model(dataset, dataset.feature_idx)


def compute_best_pair(dataset):
    '''
    Find the bivariate model with the best R2 value

    Inputs:
        dataset: (DataSet object) a dataset

    Returns:
        A Model object for the best bivariate model
    '''
    R2 = 0

    model = None

    for i in range(len(dataset.feature_idx)):
        for j in range(i+1, len(dataset.feature_idx)):
            current_model = Model(dataset, [i, j])
            if current_model.R2 > R2:
                R2 = current_model.R2
                model = current_model

    return model


def forward_selection(dataset):
    '''
    Given a dataset with P feature variables, uses forward selection to
    select models for every value of K between 1 and P.

    Inputs:
        dataset: (DataSet object) a dataset

    Returns:
        A list (of length P) of Model objects. The first element is the
        model where K=1, the second element is the model where K=2, and so on.
    '''

    model_list = []
    used_indexes = []

    model = Model(dataset, [0])

    for i in range(len(dataset.feature_idx)):
        added_index = 0
        for j in range(len(dataset.feature_idx)):
            if j not in used_indexes:
                current_model = Model(dataset, used_indexes+[j])
                if current_model.R2 > model.R2:
                    added_index = j
                    model = current_model

        used_indexes.append(added_index)
        model_list.append(model)

    return model_list


def validate_model(dataset, model):
    '''
    Given a dataset and a model trained on the training data,
    compute the R2 of applying that model to the testing data.

    Inputs:
        dataset: (DataSet object) a dataset
        model: (Model object) A model that must have been trained
           on the dataset's training data.

    Returns:
        (float) An R2 value
    '''

    return helper_R2(model.beta, dataset.testing_data[:, model.feature_idx],
        dataset.testing_data[:, model.target_idx])
