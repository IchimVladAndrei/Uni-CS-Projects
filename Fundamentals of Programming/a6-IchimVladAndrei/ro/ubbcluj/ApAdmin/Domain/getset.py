def get_apartment(invoice):
    return invoice[0]


def get_type(invoice):
    return invoice[2]


def get_amount(invoice):
    return invoice[1]


def set_apartment(invoice, ap):
    invoice[0] = ap


def set_type(invoice, tp):
    invoice[2] = tp


def set_amount(invoice, amount):
    invoice[1] = amount


def create_invoice(apartment, amount, ttype):
    return [apartment, amount, ttype]
# 5
