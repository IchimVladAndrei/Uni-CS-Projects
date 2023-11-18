from src.domain.entities import Book


class ServiceBook(object):
    def __init__(self, r_books):
        self.__r_books = r_books
        self.__history = []

    def get_books(self):
        return self.__r_books.get_all()

    def add_book(self, isbn, author, title):
        """
        This function adds a new book to the repository.
        It does so by firstly creating a book object with the given input
        Beforehand it creates a copy of the repository for the undo functionality
        :param isbn: str
        :param author: str
        :param title: str
        """
        self.__history.append(self.__r_books.get_all())
        book = Book(isbn, author, title)
        self.__r_books.add(book)

    def undo(self):
        if len(self.__history) == 0:
            raise ValueError("Nothing undo")
        prev = self.__history[-1][:]
        self.__r_books.update_all(prev)
        self.__history.pop(-1)

    def remove_word(self, x):
        n_list = []
        index = 0
        self.__history.append(self.__r_books.get_all())
        for i in self.__r_books.get_all():
            index += 1
            arg = i.Title.split()
            if arg[0] != x:
                n_list.append(i)
        self.__r_books.update_all(n_list)
