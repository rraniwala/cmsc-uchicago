'''
Short Exercises #4
Implement simplified version of battleship board
'''

import random

SIZE = 10

SHIP_SIZES = {
    "Carrier": 5,
    "Battleship": 4,
    "Destroyer": 3,
    "Submarine": 3,
    "Patrol Boat": 2}

class Board:
    '''
    Class for representing the state of the game board

    Attributes
    ----------
    board: (list of lists of strings) the current state of the board
    num_ships: (int) the number of ships that have yet to be sunk

    Methods
    -------
    deploy_fleet(fleet_locations):
        add the ships to the board
    is_game_over(): 
        are there any ships (or parts of ships) left on the board
    play_move(loc):
        update the board to reflect a shot at the specified location (loc), 
        returns Miss, Hit, or the type of ship sunk depending on the
        outcome of the shot
    '''

    def __init__(self):
        '''
        Construct an instance of the Board class
        '''
        self.board = []
        for i in range(SIZE):
            self.board.append([])
            for j in range (SIZE):
                self.board[i].append("Water")
        
        self.num_ships = 0

    
    def deploy_fleet(self, fleet_locations):
        '''
        Add ships to the board.

        Args:
            locations: a dictionary that speficies a starting
              location for ships in the fleet.  The number of
              ships in a fleet can vary.
        '''
        for i in range(len(self.board)):
            for j in range(len(self.board[1])):
                for ship, location in fleet_locations.items():
                    if location == [i, j]:
                        for k in range(SHIP_SIZES[ship]):
                            self.board[i][j+k] = ship
                        self.num_ships += 1

            



    def play_move(self, loc):
        '''
        Play a move in the game
        
        Args:
            loc: (int, int) a location in the board

        Returns: (string) "Miss" if the location contained water, "Hit" if the
            location contained a piece of a ship, but not the last piece in
            the ship.  The ship type if the location contained the last piece
            of a given ship.
        '''

        row, col = loc
        assert 0 <= row < SIZE
        assert 0 <= col < SIZE

        if self.board[loc[0]][loc[1]] == "Water" or self.board[loc[0]][loc[1]] == "Hit":
            return "Miss"

        else:
            ship = self.board[loc[0]][loc[1]]
            self.board[loc[0]][loc[1]] = "Hit"
            ship_gone = True
            for status in self.board[loc[0]]:
                if status == ship:
                    ship_gone = False
            
            if ship_gone:
                self.num_ships -= 1
                return ship
            else:
                return "Hit"


    def is_game_over(self):
        '''Have all the ships been sunk?'''

        if (self.num_ships == 0):
            return True
        else:
            return False


    def __str__(self):
        ''' Generate a string representation of the board'''

        string_list = []
        for i, row in enumerate(self.board):
            current_row = []
            for item in row:
                current_row.append(item[0])
            string_list.append(" ".join(current_row))

        string_list.append("")

        string = "\n".join(string_list)

        return string
        
        
    
class Game:
    '''
    Represent the game

    Attributes
    ----------
    board: (Board) the game board

    Methods
    '''

    def __init__(self, ships):
        self.board = Board()
        self.board.deploy_fleet(ships)
        
    def __convert_input(self, keyboard):
        '''
        Convert the input into a (int, int) tuple
        if possible.  Check in range(0, SIZE).

        Args:
            keyboard: (string) the user's input

        Returns: (int, int) or None
        '''

        split = keyboard.split()
        if len(split) != 2:
            return None
        try:
            r = int(split[0])
            c = int(split[1])
        except:
            return None

        if 0 <= r < SIZE and 0 <= c < SIZE:
            return r, c
        return None

    def __get_input(self):
        '''
        Keep asking for input until user enters: show, concede,
        cheat, or move as a pair of integers.

        Returns (action, location or None)
        '''
        while True:
            keyboard = input("Enter your move: ".format())
            if keyboard.lower() in ("concede", "cheat"):
                return (keyboard.lower(), None)
            result = self.__convert_input(keyboard)
            if result:
                return ("move", result)
            print("Please enter a valid board location or command...")

    def play(self):
        '''
        Play the game.
        '''

        print("Ready to play?")

        num_shots = 0
        while not self.board.is_game_over():
            (action, loc) = self.__get_input()
            if action == "move":
                print(self.board.play_move(loc))
                num_shots = num_shots + 1
            elif action == "concede":
                print("You conceded after {} shots".format(num_shots))
                return
            elif action == "cheat":
                print(self.board)
            else:
                assert False, "should never get here"

        print("You took {} shots to win".format(num_shots))


def generate_random_game():
    '''
    Generate a game randomly:
       Choose how many and which ships to include (zero to five)
       Choose where to place them on the board.

    Returns: (Game) a randomly generated game
    '''

    # Choose how many and which ships to include
    num_ships = random.randint(0, len(SHIP_SIZES))
    ships = list(SHIP_SIZES.keys())
    random.shuffle(ships)
    ships = ships[:num_ships]

    # Choose which rows will hold ships
    row_nums = list(range(SIZE))
    random.shuffle(row_nums)
    rows_to_use = row_nums[:num_ships]

    config = {}
    for i, r in enumerate(rows_to_use):
        ship = ships[i]
        c = random.randint(0, SIZE-SHIP_SIZES[ship])
        config[ship] = (r, c)
        
    return Game(config)

if __name__ == "__main__":
    g = generate_random_game()
    g.play()
    
