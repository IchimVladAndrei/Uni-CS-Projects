import os
import pickle

from src.repository.repo import GenericRepo


class BinaryRepo(GenericRepo):
    def __init__(self, file):
        GenericRepo.__init__(self)
        self._file = file
        self._load_file()

    def _load_file(self):
        f = open(self._file, 'rb')

        if os.path.getsize(self._file) > 0:
            with open(self._file, "rb") as f:
                while True:
                    try:
                        temp = pickle.load(f)
                        GenericRepo.add(self, temp)
                    except EOFError:
                        break

        f.close()

    def _save_file(self):
        f = open(self._file, 'wb')
        for i in GenericRepo.get_all(self):
            pickle.dump(i, f)
        f.close()

    def add(self, x):
        self._temp = []
        self._load_file()
        GenericRepo.add(self, x)
        self._save_file()

    def remove(self, x):
        self._temp = []
        self._load_file()
        GenericRepo.remove(self, x)
        self._save_file()

    def update(self, x, new_x):
        self._temp = []
        self._load_file()
        GenericRepo.update(self, x, new_x)
        self._save_file()
