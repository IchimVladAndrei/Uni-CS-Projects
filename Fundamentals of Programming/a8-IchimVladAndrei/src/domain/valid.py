from src.domain.exceptions import ValidationError, RentError
from src.domain.rental import Date


class ClientValid(object):
    def __init__(self):
        pass

    def validate_client(self, client):
        """
        This function use is for validation of properties of the object of type client.
        :param client: object
        :return: none if the properties are valid
                raise ValidationError if the name is empty or if client id is negative.
        """
        err = ''

        if client.client_id <= 0:
            err += "Invalid ID \n"
        if client.name == '':
            err += "Invalid Name\n"
        if len(err) > 0:
            raise ValidationError(err)


class MovieValid(object):
    def __init__(self):
        pass

    def validate_movie(self, movie):
        """
                This function use is for validation of properties of the object of type movie.
                :param client: object
                :return: none if the properties are valid
                        raise ValidationError if the movide id is negatie or title is empty
                """
        err = ''
        if movie.movie_id <= 0:
            err += "Invalid Movie ID \n"
        if movie.title == '':
            err += "Invalid title \n"
        if len(err) > 0:
            raise ValidationError(err)


class RentalValid(object):
    def __init__(self):
        pass

    def validate_rental(self, rental, rentals):

        err = ''
        # check if existing movie
        for r in rentals:
            if r.movie_id == rental.movie_id and r.returned_date == Date(0, 0, 0):
                err += "Movie not available yet\n"

        # check if client has past dues

        for r in rentals:
            if r.client_id == rental.client_id and r.returned_date == Date(0, 0, 0) and \
                    r.due_date <= rental.due_date:
                err += "Client has movie past due \n"
                break
        if len(err) > 0:
            raise RentError(err)
