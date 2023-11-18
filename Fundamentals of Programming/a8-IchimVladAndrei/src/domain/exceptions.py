class ValidationError(Exception):
    def __init__(self, msg):
        Exception.__init__(self, msg)


class RentError(Exception):
    def __init__(self, msg):
        Exception.__init__(self, msg)


class TimeError(Exception):
    def __init__(self, msg):
        Exception.__init__(self, msg)


class DateError(Exception):
    def __init__(self, msg):
        Exception.__init__(self, msg)


class RepoError(Exception):
    def __init__(self, msg):
        Exception.__init__(self, msg)


class InputError(Exception):
    def __init__(self, msg):
        Exception.__init__(self, msg)
