#pragma once
#include <cstdlib>
#include "service.h"
#include "validator.h"
#include "exceptions.h"
#include "watchlist.h"
#include "watchlistCSV.h"
#include "watchlistHTML.h"
class Console {
private:
	Service& service;
	Watchlist* watchlist;
public:
	Console(Service& service);
	Console(Service& service);
	void admin_print();
	void menu_wishlist();
	void solve();
	void menu_user_mode();
	int wishlist();
	void see_wishlist();
	void user_mode();
	void admin_mode();
	void add_admin_ui();
	void remove_admin_ui();
	void print_help();
	void update_admin_ui();
	void print_wishlist();

};