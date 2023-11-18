# 4
#
from ro.ubbcluj.ApAdmin.Domain.getset import get_amount, set_amount, create_invoice, get_apartment, get_type


def add_invoice(invoice_list, apartment, ttype, amount):
    """
    This function appends an invoice to a list.
    It is done by using the setters and getters from another python package.
    :param invoice_list: list
    :param apartment: integer
    :param ttype: string
    :param amount: integer
    """
    invoice = create_invoice(apartment, amount, ttype)
    invoice_list.append(invoice)


def remove_ap(invoice_list, ap):
    """
    This function removes the bills associated with a certain flat.
    It is done by searching in a loop a bill with the flat number equal to the searched one.
    :param invoice_list:list
    :param ap: integer
    :return: 1 if it successfully did the loop
    """
    i = 0
    ap = int(ap)
    while i < len(invoice_list):
        if get_apartment(invoice_list[i]) == ap:
            del invoice_list[i]
        i = i + 1
    return 1


def remove_type(invoice_list, ttype):
    """
    This function removes all bills with an associated type of expense.
    It does so by searching in a loop the bills with that certain expense.
    :param invoice_list: list
    :param ttype: string
    :return: 1 if it successfully did the loop
    """
    i = 0
    while i < len(invoice_list):
        if get_type(invoice_list[i]) == ttype:
            del invoice_list[i]
        i = i + 1
    return 1


def remove_between(invoice_list, st, fn):
    """
    This function removes all the bills between two apartments numbers.
    It does so by removing all apartments from [st] to [fn], given by the user.
    :param invoice_list: list
    :param st: integer (first ap)
    :param fn: integer (last ap)
    :return: 1 if it successfully did the loop
    """
    st = int(st)
    fn = int(fn)
    i = 0
    while i < len(invoice_list):
        indx = st
        while indx <= fn:
            if get_apartment(invoice_list[i]) == indx:
                del invoice_list[i]
            indx += 1
        i += 1
    return 1


def replace(invoice_list, a, b, _, d):
    """
    This function replaces a certain expense type amount with a newer one.
    It does so by searching in all bills the certain ap and type.
    :param invoice_list: list
    :param a: integer(number of ap)
    :param b: integer(the type of expense)
    :param _: auxiliary
    :param d: integer (the new amount of the expense)
    :return: 1 if it replaces at least one, 0 if none are replaced
    """
    a = int(a)  # nr ap
    d = int(d)  # new value
    for i in invoice_list:
        if get_apartment(i) == a and get_type(i) == b:  # verifies if it's matching
            set_amount(i, d)
            return 1
    return 0


def each_cost(invoice_bill, total_cost):
    """
    This function sums all expenses an apartment can have.
    It  does so by creating a list with sums. Each index is corresponding with an ap.

    :param invoice_bill: list
    :param total_cost: list (list of sums of apartments)

    """
    for i in invoice_bill:
        total_cost[get_apartment(i)] = 0
    for i in invoice_bill:
        total_cost[get_apartment(i)] = total_cost[get_apartment(i)] + int(get_amount(i))


def filter_type(invoice_bill, ttype):
    """
    This function removes all bills that are not corresponding with user's input.
    It does so by looping through the list of types and removing the ap with the different type.
    :param invoice_bill: list
    :param ttype: string
    :return:
    """
    temp = ['water', 'gas', 'electricity', 'other', 'heating']
    for i in temp:
        if i != ttype:
            remove_type(invoice_bill, i)


def filter_value(invoice_bill, value):
    """
    This function removes all apartments that do not respect a certain value.
    It does so by looping through the list of bills.
    :param invoice_bill: list
    :param value: integer

    """
    value = int(value)
    for i in range(len(invoice_bill) - 1, -1, -1):
        if get_amount(invoice_bill[i]) >= value:
            del invoice_bill[i]
