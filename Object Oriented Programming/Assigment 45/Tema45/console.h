#pragma once
#include <cstdlib>
#include "service.h"
#include "validator.h"

class Console {
private:
	Service* service;
	Validator* validator;
public:
	Console();
	~Console();
	Console(Service* service,Validator* validator);
	void admin_print();
	void solve();
	int wishlist();
	void user_mode();
	void admin();
	void add_admin_ui();
	void remove_admin_ui();
	void print_help();
	void update_admin_ui();
	void print_wishlist();
	
};