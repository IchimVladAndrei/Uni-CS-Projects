import datetime


class Rental:
    def __init__(self, rental_id, movie_id, client_id, rented_date, due_date, returned_date):
        self.__rental_id = rental_id
        self.__movie_id = movie_id
        self.__client_id = client_id
        self.__rented_date = rented_date
        self.__due_date = due_date
        self.__returned_date = returned_date

    @property
    def rental_id(self):
        return self.__rental_id

    @property
    def movie_id(self):
        return self.__movie_id

    @property
    def client_id(self):
        return self.__client_id

    @property
    def rented_date(self):
        return self.__rented_date

    @property
    def due_date(self):
        return self.__due_date

    @property
    def returned_date(self):
        return self.__returned_date

    @rental_id.setter
    def rental_id(self, x):
        self.__rental_id = x

    @movie_id.setter
    def movie_id(self, x):
        self.__movie_id = x

    @client_id.setter
    def client_id(self, x):
        self.__client_id = x

    @rented_date.setter
    def rented_date(self, x):
        self.__rented_date = x

    @due_date.setter
    def due_date(self, x):
        self.__due_date = x

    @returned_date.setter
    def returned_date(self, x):
        self.__returned_date = x

    def __eq__(self, other):
        return self.rental_id == other.rental_id

    def __str__(self):
        if self.returned_date.empty() == False:
            return f"Rental Id: {str(self.__rental_id)}\n" \
                   f"Movie ID: {str(self.__movie_id)}\n" \
                   f"Client ID: {str(self.__client_id)}\n" \
                   f"Rented : {str(self.rented_date)}\n" \
                   f"Due date: {str(self.due_date)}\n" \
                   f"Returned: {str(self.returned_date)}\n"
        else:
            return f"Rental Id: {str(self.__rental_id)}\n" \
                   f"Movie ID: {str(self.__movie_id)}\n" \
                   f"Client ID: {str(self.__client_id)}\n" \
                   f"Rented : {str(self.rented_date)}\n" \
                   f"Due date: {str(self.due_date)}\n" \
                   f"Returned: not yet \n "

    def same(self, x):
        return self.rental_id == x.rental_id \
               and self.movie_id == x.movie_id \
               and self.client_id == x.client_id \
               and self.rented_date == x.rented_date \
               and self.due_date == x.due_date \
               and self.returned_date == x.returned_date

    def replace(self, x):
        self.returned_date = x.returned_date

    def days_rented(self):
        temp = self.returned_date
        if temp == Date(0, 0, 0):
            temp = datetime.date.today()
        rented = self.rented_date
        return (datetime.date(temp.year, temp.month, temp.day) - datetime.date(rented.year, rented.month,
                                                                               rented.day)).days + 1

    def days_delay(self):
        due = self.due_date
        temp = datetime.date.today()
        return (temp - datetime.date(due.year, due.month, due.day)).days + 1

    @staticmethod
    def read_rental(row):
        arg = row.split(",")
        d1 = arg[3].split('/')
        Date1 = Date(int(d1[0]), int(d1[1]), int(d1[2]))
        d2 = arg[4].split('/')
        Date2 = Date(int(d2[0]), int(d2[1]), int(d2[2]))
        d3 = arg[5].split('/')
        Date3 = Date(int(d3[0]), int(d3[1]), int(d3[2]))
        return Rental(int(arg[0].strip()), int(arg[1].strip()), int(arg[2].strip()), Date1, Date2, Date3)

    @staticmethod
    def write_rental(rental):
        return f"{str(rental.rental_id)},{str(rental.movie_id)},{str(rental.client_id)},{str(rental.rented_date)},{str(rental.due_date)},{str(rental.returned_date)} "


class Date:
    def __init__(self, day, month, year):
        self.__days = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        self.day = day
        self.month = month
        self.year = year

    def __str__(self):
        return f"{str(self.day)}/{str(self.month)}/{str(self.year)}"

    def empty(self):
        return self.day == 0 and self.month == 0 and self.year == 0

    def __eq__(self, x):
        return self.day == x.day and self.month == x.month and self.year == x.year

    def __le__(self, x):
        return self.year < x.year or (self.year == x.year and self.month < x.month) or (
                self.year == x.year and self.month == x.month and self.day <= x.day)
