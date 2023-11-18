from src.domain.movie import Movie


class MoviesService(object):
    def __init__(self, r_movies, v_movie, r_rentals):
        self.r_movies = r_movies
        self.v_movie = v_movie
        self.r_rentals = r_rentals

    def get_no(self):
        return self.r_movies.size()

    def get_movies(self):
        return self.r_movies.get_all()

    def add_movie(self, movie_id, title, description, genre):
        """
        This function appends to the repository a new object of type movie, with the properties
        given by the user, by firstly validating it.

        :param movie_id: integer
        :param title: string
        :param description: string
        :param genre: string
        :return: new repo list with the appended object
        """
        m = Movie(movie_id, title, description, genre)
        self.v_movie.validate_movie(m)
        self.r_movies.add(m)

    def update_movie(self, movie_id, title, description, genre):
        """
        This function updates the fields of a movie of a given movie ID.
        :param movie_id: integer
        :param title: string
        :param description: string
        :param genre: string
        :return: new repo list with the updated object
        """
        m = self.r_movies.search(Movie(movie_id, "", "", ""))
        updated_movie = Movie(movie_id, title, description, genre)
        self.r_movies.update(m, updated_movie)

    def remove_movies(self, movie_id):
        """
        This function removes from the list a certain object having user given movie ID.
        :param movie_id: integer
        :return: new repo list with the removed object
        """

        rentals = self.r_rentals.get_all()
        for rental in reversed(rentals):
            if rental.movie_id == movie_id:
                self.r_rentals.remove(rental)

        movie = self.r_movies.search(Movie(movie_id, '', '', ''))
        self.r_movies.remove(movie)

    def search_movie(self, find):
        find_movie = Movie(find, find, find, find)
        searched_movie = self.r_movies.search_all(find_movie)
        return searched_movie
