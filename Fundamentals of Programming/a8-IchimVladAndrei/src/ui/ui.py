from src.domain.exceptions import RepoError, ValidationError, InputError


class Console(object):
    def __manager(self):
        print("What to manage?")
        print("1. Movies ")
        print("2. Clients ")
        cmd = input("> ")
        if cmd == '1':
            self.__manage_movies()
        elif cmd == '2':
            self.__manage_clients()
        else:
            print("Invalid Command")

    def __add_movie_ui(self):
        movie_id = self.__read_id()
        title = input("Title: ")
        description = input('Description: ')
        genre = input("Genre: ")
        self.__s_movies.add_movie(movie_id, title, description, genre)

    def __remove_movie_ui(self):
        print("Movie will be deleted ")
        movie_id = self.__read_id()
        self.__s_movies.remove_movies(movie_id)

    def __update_movie_ui(self):
        print('Change the title,description and genre of a certain movie')
        # print("enter for skip")
        movie_id = self.__read_id()
        title = input('Title: ')
        description = input('Description: ')
        genre = input('Genre: ')
        self.__s_movies.update_movie(movie_id, title, description, genre)

    def __list_movie_ui(self):
        for m in self.__s_movies.get_movies():
            print(m)
            print("")

    def __add_client_ui(self):
        client_id = self.__read_id()
        name = input("Name: ")
        self.__s_clients.add_client(client_id, name)

    def __remove_client_ui(self):
        client_id = self.__read_id()
        self.__s_clients.remove_client(client_id)

    def __update_client_ui(self):
        client_id = self.__read_id()
        name = input("New name is: ")
        self.__s_clients.update_client(client_id, name)

    def __list_client_ui(self):
        for c in self.__s_clients.get_clients():
            print(c)
            print("")

    def __init__(self, s_movies, s_clients, s_rentals):
        self.__s_movies = s_movies
        self.__s_clients = s_clients
        self.__s_rentals = s_rentals
        self.__cmds = {
            '1': self.__manager,
            '2': self.__rents,
            '3': self.__search,
            '4': self.__stats

        }
        self.__client_cmd = {
            '1': self.__add_client_ui,
            '2': self.__remove_client_ui,
            '3': self.__update_client_ui,
            '4': self.__list_client_ui
        }
        self.__movie_cmd = {
            '1': self.__add_movie_ui,
            '2': self.__remove_movie_ui,
            '3': self.__update_movie_ui,
            '4': self.__list_movie_ui
        }

    def menu(self):
        print("1. Manage clients and movies")
        print("2. Rent or return a movie")
        print("3. Search for clients and movies")
        print("4. Create statistics")
        print("x. Exit")
        print("")

    def solve(self):
        self.menu()
        while True:
            arg = input('> ')
            if arg == 'x':
                break
            elif arg in self.__cmds:
                try:
                    self.__cmds[arg]()
                except InputError as txt:
                    print(' ! Input error: ' + str(txt))
                except RepoError as txt:
                    print(' ! Repository error: ' + str(txt))
                except ValidationError as txt:
                    print(' ! Validity error: ' + str(txt))
            else:
                print("Invalid command !")

    def __manage_movies(self):
        print("1.Add ")
        print("2.Remove")
        print("3.Update")
        print("4.List")
        print("")
        cmd = input("> ")
        if cmd in self.__movie_cmd:
            self.__movie_cmd[cmd]()
        else:
            print("Invalid command")

    def __manage_clients(self):
        print("1.Add ")
        print("2.Remove")
        print("3.Update")
        print("4.List")
        print("")
        cmd = input("> ")
        if cmd in self.__client_cmd:
            self.__client_cmd[cmd]()
        else:
            print("Invalid Command")

    def __rents(self):
        print("Do yo want to rent/return?  ")
        print("write <<no>> to go back ")
        print("write <<list>> to list all rentals ")
        cmd = input("> ")
        if cmd == 'no':
            return
        if cmd == 'list':
            self.__list_rentals_ui()
        elif cmd == "rent":
            self.__rent_ui()
        elif cmd == "return":
            self.__return_ui()
        else:
            print("Invalid command")

    def __search(self):
        print("Searching for ...")
        print("1 for movies, 2 for clients")
        cmd = input("> ")
        if cmd not in ['1', '2']:
            raise InputError("not ok")
        find_by = input("Search by...")
        if cmd == '1':
            movies_list = self.__s_movies.search_movie(find_by)
            self.__print_list(movies_list)
        if cmd == '2':
            clients_list = self.__s_clients.search_client(find_by)
            self.__print_list(clients_list)

    def __stats(self):
        print('Statistics for...')
        print('1. Most rented movies')
        print('2. Most active clients')
        print('3. Late rentals')
        cmd = input(">")
        if cmd == '1':
            self.__print_list(self.__s_rentals.most_rented())
        elif cmd == '2':
            self.__print_list(self.__s_rentals.most_active())
        elif cmd == '3':
            self.__print_list(self.__s_rentals.late_rentals())
        else:
            print("Invalid command")

    def __read_id(self):
        while True:
            number = input("ID is: ")
            try:
                number = int(number)
                return number
            except ValueError:
                print("ID is not ok")

    def __list_rentals_ui(self):
        for r in self.__s_rentals.get_rentals():
            print(r)
            print("")

    def __rent_ui(self):
        try:
            rental_id = int(input("Rental ID:"))
            movie_id = int(input("Movie ID: "))
            client_id = int(input("Client ID"))
        except ValueError:
            raise InputError("ID not ok")
        print("Date is in format day/month/year, please insert date: ")
        rent_date = input("Rented date is: ")
        due_date = input("Due date is: ")
        self.__s_rentals.rent_movie(rental_id, movie_id, client_id, rent_date, due_date)

    def __return_ui(self):
        try:
            rental_id = int(input("Rental ID: "))
        except ValueError:
            raise InputError("ID not ok")
        print("Date is in format day/month/year, please insert date: ")
        returned_date = input("Returned date: ")
        self.__s_rentals.return_movie(rental_id, returned_date)

    def __print_list(self, temp):
        for t in temp:
            print(t)
            print("")
