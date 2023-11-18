from texttable import Texttable
from copy import deepcopy


class Board:
    def __init__(self, xaxis, yaxis):

        if not xaxis.isdigit() or not yaxis.isdigit():
            raise ValueError("Board sizes are natural numbers")
        xaxis = int(xaxis)
        yaxis = int(yaxis)
        if xaxis <= 0 or yaxis <= 0:
            raise ValueError("Board sizes are natural numbers")
        self._xaxis = xaxis
        self._yaxis = yaxis
        self._data = [0] * self._yaxis * self._xaxis
        self._moves = 0
        self._temp = []
        self._nox = 0
        self._noo = 0

    def move(self, x, y, symbol):
        """
        This function executes the player's move.
        This function also protects the program of wrong user input.
        :param x: x-axis
        :param y: y-axis
        :param symbol: what element to place
        :return:
        """
        if symbol not in ['X', '0']:
            raise ValueError("Symbol doesn't exist!")
        if x not in range(self._xaxis) or y not in range(self._yaxis):
            print(x, y)
            raise ValueError("You cannot move outside the table!")
        if self._data[self._yaxis * x + y] != 0:
            raise ValueError("Element cannot be placed!")
        self._temp.append((deepcopy(self._data), deepcopy(self._moves), deepcopy(self._nox), deepcopy(self._noo)))
        if symbol == 'X':
            self._nox += 1
        else:
            self._noo += 1
        d = {'X': 1, '0': -1}
        self._data[self._yaxis * x + y] = d[symbol]
        self._moves += 1
        dx = [-1, -1, -1, 0, 1, 1, 1, 0]
        dy = [-1, 0, 1, 1, 1, 0, -1, -1]
        'blocking neighbors'
        for i in range(8):
            if x + dx[i] in range(self._xaxis) and y + dy[i] in range(self._yaxis) and \
                    self._data[self._yaxis * (x + dx[i]) + y + dy[i]] == 0:
                self._data[self._yaxis * (x + dx[i]) + y + dy[i]] = 2
                self._moves += 1

    def done(self):
        """
        This function checks whether the game has ended.
        :return: true if game is done, false otherwise
        """
        return self._moves == self._xaxis * self._yaxis

    def get(self, x, y):
        """
        This functions gets an element.
        :param x: x-axis
        :param y: y-axis
        :return:
        """
        return self._data[self._yaxis * x + y]

    def empty_neighbor(self, x, y):
        """
        This function searches for all empty slots.

        :param x:x-axis
        :param y:y-axis
        :return:number of empty slots
        """
        dx = [-1, -1, -1, 0, 1, 1, 1, 0]
        dy = [-1,  0,  1, 1, 1, 0,-1,-1]
        nr = 0
        for i in range(8):
            if x + dx[i] in range(self._xaxis) and y + dy[i] in range(self._yaxis) and \
                    self._data[self._yaxis * (x + dx[i]) + y + dy[i]] == 0:
                nr += 1
        return nr

    def evaluate(self):
        """
        This function evaluates the value of the move
        :return:
        """
        if self.done():
            return 999
        if self._xaxis * self._yaxis - self._moves <= 9:
            if self._nox == self._noo:
                return 10 - (self._yaxis * self._xaxis - self._moves)
            else:
                return -10 + (self._yaxis * self._xaxis - self._moves)
        return 998

    def back(self):
        """
        This function does an undo. It is used for the minmax algorithm.
        :return:
        """
        btemp = deepcopy(self._temp.pop())
        self._data.clear()
        self._data.extend(btemp[0])
        self._moves = btemp[1]
        self._nox = btemp[2]
        self._noo = btemp[3]

    @property
    def sizeofX(self):
        return self._xaxis

    @property
    def sizeofY(self):
        return self._yaxis

    def __str__(self):
        """
        Function for print
        :return: Texttable board
        """
        table = Texttable()
        d = {1: 'X', -1: '0', 0: ' ', 2: 'B'}
        for i in range(0, self._xaxis * self._yaxis, self._yaxis):
            row = self._data[i:i + self._yaxis]
            for j in range(self._yaxis):
                row[j] = d[row[j]]
            table.add_row(row)
        return table.draw()
