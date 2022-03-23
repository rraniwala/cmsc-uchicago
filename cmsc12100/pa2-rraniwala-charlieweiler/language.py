"""
CS 121: Language shifts

Rishabh Raniwala, Charlie Weiler

Functions for language shift simulation.

This program takes the following parameters:
    grid _file (string): the name of a file containing a sample region
    R (int): neighborhood radius
    A (float): the language state transition threshold A
    Bs (list of floats): a list of the transition thresholds B to
      use in the simulation
    C (float): the language state transition threshold C
      centers (list of tuples): a list of community centers in the
      region
    max_steps (int): maximum number of steps

Example use:
    $ python3 language.py -grid_file tests/writeup-grid-with-cc.txt
	  --r 2 --a 0.5 --b 0.9 --c 1.2 --max_steps 5
While shown on two lines, the above should be entered as a single command.
"""

"""
EDITS MADE:

  The helper function determine_next_language_step now determines
    whether or not the home location changed language steps (83-141)
    Specifically, a state_changed variable was introduced in line 107
    with its value changing if the language step changes in lines
    115, 122, 127, 134, 137, and 142. Additionally, the return line
    145 now returns a tuple including the boolean representation of
    whether or not a home changed language steps

  The helper function simulate_one_day no longer makes a deepcopy of the
    initial grid to be compared back to. It now utilizes location_changed
    and grid_changed variables (172-173) where location_changed is assigned
    to the boolean value in the return tuple of determine_next_language_step
    as a way to see whether a home has changed language step, and grid_changed
    is set to True if location_changed is ever true for any home (183-186).
    Moreover, simulate_one_day now returns grid_changed as a part of its return
    tuple as a boolean determining whether the grid has changed or not (199).

  In run_simulation, on line 225 I use tuple unpacking rather than assigning
    individual variables as I had before.

  In simulation_sweep, print statements have been removed.


"""

import copy
import click
import utility

def community_center_in_area(home_location, centers):
    """
    Determines whether an SL home is within the service distance of any centers.

    Inputs:
      home_location (tuple of two ints):
        the location of the home in question
      centers (list of tuples): a list of community centers

      Returns: True if a center is within service distance of
        a home and false otherwise (boolean)
    """

    for center in centers:
        if ((abs(home_location[0]-center[0][0])<= center[1]) and
            (abs(home_location[1]-center[0][1])<= center[1])):
            return True

    return False


def engagement_level(grid, home_location, R):
    """
    Determines the engagement level of a home.

    Inputs:
      grid (list of lists of ints):
        The region where the home is located
      home_location (tuple of two ints):
        The location of the home being examined
      R (int): The area of the neighborhood examined

    Returns: The engagement level of a home (int)
    """
    total_engagement = 0
    total_homes = 0

    for i in range(max(home_location[0]-R, 0),
        min(home_location[0]+R+1, len(grid[0]))):
        for j in range(max(home_location[1]-R, 0),
            min(home_location[1]+R+1, len(grid))):
            total_homes += 1
            total_engagement += grid[i][j]

    return total_engagement/total_homes


def determine_next_language_state(grid, A, B, C, home_location, R, centers):
    """
    Determines the next language state of a home

    Inputs:
      grid (list of lists of ints):
        The region in which a home is located
      A (int): Threshold A for engagement
      B (int): Threshold B for engagement
      C (int): Threshold C for engagement
      home_location (tuple of two ints):
        The location of the home being examined
      R (int): Size of the neighborhood
      centers (list of tuples): A list of
        community centers in the area

      Returns: A tuple of the next language state of a given home based
        on the parameters (int) along with whether the language state
        changed (boolean)
    """

    current_state = grid[home_location[0]][home_location[1]]
    final_state = None
    state_changed = False
    engagement = engagement_level(grid, home_location, R)

    if current_state == 0:
        if B<engagement:
            final_state = 1
            state_changed = True
        else:
            final_state = 0

    if current_state == 1:
        if C<engagement:
            final_state = 2
            state_changed = True
        elif B <= engagement:
            final_state = 1
        else:
            final_state = 0
            state_changed = True

    if current_state == 2:
        if B <= engagement:
            final_state = 2
        elif A < engagement:
            final_state = 1
            state_changed = True
        else:
            final_state = 0
            state_changed = True

    if current_state > 0 and current_state > final_state:
        if community_center_in_area(home_location, centers):
            final_state = current_state
            state_changed = False

    return (final_state, state_changed)


