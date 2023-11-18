from game import Game


class UI:
    def __init__(self, game):
        self._game = game

    def start(self):
        self.select_board()
        self.select_diff()
        b = self._game.get_board()
        player_move = True
        while not b.done():
            print(b)
            print("")
            if player_move:
                try:
                    move = self._read_move()
                    self._game.player_move(*move)
                except Exception as e:
                    print(e)
                    continue
            else:
                self._game.ai_move()
            player_move = not player_move
            if b.done():
                if player_move:
                    print("A.I. won")
                else:
                    print("You won!!")
        print(b)

    def select_board(self):
        xaxis=input("Number of rows: ")
        yaxis=input("Number of columns: ")
        self._game.set_board(xaxis,yaxis)

    def select_diff(self):
        print('Levels:')
        print('1. Easy')
        print('2. Medium')
        print('3. Hard')
        lvl = input('Difficulty: ')
        d = {'1': 'Easy',
             '2': 'Medium',
             '3': 'Hard'}
        self._game.set_ai(d[lvl])

    def _read_move(self):
        try:
            cmd=input("Place: ").split(' ')
            return(int(cmd[0]),int(cmd[1]))
        except Exception as e:
            print(e)
            print("Invalid coordinates")
g = Game()
u = UI(g)
u.start()