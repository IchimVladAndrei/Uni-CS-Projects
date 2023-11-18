class Client:
    def __init__(self, client_id, name):
        self.__client_id = client_id
        self.__name = name

    @property
    def client_id(self):
        return self.__client_id

    @property
    def name(self):
        return self.__name

    @client_id.setter
    def client_id(self, x):
        self.__client_id = x

    @name.setter
    def name(self, x):
        self.__name = x

    def __eq__(self, other):
        return self.client_id == other.client_id

    def __str__(self):
        return f"Client ID {str(self.__client_id)} " \
               f"Name {str(self.__name)}"

    def same(self, x):
        return self.client_id == x.client_id \
               and self.name == x.name

    def partial(self, x):
        return x.client_id.lower() in str(self.client_id).lower() \
               or x.name.lower() in str(self.name).lower()

    def replace(self, x):
        if x.name != "":
            self.name = x.name

    @staticmethod
    def read_client(row):
        arg = row.split(",")
        return Client(int(arg[0].strip()), arg[1].strip())

    @staticmethod
    def write_client(x):
        return f"{str(x.client_id)},{x.name}"
