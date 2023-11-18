import unittest

from src.domain.client import Client
from src.domain.exceptions import ValidationError
from src.domain.movie import Movie
from src.domain.valid import ClientValid, MovieValid
from src.repository.repo import GenericRepo
from src.services.client_service import ClientsService
from src.services.movie_service import MoviesService


class TestsMovieClients(unittest.TestCase):
    def SetUp(self):
        unittest.TestCase.setUp(self)

    def test_init_client(self):
        client = Client(99, "Vlad Ichim")
        self.assertEqual(client.client_id, 99)
        self.assertEqual(client.name, "Vlad Ichim")

    def test_setter_client(self):
        self.__valid_client = Client(99, 'TMP')
        self.__valid_client.client_id = 100
        self.assertEqual(self.__valid_client.client_id, 100)
        self.__valid_client.name = "Vlad Ichim"
        self.assertEqual(self.__valid_client.name, "Vlad Ichim")

    def test_validate_client_id(self):
        valid = ClientValid()
        self.__client = Client(-1, 'Vlad')
        with self.assertRaises(ValidationError):
            valid.validate_client(self.__client)

    def test_validate_client_name(self):
        valid = ClientValid()
        self.__client = Client(99, '')
        with self.assertRaises(ValidationError):
            valid.validate_client(self.__client)

    def test_add_client(self):
        self.__r_rentals = GenericRepo()
        self.__v_client = ClientValid()
        self.__r_clients = GenericRepo()
        self.__s_clients = ClientsService(self.__r_clients, self.__v_client, self.__r_rentals)
        self.__s_clients.add_client(99, "Vlad Ichim")
        self.assertEqual(self.__s_clients.get_clients()[self.__s_clients.get_no() - 1], Client(99, 'Vlad Ichim'))

    def test_remove_client(self):
        self.__r_rentals = GenericRepo()
        self.__v_client = ClientValid()
        self.__r_clients = GenericRepo()
        self.__s_clients = ClientsService(self.__r_clients, self.__v_client, self.__r_rentals)
        self.__s_clients.add_client(99, "Vlad Ichim")
        self.__s_clients.remove_client(99)
        self.assertEqual(self.__s_clients.get_no(), 0)

    def test_update_client(self):
        self.__r_rentals = GenericRepo()
        self.__v_client = ClientValid()
        self.__r_clients = GenericRepo()
        self.__s_clients = ClientsService(self.__r_clients, self.__v_client, self.__r_rentals)
        self.__s_clients.add_client(99, "Vlad")
        self.__s_clients.update_client(99, "John")
        self.assertEqual(self.__s_clients.get_clients()[0].name, "John")

    def test_init_movie(self):
        movie = Movie(1, 'Friday', 'Ice Cube relax', 'Comedy')
        self.__valid_movie = movie
        self.assertEqual(movie.movie_id, 1)
        self.assertEqual(movie.title, 'Friday')
        self.assertEqual(movie.description, "Ice Cube relax")
        self.assertEqual(movie.genre, "Comedy")

    def test_setters_movie(self):
        self.__valid_movie = Movie(1, 'Friday', 'Ice Cube relax', 'Comedy')
        self.__valid_movie.title = 'Next Friday'
        self.assertEqual(self.__valid_movie.title, 'Next Friday')
        self.__valid_movie.movie_id = 2
        self.assertEqual(self.__valid_movie.movie_id, 2)
        self.__valid_movie.genre = "Action"
        self.assertEqual(self.__valid_movie.genre, "Action")

    def test_validate_movie_id(self):
        valid = MovieValid()
        self.__movie_iid = Movie(-1, "Scarface", "Money and power", "action")
        with self.assertRaises(ValidationError):
            valid.validate_movie(self.__movie_iid)

    def test_validate_movie_name(self):
        valid = MovieValid()
        self.__movie_nname = Movie(-1, "Scarface", "Money and power", "action")
        with self.assertRaises(ValidationError):
            valid.validate_movie(self.__movie_nname)

    def test_add_movie(self):
        self.__r_rentals = GenericRepo()
        self.__v_movie = MovieValid()
        self.__r_movies = GenericRepo()
        self.__s_movie = MoviesService(self.__r_movies, self.__v_movie, self.__r_movies)
        self.__s_movie.add_movie(1, "Scarface", "Money and power", "action")
        self.assertEqual(self.__s_movie.get_movies()[self.__s_movie.get_no() - 1],
                         Movie(1, "Scarface", "Money and power", "action"))

    def test_update_movie(self):
        self.__r_rentals = GenericRepo()
        self.__v_movie = MovieValid()
        self.__r_movies = GenericRepo()
        self.__s_movie = MoviesService(self.__r_movies, self.__v_movie, self.__r_movies)
        self.__s_movie.add_movie(1, "Scarface", "Money and power", "action")
        self.__s_movie.update_movie(1, "a", 'b', 'c')
        self.assertEqual(self.__s_movie.get_movies()[0].title, 'a')
        self.assertEqual(self.__s_movie.get_movies()[0].description, 'b')
        self.assertEqual(self.__s_movie.get_movies()[0].genre, 'c')

    def test_remove_movie(self):
        self.__r_rentals = GenericRepo()
        self.__v_movie = MovieValid()
        self.__r_movies = GenericRepo()
        self.__s_movie = MoviesService(self.__r_movies, self.__v_movie, self.__r_movies)
        self.__checked_movie=Movie(1, "Scarface", "Money and power", "action")
        self.__r_movies.add(self.__checked_movie)
        self.__r_movies.remove(self.__checked_movie)
        self.assertEqual(self.__s_movie.get_no(), 0)
