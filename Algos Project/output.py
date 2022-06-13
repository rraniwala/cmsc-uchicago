from audioop import reverse
import math
import sys

START_LOCATION = [200, 200]

def distance(x, y):
    return math.ceil(math.sqrt((x[0]-y[0])**2+(x[1]-y[1])**2))

def calculate_marginal_backward(x, y, t):
    distance_between = distance(x, y)
    if y[2] > t - (distance_between + y[5]):
        return -1
    elif y[3] < t - (distance_between+y[5]):
        total_time = t - y[3]
        if y[3] - distance(y, START_LOCATION) < 0:
            return -1
        else:
            if total_time == 0:
                return float('inf')
            return y[4] / total_time
    else:
        total_time = distance_between + y[5]
        if (t - (total_time + distance(y, START_LOCATION)) < 0):
            return -1
        else:
            if total_time == 0:
                return float('inf')
            return y[4] / total_time

def calculate_marginal(x, y, t):
    distance_between = distance(x, y)
    if (y[3] < t + distance_between):
        return -1
    elif (y[2] > t + distance_between):
        total_time = y[2]-t + y[5]
        if (total_time + t + distance(y, START_LOCATION) > 1440):
            return -1
        else:
            if total_time == 0:
                return float('inf')
            return (y[4]) / total_time
    else:
        total_time = distance_between + y[5]
        if (total_time + t + distance(y, START_LOCATION) > 1440):
            return -1
        else:
            if total_time == 0:
                return float('inf')
            return (y[4]) / total_time

def check_max_utility(x, y, t):
    distance_between = distance(x, y)
    if (y[3] < t + distance_between):
        return -1
    elif (y[2] > t + distance_between):
        total_time = y[2]-t + y[5]
        if (total_time + t + distance(y, START_LOCATION) > 1440):
            return -1
        else:
            if total_time == 0:
                return float('inf')
            return y[4]
    else:
        total_time = distance_between + y[5]
        if (total_time + t + distance(y, START_LOCATION) > 1440):
            return -1
        else:
            if total_time == 0:
                return float('inf')
            return y[4]

def calculate_time(x, y, t):
    distance_between = distance(x, y)
    if (y[3] < t + distance_between):
        return float('inf')
    elif (y[2] > t + distance_between):
        total_time = y[2]-t + y[5]
        if (total_time + t + distance(y, START_LOCATION) > 1440):
            return float('inf')
        else:
            return total_time
    else:
        total_time = distance_between + y[5]
        if (total_time + t + distance(y, START_LOCATION) > 1440):
            return float('inf')
        else:
            return total_time

def calculate_time_backward(x, y, t):
    distance_between = distance(x, y)
    if y[2] > t - (distance_between + y[5]):
        return float('inf')
    elif y[3] < t - (distance_between+y[5]):
        total_time = t - y[3]
        if y[3] - distance(y, START_LOCATION) < 0:
            return float('inf')
        else:
            return total_time
    else:
        total_time = distance_between + y[5]
        if (t - (total_time + distance(y, START_LOCATION)) < 0):
            return float('inf')
        else:
            return total_time
    
def solveMU(N, attractions):
    t = 0
    visited = []
    total_utility = 0
    current = START_LOCATION
    current_index = set()
    while t < 1440:
        max_MU = -1
        max_index = 0
        for i in range(N):
            # print(calculate_marginal(current, attractions[i], t), i+1)
            if (i in current_index):
                continue
            if (calculate_marginal(current, attractions[i], t) > max_MU):
                max_MU = calculate_marginal(current, attractions[i], t)
                max_index = i
        if max_MU == -1:
            break
        current_index.add(max_index)
        t += distance(current, attractions[max_index]) 
        if t < attractions[max_index][2]:
            t = attractions[max_index][2]
        t += attractions[max_index][5]
        current = attractions[max_index]
        visited.append(max_index+1)
        total_utility += current[4]
        # print("\n")
    return total_utility, len(visited), visited

def solveMUbackward(N, attractions):
    t = 1440
    visited = []
    total_utility = 0
    current = START_LOCATION
    current_index = set()
    while t > 0:
        max_MU = -1
        max_index = 0
        for i in range(N):
            # print(calculate_marginal_backward(current, attractions[i], t), i+1)
            if (i in current_index):
                continue
            if (calculate_marginal_backward(current, attractions[i], t) > max_MU):
                max_MU = calculate_marginal_backward(current, attractions[i], t)
                max_index = i
        if max_MU == -1:
            break
        current_index.add(max_index)
        t -= (distance(current, attractions[max_index]) + attractions[max_index][5]) 
        if t > attractions[max_index][3]:
            t = attractions[max_index][3]
        current = attractions[max_index]
        visited.append(max_index+1)
        total_utility += current[4]
        # print("\n")
    visited.reverse()
    return total_utility, len(visited), visited

