#
#
from ro.ubbcluj.ApAdmin.Domain.functions import add_invoice, replace, remove_ap, remove_between, remove_type, \
    filter_value, filter_type, each_cost
from ro.ubbcluj.ApAdmin.Domain.getset import create_invoice, get_apartment, get_type, get_amount


def print_all(invoices_list):
    for i in invoices_list:
        print(
            'Apartment ' + str(get_apartment(i)) + ' has ' + str(get_amount(i)) + ' in ' + str(
                get_type(i)) + ' expenses ')


def print1(all_invoices, ap):
    ap = int(ap)
    for i in all_invoices:
        if get_apartment(i) == ap:
            print('Apartment ' + str(get_apartment(i)) + ' has ' + str(get_amount(i)) + ' in ' + str(
                get_type(i)) + ' expenses ')


def get_cmd():
    line = input("What you want to do? ")
    pos = line.find(' ')
    if pos == -1:
        return line, []
    cmd_name = line[:pos]
    args = line[pos + 1:]
    args = args.split(' ')
    args = [arg.strip() for arg in args]
    return cmd_name, args


def add_transaction_ui(all_invoices: list, history, apartment, ttype, amount):
    cpy = all_invoices[:]
    history.append(cpy)
    possible_types = ["gas", "water", "electricity", "heating", "water", "other"]
    if ttype not in possible_types:
        print("This is not a valid expense.")
    try:
        apartment = int(apartment)
    except ValueError as e:
        print("Apartment must be an integer", e)
    try:
        amount = int(amount)
    except ValueError as e:
        raise ValueError("The amount must be a integer", e)
    add_invoice(all_invoices, apartment, ttype, amount)


def replaces_exp_ui(all_invoices: list, history, *info):
    cpy = all_invoices[:]
    history.append(cpy)
    possible_types = ["gas", "water", "electricity", "heating", "water", "other"]

    if info[1] not in possible_types:
        print("This is  not a valid expense!")
    if info[2] != "with":
        print("This is not a valid command!")
    replace(all_invoices, *info)


def remove_ui(all_invoices: list, history, *info):
    cpy = all_invoices[:]
    history.append(cpy)

    if len(info) > 1 and info[0].isnumeric() and info[2].isnumeric():
        remove_between(all_invoices, info[0], info[2])
    elif info[0].isnumeric():
        remove_ap(all_invoices, info[0])
    else:
        remove_type(all_invoices, info[0])


def print_some(all_invoices, parameters):
    sign = parameters[0]
    value = int(parameters[1])
    all_costs = {}
    each_cost(all_invoices, all_costs)
    possible = ['<', '=', '>']
    if sign not in possible:
        print("not a good sign")
    if sign == '<':
        for i in all_costs:
            if all_costs[i] < value:
                print('Apartment ' + str(i) + ' has to pay ' + str(all_costs[i]) + ' RON')
    if sign == '=':
        for i in all_costs:
            if all_costs[i] == value:
                print('Apartment ' + str(i) + ' has to pay ' + str(all_costs[i]) + ' RON')
    if sign == '>':
        for i in all_costs:
            if all_costs[i] > value:
                print('Apartment ' + str(i) + ' has to pay ' + str(all_costs[i]) + ' RON')


def printing_ui(all_invoices, _, *info):
    if len(info) == 0:
        print_all(all_invoices)
    elif len(info) == 1:
        print1(all_invoices, info[0])
    elif len(info) == 2:
        parameters = [info[0], info[1]]
        print_some(all_invoices, parameters)


def filter_ui(all_invoices, history, *info):
    cpy = all_invoices[:]
    history.append(cpy)
    if info[0].isalpha():
        possible_types = ["gas", "water", "electricity", "heating", "water", "other"]

        if info[0] not in possible_types:
            print("This is  not a valid expense!")
    if info[0].isnumeric():
        filter_value(all_invoices, info[0])
    elif info[0].isalpha():
        filter_type(all_invoices, info[0])


def undo_ui(all_invoices, hist):
    if len(hist) == 0:
        raise ValueError("No more undos")
    all_invoices.clear()
    all_invoices.extend(hist.pop())


def solve():
    temp = [create_invoice(1, 201, 'gas'),
            create_invoice(2, 200, 'water'),
            create_invoice(3, 300, 'gas'),
            create_invoice(4, 400, 'electricity'),
            create_invoice(5, 500, 'heating'),
            create_invoice(6, 600, 'other'),
            ]
    opt = {"add": add_transaction_ui,
           "remove": remove_ui,
           "replace": replaces_exp_ui,
           "list": printing_ui,
           "filter": filter_ui,
           "undo": undo_ui
           }
    history = []
    while True:
        cmd, ars = get_cmd()
        if cmd == 'exit':
            break
        try:

            opt[cmd](temp, history, *ars)

        except KeyError as ke:
            print("Wrong command", ke)

# 1
