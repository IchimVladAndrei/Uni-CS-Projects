from src.repository.repo import GenericRepo


class TextRepo(GenericRepo):
    def __init__(self, file, readit, write):

        self.__file = file
        self.__readit = readit
        self.__write = write
        GenericRepo.__init__(self)

    def __load_file(self):
        self._temp = []
        with open(self.__file, "r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    _obj = self.__readit(line)
                    self._temp.append(_obj)
        f.close()

    def __save_file(self):
        with open(self.__file, "w") as f:
            for _obj in self._temp:
                line = self.__write(_obj)
                f.write(line+"\n")
        f.close()

    def add(self,x):
        self.__load_file()
        GenericRepo.add(self,x)
        self.__save_file()

    def update(self,x,new_x):
        self.__load_file()
        GenericRepo.update(self,x,new_x)
        self.__save_file()

    def remove(self,x):
        GenericRepo.remove(self,x)
        self.__save_file()

    def get_all(self):
        self.__load_file()
        return GenericRepo.get_all(self)

    def size(self):
        self.__load_file()
        return GenericRepo.size()

    def search(self,find):
        self.__load_file()
        return GenericRepo.search(self,find)

    def search_all(self, find):
        self.__load_file()
        return GenericRepo.search_all(self,find)