def solvetime(N, attractions):
    t = 0
    visited = []
    total_utility = 0
    current = START_LOCATION
    current_index = set()
    while t < 1440:
        max_MU = float('inf')
        max_index = 0
        for i in range(N):
            if (i in current_index):
                continue
            if (calculate_time(current, attractions[i], t) < max_MU):
                max_MU = calculate_time(current, attractions[i], t)
                max_index = i
        if max_MU == float('inf'):
            break
        current_index.add(max_index)
        t += distance(current, attractions[max_index]) 
        if t < attractions[max_index][2]:
            t = attractions[max_index][2]
        t += attractions[max_index][5]
        current = attractions[max_index]
        visited.append(max_index+1)
        total_utility += current[4]
    return total_utility, len(visited), visited    

def solvetimebackward(N, attractions):
    t = 1440
    visited = []
    total_utility = 0
    current = START_LOCATION
    current_index = set()
    while t > 0:
        max_MU = float('inf')
        max_index = 0
        for i in range(N):
            if (i in current_index):
                continue
            if (calculate_time_backward(current, attractions[i], t) < max_MU):
                max_MU = calculate_time_backward(current, attractions[i], t)
                max_index = i
        if max_MU == float('inf'):
            break
        current_index.add(max_index)
        t -= (distance(current, attractions[max_index]) + attractions[max_index][5]) 
        if t > attractions[max_index][3]:
            t = attractions[max_index][3]
        current = attractions[max_index]
        visited.append(max_index+1)
        total_utility += current[4]
    visited.reverse()
    return total_utility, len(visited), visited

def solvetotal(N, attractions):
    t = 0
    visited = []
    total_utility = 0
    current = START_LOCATION
    current_index = set()
    while t < 1440:
        max_MU = -1
        max_index = 0
        for i in range(N):
            distance_between = distance(current,attractions[i])
            if (i in current_index):
                continue
            if check_max_utility(current, attractions[i], t) > max_MU:
                max_MU = attractions[i][4]
                max_index = i
        if max_MU == -1:
            break
        current_index.add(max_index)
        t += distance(current, attractions[max_index]) 
        if t < attractions[max_index][2]:
            t = attractions[max_index][2]
        t += attractions[max_index][5]
        current = attractions[max_index]
        visited.append(max_index+1)
        total_utility += current[4]
    
    return total_utility, len(visited), visited

def isSubsetSum(set, n, sum):
     
    # The value of subset[i][j] will be
    # true if there is a
    # subset of set[0..j-1] with sum equal to i
    subset =([[False for i in range(sum + 1)]
            for i in range(n + 1)])
     
    # If sum is 0, then answer is true
    for i in range(n + 1):
        subset[i][0] = True
         
    # If sum is not 0 and set is empty,
    # then answer is false
    for i in range(1, sum + 1):
         subset[0][i]= False
             
    # Fill the subset table in bottom up manner
    for i in range(1, n + 1):
        for j in range(1, sum + 1):
            if j<set[i-1]:
                subset[i][j] = subset[i-1][j]
            if j>= set[i-1]:
                subset[i][j] = (subset[i-1][j] or
                                subset[i - 1][j-set[i-1]])
     
    # uncomment this code to print table
    # for i in range(n + 1):
    # for j in range(sum + 1):
    # print (subset[i][j], end =" ")
    # print()
    return subset[n][sum]  

def sortinputs(attractions):
    list = [[[1] for _ in range(40)] for _ in range(40)]
    print(list)
    for i in attractions:
        x = attractions[0] % 40
        y = attractions[1] % 40
        list[x][y].append(attractions[i])


def read_input(f):
    file = open(f, 'r')
    N = int(file.readline())
    attractions = [[int(i) for i in file.readline().split()] for _ in range(N)]
    return N, attractions

def main(f):
    print(isSubsetSum())
    N, attractions = read_input(f)
    best = max(solveMU(N, attractions), solveMUbackward(N, attractions), solvetotal(N, attractions), solvetime(N, attractions), solvetimebackward(N, attractions))
    return best

if __name__ == '__main__':
    main()