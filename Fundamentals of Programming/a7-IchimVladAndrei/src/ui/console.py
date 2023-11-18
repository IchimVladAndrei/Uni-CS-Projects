import random


class Console:
    def __init__(self, s_books):
        self.__s_books = s_books
        self.options = {
            '1': self.__add_ui,
            '2': self.__list_ui,
            '3': self.__remove_ui,
            '4': self.__undo_ui

        }
        self.generate_book()

    def solve(self):
        while True:
            self.__menu()
            cmd = input("> ")
            if cmd == "x":
                break
            if cmd not in self.options.keys():
                print("Not valid")
            else:
                try:
                    self.options[cmd]()
                except ValueError as ve:
                    print("Error is:" + str(ve))

    def __menu(self):
        print("The options are: ")
        print("1. Add book ")
        print("2. Display books ")
        print("3. Remove books starting with a given word ")
        print("4. Undo")
        print("x. Exit")

    def __add_ui(self):
        isbn = input("Book's ISBN is: ")
        author = input("Book's author is: ")
        title = input("Book's title is: ")
        self.__s_books.add_book(isbn, author, title)

    def __list_ui(self):
        for b in self.__s_books.get_books():
            print(b)

    def __remove_ui(self):
        find = input("What book you want to remove?...")
        self.__s_books.remove_word(find)

    def __undo_ui(self):
        self.__s_books.undo()

    def generate_book(self):
        authors = ["Sadoveanu ", "Rebreanu ", "Caragiale ", "Bacovia "]
        titles = ["Luceafarul", "Baltagul ", "Plumb ", "Ion ", "Testament"]
        result = []
        n = 10
        while n > 0:
            isbn = str(random.randint(100_000_000, 999_999_999))
            author = random.choice(authors)
            title = random.choice(titles)
            self.__s_books.add_book(isbn, author, title)
            n -= 1
        return result
