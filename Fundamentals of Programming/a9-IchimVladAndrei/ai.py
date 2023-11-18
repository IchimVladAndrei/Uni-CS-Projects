import random
from copy import deepcopy


class EasyComputer:

    @staticmethod
    def next(board):
        """
            This functions makes the A.I. to use an easy difficulty, by simply selecting an
            empty slot.
            """
        for i in range(board.sizeofX):
            for j in range(board.sizeofY):
                if board.get(i, j) == 0:
                    return (i, j)


class MediumComputer:

    @staticmethod
    def next(board):
        """
           This function makes the A.I. to use a medium difficulty, by doing a random choice
           from the empty slots.
           """
        temp = []
        for i in range(board.sizeofX):
            for j in range(board.sizeofY):
                if board.get(i, j) == 0:
                    temp.append((i, j))
        return random.choice(temp)


class HardComputer:
    def minmax(self, board, depth, is_max, a, b):
        """
        This function finds the best value of a move, thus providing a hard difficulty
        for the game.
        :param board: board object
        :param depth: depth of the tree
        :param is_max: whether it's the maximum
        :param a: value of max function
        :param b: value of min function
        :return: the move
        """
        e = board.evaluate()
        if e != 998 and e != 999:
            return e
        if b <= a:
            return 0
        if board.done():
            return 0
        if is_max:
            for i in range(board.sizeofX):
                for j in range(board.sizeofY):
                    if board.get(i, j) == 0:
                        board.move(i, j, 'X')
                        a = max(a, self.minmax(board, depth + 1, not is_max, a, b))
                        board.back()
            return a
        else:
            for i in range(board.sizeofX):
                for j in range(board.sizeofY):
                    if board.get(i, j) == 0:
                        board.move(i, j, '0')
                        b = min(b, self.minmax(board, depth + 1, not is_max, a, b))
                        board.back()
            return b

    def next(self, board):
        """
        This function ensures the best next move.
        :param board: object
        :return: tuple, next move
        """
        best_val = -9999
        x = -1
        y = -1
        board = deepcopy(board)
        for i in range(board.sizeofX):
            for j in range(board.sizeofY):
                if board.get(i, j) == 0:
                    board.move(i, j, 'X')
                    move_val = self.minmax(board, 0, False, -1000, 1000)
                    board.back()
                    if move_val > best_val:
                        x = i
                        y = j
                        best_val = move_val
        return (x, y)
