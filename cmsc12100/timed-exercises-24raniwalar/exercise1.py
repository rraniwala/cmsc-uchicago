def predicted_coins(max_per_side, guesses_to_win, seq):
    """
    Determines whether your friend wins the guessing game.
    Your friend wins if they make at least guess_to_win
    correct predictions by the time the game ends. The game
    ends when there have been max_per_side heads or
    max_per_side tails, even if the end of the sequence seq
    has not been reached. Barring either of those
    conditions, the game also ends at the end of the
    sequence.

    Inputs:
      max_per_side: (int) the game ends when this many
        heads appear or when this many tails appear.
      guesses_to_win: (int) your friend wins if they make
        this many correct guesses by the time the game ends.
      seq: a list of pairs (flip, guess), where flip and
        guess are each either "H" or "T". Here, flip is the
        actual outcome of the coin flip, while guess is what
        your friend guessed. This list may be long.

    Returns: boolean indicating whether your friend wins.
    """
    total_heads = 0
    total_tails = 0
    total_wins = 0
    for flip, guess in seq:
        if flip == "H":
            total_heads += 1
        else:
            total_tails += 1
        if flip == guess:
            total_wins += 1

        if total_heads == max_per_side or total_tails == max_per_side:
            return total_wins >= guesses_to_win

    return total_wins >= guesses_to_win

def gen_class_rosters(students, instructor_assignments):
    """
    Combine student enrollment information and instructor course
    assignments to generate rosters.

    Inputs:
        students: a list of student enrollment dictionaries
        instructor_assignments: a list of (course, name) tuples

    Returns: a dictionary that maps courses to dictionaries that
    contain the instructor's name and a list of student information
    dictionaries.
    """

    course_dict = {}

    for course, name in instructor_assignments:
        course_dict[course] = {'Instructor': name,
                                'Students': []}

    for student in students:
        student_without_courses = {'Name': student['Name'],
                                    'Student ID': student['Student ID'],
                                    'EMail': student['EMail']}
        for course in student['Courses']:
            if course not in course_dict:
                course_dict[course] = {'Instructor': 'Staff',
                                        'Students': []}

            course_dict[course]['Students'].append(student_without_courses)

    return course_dict

def flip(lst):
    """
    Flips a list of list of possibly different lengths

    Input:
      lst (list of lists): the list

    Returns (list of lists): lst flipped
    """

    new_lst = []

    new_row_count = 0

    for row in lst:
        if len(row) > new_row_count:
            new_row_count = len(row)

    for row in lst:
        for i in range(new_row_count):
            if len(new_lst) < new_row_count:
                new_lst.append([])

            if i >= len(row):
                new_lst[i].append(row[-1])
            else:
                new_lst[i].append(row[i])

    return new_lst

def get_unauthorized_accesses(security_log):
    '''
    Given a security log, determines the unauthorized accesses
    made by each employee.

    Inputs:
        security_log (list of tuples): The security log, where
        each element of the list is a (event, employee, room, time)
        tuple, as described in the exercise.

    Returns:
        (dictionary mapping strings to lists) A dictionary where the
        key is an employee identifier, and the value is a list
        of (room, time) tuples representing the unauthorized accesses 
        by that employee.
    '''

    access_dict = {}

    unauthorized = {}

    for event in security_log:
        if event[1] not in access_dict:
            access_dict[event[1]] = {}
            unauthorized[event[1]] = []

        if event[0] != "SWIPE":
            access_dict[event[1]][event[2]] = event[0]

        else:
            if event[2] not in access_dict[event[1]] or \
                access_dict[event[1]][event[2]] != "GRANT":
                unauthorized[event[1]].append((event[2], event[3]))

    return unauthorized
