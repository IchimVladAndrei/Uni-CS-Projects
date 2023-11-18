import pickle

from src.repository.file_repo import FileRepository


class BinaryRepository(FileRepository):
    def _save_file(self, list):
        fout = open(self._file, "wb")
        pickle.dump(list, fout)
        fout.close()

    def _load_file(self):
        fin = open(self._file, "rb")
        self.entities = pickle.load(fin)

        fin.close()