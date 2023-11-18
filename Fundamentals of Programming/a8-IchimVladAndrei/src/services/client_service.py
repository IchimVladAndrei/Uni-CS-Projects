from src.domain.client import Client


class ClientsService(object):
    def __init__(self, r_client, v_client, r_rentals):
        self.r_client = r_client
        self.v_client = v_client
        self.r_rentals = r_rentals

    def get_no(self):
        return self.r_client.size()

    def get_clients(self):
        return self.r_client.get_all()

    def add_client(self, client_id, name):
        """
        This function enables the user to append a new object of type client to the
        repository, by firstly validating its properties.
        :param client_id: integer
        :param name: string
        :return: new list with the appended object
        """
        c = Client(client_id, name)
        self.v_client.validate_client(c)
        self.r_client.add(c)

    def update_client(self, client_id, name):
        """
        This function update the properties for a certain client, with a given client ID.
        :param client_id: integer
        :param name: string
        :return: updated object with new properties
        """
        c = self.r_client.search(Client(client_id, ''))
        updated_c = Client(client_id, name)
        self.r_client.update(c, updated_c)

    def remove_client(self, client_id):
        """
        This function removes from the list a client with a given client ID provided by the
        user.
        :param client_id: integer
        :return: New repo list with the removed object
        """
        rentals = self.r_rentals.get_all()
        for rental in reversed(rentals):
            if rental.client_id == client_id:
                self.r_rentals.remove(rental)

        client = self.r_client.search(Client(client_id, ''))
        self.r_client.remove(client)

    def search_client(self, find):
        find_client = Client(find, find)
        searched_client = self.r_client.search_all(find_client)
        return searched_client
