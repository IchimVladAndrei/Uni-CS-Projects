class Book:
    def __init__(self, isbn: str, author: str, title: str):
        self.__isbn = isbn
        self.__author = author
        self.__title = title

    @property
    def ISBN(self):
        return self.__isbn

    @property
    def Author(self):
        return self.__author

    @property
    def Title(self):
        return self.__title

    @ISBN.setter
    def ISBN(self, x):
        self.__isbn = x

    @Author.setter
    def Author(self, x):
        self.__author = x

    @Title.setter
    def Title(self, x):
        self.__title = x

    def __str__(self):
        return 'Book ' + self.Title + ' written by ' + self.Author + ' has ISBN ' + self.ISBN

    @property
    def firstword(self):
        first = self.Title.split(' ')
        return first[0]


class Validate:
    def validate_book(self, book):
        if len(str(book.ISBN)) < 2:
            raise ValueError("ISBN is at least 2 characters")
