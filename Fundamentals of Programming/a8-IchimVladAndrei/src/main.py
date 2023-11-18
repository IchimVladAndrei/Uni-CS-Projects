from src.domain.client import Client
from src.domain.movie import Movie
from src.domain.rental import Rental
from src.domain.valid import RentalValid, ClientValid, MovieValid
from src.repository.repo import GenericRepo
from src.repository.repo_binary import BinaryRepo
from src.repository.repo_file import TextRepo
from src.services.client_service import ClientsService
from src.services.movie_service import MoviesService
from src.services.rent_service import RentalService
from src.ui.ui import Console

v_movie = MovieValid()
v_client = ClientValid()
v_rental = RentalValid()

path = "settings_text.properties"

try:
    f = open(path, "r")
    line = f.readline().strip()
    line = line.split(" ")

    if line[2] == 'text':
        line = f.readline().strip()
        line = line.split(" ")
        r_movie = TextRepo(line[2], Movie.read_movie, Movie.write_movie)

        line = f.readline().strip()
        line = line.split(" ")
        r_client = TextRepo(line[2], Client.read_client, Client.write_client)

        line = f.readline().strip()
        line = line.split(" ")
        r_rental = TextRepo(line[2], Rental.read_rental, Rental.write_rental)

        s_movie = MoviesService(r_movie, v_movie, r_rental)
        s_client = ClientsService(r_client, v_client, r_rental)
        s_rentals = RentalService(r_movie, r_client, r_rental, v_rental)


except IOError as error:
    print(str(error))

ui = Console(s_movie, s_client, s_rentals)
ui.solve()
