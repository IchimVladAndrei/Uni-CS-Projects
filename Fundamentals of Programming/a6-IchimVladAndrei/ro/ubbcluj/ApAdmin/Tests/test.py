# 3
from ro.ubbcluj.ApAdmin.Domain.functions import add_invoice, remove_ap, remove_type, remove_between, replace
from ro.ubbcluj.ApAdmin.Domain.getset import create_invoice


def test_add_invoice():
    lista = []
    add_invoice(lista, 59, 'gas', 200)
    assert len(lista) == 1
    try:
        add_invoice(lista, 49, 'water', 1250)
    except ValueError:
        assert True


def test_remove_ap():
    lista = [create_invoice(99, 101, 'gas'), create_invoice(89, 139, 'water')]
    ap = 89
    assert remove_ap(lista, ap) == 1
    assert len(lista) == 1


def test_remove_type():
    lista = [create_invoice(99, 101, 'gas'), create_invoice(89, 139, 'water')]
    test = 'gas'
    assert remove_type(lista, test) == 1
    assert len(lista) == 1


def test_remove_between():
    lista = [create_invoice(1, 101, 'gas'), create_invoice(2, 139, 'water'), create_invoice(3, 104, 'electricity')]
    assert remove_between(lista, 2, 3) == 1
    assert len(lista) == 1


def test_replace_bill():
    lista = [create_invoice(10, 156, 'other')]
    assert replace(lista, 10, 'other', '-', 200) == 1
    assert lista[0][1] == 200
