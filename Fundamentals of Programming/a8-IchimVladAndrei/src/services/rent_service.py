import datetime
import random

from src.domain.client import Client
from src.domain.exceptions import TimeError, RentError, DateError
from src.domain.movie import Movie
from src.domain.rental import Date, Rental


class MovieRentDays:
    def __init__(self, movie, days_rented):
        self.movie = movie
        self.days_rented = days_rented

    def get_days(self):
        return self.days_rented

    # getter>??
    def __str__(self):
        return f"{str(self.movie)}+\n Rented for: {str(self.days_rented)}"


class ClientRentDays:
    def __init__(self, client, days_rented):
        self.client = client
        self.days_rented = days_rented

    def get_days(self):
        return self.days_rented

    # getter????
    def __str__(self):
        return f"{str(self.client)}\n has {str(self.days_rented)} movie rental days"


class LateRentals:
    def __init__(self, movie_id, name, dues):
        self.movie_id = movie_id
        self.name = name
        self.dues = dues

    def get_dues(self):
        return self.dues

    def __str__(self):
        return f"{str(self.movie_id)}:{self.name}\n Late for {str(self.dues)} days"


class RentalService(object):
    def __init__(self, r_movies, r_clients, r_rentals, v_rental):
        self.r_movies = r_movies
        self.r_clients = r_clients
        self.r_rentals = r_rentals
        self.v_rental = v_rental

    def get_no(self):
        return self.r_rentals.size()

    def get_rentals(self):
        return self.r_rentals.get_all()

    def get_date(self, row):
        d = row.split('/')
        if len(d) != 3:
            raise DateError("Date is not valid")
        return Date(int(d[0]), int(d[1]), int(d[2]))

    def rent_movie(self, rental_id, movie_id, client_id, rent_date, due_date):
        m = self.r_movies.search(Movie(movie_id, '', '', ''))
        c = self.r_clients.search(Client(client_id, ''))
        rent_date = self.get_date(rent_date)
        due_date = self.get_date(due_date)
        returned_date = Date(0, 0, 0)
        if due_date <= rent_date:
            raise TimeError("Please obey the laws of physics")

        r = Rental(rental_id, m.movie_id, c.client_id, rent_date, due_date, returned_date)
        temp = self.get_rentals()
        self.v_rental.validate_rental(r, temp)
        self.r_rentals.add(r)

    def return_movie(self, rental_id, return_date):
        return_date = self.get_date(return_date)
        r = self.r_rentals.search(Rental(rental_id, '', '', '', '', ''))
        if r.returned_date != Date(0, 0, 0):
            raise RentError("Movie was returned")
        if return_date <= r.returned_date:
            raise TimeError("Please obey the law of physics")
        self.r_rentals.update(r, Rental(rental_id, '', '', '', '', return_date))

    def most_rented(self):
        temp = {}
        rentals = self.get_rentals()
        for r in rentals:
            movie_id = r.movie_id
            if movie_id not in temp:
                temp[movie_id] = 0
            temp[movie_id] += r.days_rented()  # ce

        result = []
        for i in temp.items():
            movie = self.r_movies.search(Movie(i[0], '', '', ''))
            rented_days = i[1]
            result.append(MovieRentDays(movie, rented_days))
        result.sort(key=lambda x: x.get_days(), reverse=True)
        return result

    def most_active(self):
        temp = {}
        rentals = self.get_rentals()
        for r in rentals:
            client_id = r.client_id
            if client_id not in temp:
                temp[client_id] = 0
            temp[client_id] += r.days_rented()
        result = []
        for i in temp.items():
            client = self.r_clients.search(Client(i[0], ''))
            rentals_days = i[1]
            result.append(ClientRentDays(client, rentals_days))
        result.sort(key=lambda x: x.get_days(), reverse=True)
        return result

    def late_rentals(self):
        current_date = datetime.date.today()
        temp = []
        rentals = self.get_rentals()
        for r in rentals:
            if r.returned_date == Date(0, 0, 0) and r.due_date <= Date(current_date.day,
                                                                       current_date.month,
                                                                       current_date.year):
                movie_id = r.movie_id
                movie = self.r_movies.search(Movie(movie_id, '', '', ''))
                name = movie.title
                delay = r.days_delay()
                temp.append(LateRentals(movie_id, name, delay))
        temp.sort(key=lambda x: x.get_dues(), reverse=True)
        return temp
