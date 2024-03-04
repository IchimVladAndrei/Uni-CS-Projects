#pragma once
#include <stdio.h>
#include "service.h"


typedef struct {
	Service service;
}Console;

///This function creates a console
Console* create_console(Service service);

//This function deletes the created console
void destroy_ui(Console* console);
void add_offer_ui(Console* console);
void delete_offer_ui(Console* console);
void update_offer_ui(Console* console);
void display_search_ui(Console* console);
void display_certain(Console* console);
void undo_ui(Console* console);
void redo_ui(Console* console);

//This function prints the menu
void menu();

//This function starts the program
void solve(Console* console);