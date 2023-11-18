from unittest import TestCase

from src.domain.entities import Book, Validate
from src.repository.repo import Repository


class TestServiceBook(TestCase):
    def test_add_book(self):
        self.b1 = Book("565656", "Cenusa", "Matematica")
        self.b2 = Book("1234", "Cuzic", "Muzica")
        self.validator = Validate()
        self.repo = Repository(self.validator)
        self.assertEqual(self.b1.ISBN, "565656", "isbn must be 565656")
        self.assertEqual(self.b2.Author, "Cuzic", "Author must be Cuzic")
        self.repo.add(self.b1)
        self.assertEqual(self.repo.entities[-1], self.b1, "Not working")
