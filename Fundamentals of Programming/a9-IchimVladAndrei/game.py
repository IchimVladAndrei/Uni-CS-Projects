from ai import *
from board import Board


class Game:
    def __init__(self, board=None, ai_player=None):
        self._board = board
        self._ai_player = ai_player

    def player_move(self, x, y):
        """
        This function does the player's move on the board.
        :param x: int x-axis coord
        :param y: int y-axis coord
        """
        self._board.move(x, y, 'X')

    def ai_move(self):
        """
        This function does the computer's move on the board.
        """
        move = self._ai_player.next(self._board)
        self._board.move(move[0], move[1], '0')

    def set_board(self, x, y):
        """
        This function return the game board with the given dimensions.
        :param x: int, x-axis
        :param y: int, y-axis
        """
        self._board = Board(x, y)

    def get_board(self):
        """
        This function simply returns the board.

        """
        return self._board

    def set_ai(self, lvl):
        """
        This functions selects the difficulty of the A.I. with the input given
        by the user.
        :param lvl: string
        """
        if lvl == 'Easy':
            self._ai_player = EasyComputer()
        elif lvl == 'Medium':
            self._ai_player = MediumComputer()
        elif lvl == 'Hard':
            self._ai_player = HardComputer()

    def __str__(self):
        return str(self._board)
