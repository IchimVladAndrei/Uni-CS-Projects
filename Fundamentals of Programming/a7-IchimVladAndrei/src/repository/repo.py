class Repository(object):
    def __init__(self, validator):
        self.entities = []
        self.__validator = validator

    def get_all(self):
        return self.entities[:]

    def __len__(self):
        return len(self.entities)

    def add(self, x):
        """
        This function appends to the entities list a new Book object. Beforehand it checks if the ISBN is already
        in the list of Book objects.
        :param x: the new book object to be appended
        """
        self.__validator.validate_book(x)
        if x in self.entities:
            raise ValueError("ISBN already exists\n")

        self.entities.append(x)

    def update_all(self, n_list):
        self.entities.clear()
        for b in n_list:
            self.entities.append(b)
