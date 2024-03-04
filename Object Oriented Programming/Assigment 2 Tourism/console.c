#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"
#include "dynamic.h"
#include "valid.h"
#include "reundo.h"



Console* create_console(Service service) {
	Console* console = (Console*)malloc(sizeof(Console));
	if (console == NULL)
		return NULL;
	console->service = service;
	return console;
}
void destroy_ui(Console* console) {
	if (console == NULL)
		return;
	free(console);

}
void display_test_ui(Console* console) {
	for (int i = 0; i < console->service.repo.array.count; i++)
		printf(" Type: %s Destination: %s Date: %s Price: %d \n", console->service.repo.array.data[i].type, console->service.repo.array.data[i].destination, console->service.repo.array.data[i].date, console->service.repo.array.data[i].price);
}

void display_search_ui(Console* console) {
	char search_dest[100] = " ", debug[3] = "";
	DynamicArray* arr = createDA(100);
	Repos* repohere = createRepos(*arr);
	printf("\n	What name you want to search for?\n");
	//gets_s(debug, sizeof(debug));
	gets_s(search_dest, sizeof(search_dest));

	search_s(&console->service, search_dest, repohere);
	for (int i = 0; i < repohere->array.count; i++)
		printf("Type: %s Destination: %s Date: %s Price: %d \n", repohere->array.data[i].type, repohere->array.data[i].destination, repohere->array.data[i].date, repohere->array.data[i].price);
	
	destroy(arr);

}
//(c) Display all offers of a given type, having their departure after a given date.

void display_certain(Console* console)
{
	char search_date[100] = "", search_type[100] = "";
	DynamicArray* arr = createDA(100);
	Repos* repohere = createRepos(*arr);
	printf("\n What type you want to search for?\n");
	gets_s(search_type, sizeof(search_type));
	printf("\n After what date you want to look for?\n");
	gets_s(search_date, sizeof(search_date));
	if (validate_type(search_type) && validate_date(search_date)) {
		certain_search_s(&console->service, search_type, search_date, repohere);
		for (int i = 0; i < repohere->array.count; i++)
			printf("Type: %s Destination: %s Date: %s Price: %d \n", repohere->array.data[i].type, repohere->array.data[i].destination, repohere->array.data[i].date, repohere->array.data[i].price);
	}
	else 
		printf("\nParameters not valid\n");
	
	destroy(arr);
}

void undo_ui(Console* console)
{
	if (undo_op(&console->service.undo_redo) == 0)
		printf("\n There is no undo operation to do\n");
	else
		copy_repo_s(&console->service, &console->service.undo_redo);

}

void redo_ui(Console* console)
{
	if (redo_op(&console->service.undo_redo) == 0)
		printf("\nThere is no redo to do \n");
	else copy_repo_s(&console->service, &console->service.undo_redo);
}


void add_offer_ui(Console* console) {
	char type[100] = "", destination[100] = "", date[100] = "";
	int price = 0; char debug[3] = "";
	printf("\n Enter the type of an offer\n");
	//gets_s(debug, sizeof(debug));
	gets_s(type, sizeof(type));
	printf("\n Enter the destination of an offer\n");
	gets_s(destination, sizeof(destination));
	printf("\n Enter the date of departure\n");
	gets_s(date, sizeof(date));
	printf("\n Enter the price of the offer\n");
	scanf("%d", &price);
	if (validate_type(type) && validate_date(date) && validate_price(price) && validate_destination(destination))
	{
		add_offer_s(&console->service, type, destination, date, price);

	}
	else printf("\n Not valid parameters\n");
}

void delete_offer_ui(Console* console) {
	char destination[100] = "", date[100] = "";
	//char debug[3];
	printf("\n Enter the destination of an offer\n");
	//gets_s(debug, sizeof(debug));
	gets_s(destination, sizeof(destination));
	printf("\n Enter the date of departure\n");
	gets_s(date, sizeof(date));

	if (validate_date(date) && validate_destination(destination))
	{
		if (delete_offer_s(&console->service, destination, date) == 0)
			printf("\n We found no such offer\n");
		else
			printf("\n The offer was deleted succesfully\n");

	}
	else printf("\n Not valid parameters\n");
}

void update_offer_ui(Console* console) {
	char destination[100] = "", date[100] = "";
	int n_price = 0; 
	//char debug[3];
	char n_dest[30] = "", n_date[30] = "", n_type[30] = "";

	printf("\n Enter the destination of an offer\n");
	//gets_s(debug, sizeof(debug));
	gets_s(destination, sizeof(destination));
	printf("\n Enter the date of departure\n");
	gets_s(date, sizeof(date));
	printf("\n Enter the NEW type\n");
	gets_s(n_type, sizeof(n_type));
	printf("\n Enter the NEW destination\n");
	gets_s(n_dest, sizeof(n_dest));
	printf("\n Enter the NEW date\n");
	gets_s(n_date, sizeof(n_date));
	printf("\n Enter the NEW price of the offer\n");
	scanf("%d", &n_price);


	if (validate_type(n_type) && validate_date(n_date) && validate_price(n_price) && validate_destination(n_dest))
	{
		if (update_offer_s(&console->service, destination, date, n_type, n_dest, n_date, n_price) == 0)
			printf("\n We found no such offer\n");
		else
			printf("\n The offer was updated succesfully\n");

	}
	else printf("\n Not valid parameters\n");
}


void menu() {
	printf("\n 1.Add a new offer\n 2.Delete an offer\n 3.Update and offer");
	printf("\n 4.Display all tourism offers whose destinations contain a given string,sorted by price");
	printf("\n 5.Display all offers of a given type, having their departure after a given date");
	printf("\n 6.Undo\n 7.Redo.\n x.Exit");

}
void solve(Console* console) {
	int done = 0;
	while (done == 0) {
		menu();
		char text[5];
		printf("\n Please enter what you want to do?\n");
		gets_s(text, sizeof(text));//seems ok
		if (strlen(text) > 2)
			printf(" Please enter valid command!\n");
		else
			switch (text[0]) {
			case '1':
				add_offer_ui(console);
				break;
			case '2':
				delete_offer_ui(console);
				break;
			case '3':
				update_offer_ui(console);
				break;
			case '4':
				display_search_ui(console);
				break;
			case '5':
				display_certain(console);
				break;
			case '6':
				undo_ui(console);
				break;
			case '7':
				redo_ui(console);
				break;
			case 'x':
				done = 1;
				break;
			case 'i':
				display_test_ui(console);
				break;
			default:
				printf("\n You misspelled\n");
				

			}
	}

}