def simulate_one_day(grid, R, thresholds, centers):
    """
    Simulates one generation of language preference changes

    Inputs:
      grid (list of lists of ints): the region
      R (int): neighborhood radius
      thresholds (float, float, float): the language
        state transition thresholds (A, B, C)
      centers (list of tuples): a list of community centers
        in the region

    Returns: the frequency of each language state along with
      whether the grid was changed (int, int, int, boolean)
    """

    first_state = 0
    second_state = 0
    third_state = 0
    location_changed = False
    grid_changed = False

    for i in range(len(grid)):
        for j in range(len(grid[0])):
            next_state = determine_next_language_state(grid, thresholds[0],
            thresholds[1],thresholds[2], (i, j), R, centers)

            grid[i][j], location_changed = next_state

            if location_changed:
                grid_changed = True

            if grid[i][j] == 0:
                first_state += 1
            elif grid[i][j] == 1:
                second_state += 1
            else:
                third_state += 1

    return (first_state, second_state, third_state, grid_changed)


def run_simulation(grid, R, thresholds, centers, max_steps):
    """
    Do the simulation.

    Inputs:
      grid (list of lists of ints): the grid
      R (int): neighborhood radius
      thresholds (float, float, float): the language
        state transition thresholds (A, B, C)
      centers (list of tuples): a list of community centers in the
        region
      max_steps (int): maximum number of steps

    Returns: the frequency of each language state (int, int, int)
    """
    first_state = 0
    second_state = 0
    third_state = 0

    for i in range(max_steps):
        generation_values = simulate_one_day(grid, R, thresholds, centers)
        first_state, second_state, third_state, grid_changed = generation_values
        if not grid_changed:
            break

    return (first_state, second_state, third_state)


def simulation_sweep(grid, R, A, Bs, C, centers, max_steps):
    """
    Run the simulation with various values of threshold B.

    Inputs:
      grid (list of lists of ints): the grid
      R (int): neighborhood radius
      A (float): the language state transition threshold A
      Bs (list of floats): a list of the transition thresholds B to
        use in the simulation
      C (float): the language state transition threshold C
      centers (list of tuples): a list of community centers in the
        region
      max_steps (int): maximum number of steps

    Returns: a list of frequencies (tuples) of language states for
      each threshold B.
    """
    simulation_results = []

    for i in Bs:
        new_grid = copy.deepcopy(grid)
        simulation_results.append(run_simulation(new_grid,
            R, (A, i, C), centers, max_steps))

    return simulation_results

@click.command(name="language")
@click.option('--grid_file', type=click.Path(exists=True),
              default="tests/writeup-grid.txt", help="filename of the grid")
@click.option('--r', type=int, default=1, help="neighborhood radius")
@click.option('--a', type=float, default=0.6, help="transition threshold A")
@click.option('--b', type=float, default=0.8, help="transition threshold B")
@click.option('--c', type=float, default=1.6, help="transition threshold C")
@click.option('--max_steps', type=int, default=1,
              help="maximum number of simulation steps")
def cmd(grid_file, r, a, b, c, max_steps):
    '''
    Run the simulation.
    '''

    grid, centers = utility.read_grid(grid_file)
    print_grid = len(grid) < 20

    print("Running the simulation...")

    if print_grid:
        print("Initial region:")
        for row in grid:
            print("   ", row)
        if len(centers) > 0:
            print("With community centers:")
            for center in centers:
                print("   ", center)

    # run the simulation
    frequencies = run_simulation(grid, r, (a, b, c), centers, max_steps)

    if print_grid:
        print("Final region:")
        for row in grid:
            print("   ", row)

    print("Final language state frequencies:", frequencies)

if __name__ == "__main__":
    cmd()
