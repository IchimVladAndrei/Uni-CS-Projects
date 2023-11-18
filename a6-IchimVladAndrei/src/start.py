# 2
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#


from ro.ubbcluj.ApAdmin.Tests.test import test_add_invoice, test_remove_ap, test_remove_type, test_remove_between, \
    test_replace_bill
from ro.ubbcluj.ApAdmin.UI.ui import solve

solve()
test_add_invoice()
test_remove_ap()
test_remove_type()
test_remove_between()
test_replace_bill()
