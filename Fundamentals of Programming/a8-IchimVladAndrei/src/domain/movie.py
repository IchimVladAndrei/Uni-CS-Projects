class Movie:
    def __init__(self, movie_id, title, description, genre):
        self.__movie_id = movie_id
        self.__title = title
        self.__description = description
        self.__genre = genre

    @property
    def movie_id(self):
        return self.__movie_id

    @property
    def title(self):
        return self.__title

    @property
    def description(self):
        return self.__description

    @property
    def genre(self):
        return self.__genre

    @movie_id.setter
    def movie_id(self, x):
        self.__movie_id = x

    @title.setter
    def title(self, x):
        self.__title = x

    @description.setter
    def description(self, x):
        self.__description = x

    @genre.setter
    def genre(self, x):
        self.__genre = x

    def __eq__(self, other):
        return self.__movie_id == other.__movie_id

    def __str__(self):
        return f"Movie ID {str(self.__movie_id)}," \
               f" Title {str(self.__title)}," \
               f" Description {str(self.__description)}," \
               f" Genre {str(self.__genre)}"

    def same(self, x):
        return self.title == x.title \
               and self.movie_id == x.movie_id \
               and self.description == x.description \
               and self.genre == x.genre

    def replace(self, x):
        if x.title != "":
            self.title = x.title
        if x.description != "":
            self.description = x.description
        if x.genre != "":
            self.genre = x.genre

    def partial(self, x):
        return x.movie_id.lower() in str(self.movie_id).lower() \
               or x.title.lower() in str(self.title).lower() \
               or x.description.lower() in str(self.description).lower() \
               or x.genre.lower() in str(self.genre).lower()

    @staticmethod
    def read_movie(row):
        arg = row.split(",")
        return Movie(int(arg[0].strip()), arg[1].strip(), arg[2].strip(), arg[3].strip())

    @staticmethod
    def write_movie(x):
        return f"{str(x.movie_id)},{x.title},{x.description},{x.genre}"
