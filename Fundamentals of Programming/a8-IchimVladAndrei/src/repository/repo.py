from src.domain.exceptions import RepoError


class GenericRepo(object):
    def __init__(self):
        self._temp = []

    def size(self):
        return len(self._temp)

    def get_all(self):
        return self._temp[:]

    def add(self, x):
        if x in self._temp:
            raise RepoError("Already in repo \n")
        self._temp.append(x)

    def remove(self, x):
        self._temp.remove(x)

    def update(self, x, new_x):
        for t in self._temp:
            if t == x:
                t.replace(new_x)

    def search(self, find):
        if find not in self._temp:
            raise RepoError("The element doesn't exist \n")
        for t in self._temp:
            if t == find:
                return t

    def search_all(self, find):
        matching = []
        for t in self.get_all():
            if t.partial(find):
                matching.append(t)
        return matching

    def remove(self, x):
        self._temp.remove(x)
