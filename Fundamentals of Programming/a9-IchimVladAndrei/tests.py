import unittest

from board import Board
from game import Game


class TestGame(unittest.TestCase):
    def test_game(self):
        a=Game()
        a.set_ai('Easy')
        a.set_board('2','2')
        a.ai_move()
        self.assertEqual(a.get_board().done(),True)

    def test_board(self):
        with self.assertRaises(ValueError):
            a=Board('vlad','2')
        a=Board('2','2')
        a.move(1,1,'0')
        self.assertEqual(a.done(),True)
        self.assertEqual(a.get(0,0),2)
        with self.assertRaises(ValueError):
            a.move(2,2,'X')
        with self.assertRaises(ValueError):
            a.move(1,1,'k')
        with self.assertRaises(ValueError):
            a.move(1,1,'X')

    def test_ai(self):
        a=Game()
        a.set_ai('Hard')
        a.set_board('3','3')
        a.ai_move()
        self.assertEqual(a.get_board().done(),True)