class ObsTracker(object):
    '''                                                                             
    Class for tracking observations collected over the course                       
    of an experiment using a sliding window.                                        
                                                                                    
    Attributes:                                                                     
        name (string): the name of the experiment                                   
        num_obs (int): the number of observations recorded                          
                                                                                    
    Methods:                                                                        
        add_obs(obs): adds an observation (represented as a float)                  
           to the tracker                                                           
        get_over_mean(): returns the mean of all the values                         
           added to the tracker.  Returns None if no values                         
           have been recorded.                                                      
        get_window_range(): returns a tuple with the minimum and                    
           maximum values currently in the sliding window.  Returns                 
           None if no values have been recorded.                                    
    '''

    def __init__(self, name, window_size):
        '''                                                                         
        Initialze the tracker                                                       
                                                                                   
        Args:                                                                       
            name (string): the name of the experiment                               
            window_size (int or None): the size of the sliding
                window. The size of the window will be unbounded if
                the window_size is None.
        '''

        assert (not window_size) or (window_size > 0)
        
        self.name = name
        self.__window_size = window_size
        self.num_obs = 0
        self.__obs_list = []
        self.__total = 0

    def add_obs(self, obs):
        '''
        Add an observation to the tracker

        Args:
            obs (float): an observation
        '''
        if self.__window_size != None and len(self.__obs_list) >= self.__window_size:
            self.__obs_list.pop(0)

        self.__obs_list.append(obs)
        self.num_obs += 1
        self.__total += obs


    def get_overall_mean(self):
        '''
        Returns the mean of ALL the observations that have been
        added to the tracker.

        Returns: float, if at least one observation has been added.  None,
            otherwise.
        '''

        if self.num_obs == 0:
            return None

        return self.__total / self.num_obs

    def get_window_range(self):
        '''
        Returns the minimum and maximum value currently in the sliding
            window.

        Returns: (float, float) with the minimum and maximum value in
            the sliding window, if at least one observation has been added.
            None, otherwise.
        '''
        if self.num_obs == 0:
            return None
        
        return (min(self.__obs_list), max(self.__obs_list))