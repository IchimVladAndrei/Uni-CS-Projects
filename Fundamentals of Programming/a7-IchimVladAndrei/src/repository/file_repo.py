from src.domain.entities import Book
from src.repository.repo import Repository


class FileRepository(Repository):
    def __init__(self,file,validator):
        super().__init__(validator)
        self._file=file
        self._load_file()

    def add(self,book):
        """
        This method is a child of the superclass Repository

        :param book: book object
        :return:
        """
        super().add(book)
        n_list=self.entities[:]
        self._save(n_list)

    def update_all(self, n_list):
        super().update_all(n_list)
        self._save(n_list)

    def _save(self,list):
        with open(self._file,"w") as f:
            for b in list:
                f.write(f"{str(b)} \n")

    def _load_file(self):
        # t text file mode r for reading
        lines = []
        try:
            fin = open(self._file, "rt")
            lines = fin.readlines()
            fin.close()
        except IOError:
            pass  # it's ok if we dont find file
        for line in lines:
            current = line.split()
            new_book = Book(current[-1].strip(), current[4].strip(), current[1].strip())
            super().add(new_book)

