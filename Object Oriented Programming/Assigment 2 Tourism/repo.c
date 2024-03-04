#include "repo.h"
#include "domain.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma once

Repos* createRepos(DynamicArray arr)
{
	Repos* repo = (Repos*)malloc(sizeof(repo));
	if (repo == NULL)
		return NULL;
	repo->array = arr;
	return repo;

}

void add_offer_r(Repos* repo, char type[], char destination[], char date[], int price)
{
	int test = -1;
	if (test == -1) {
		Offer offer;
		offer = create_offer(type, destination, date, price);
		add_TElem(&repo->array, offer);

	}

}

Repos duplicate(Repos* repo) {
	Repos n_repo;
	n_repo.array.max_len = repo->array.max_len;
	n_repo.array.count = repo->array.count;
	n_repo.array.data = (Offer*)malloc(n_repo.array.max_len * sizeof(Offer));
	copy_repo(repo, n_repo);
	return n_repo;
}

void copy_repo(Repos* repo, Repos n_repo) {
	for (int i = 0; i < repo->array.count; i++)
		new_values(&n_repo.array.data[i], repo->array.data[i]);

}

int delete_offer_r(Repos* repo, char destination[], char date[])
{
	int pos = -1;
	pos = check(repo, destination, date);
	if (pos == -1)
		return 0;
	else {
		delete_TElem(&repo->array, pos);
		return 1;
	}
}

int update_offer_r(Repos* repo, char destination[], char date[], char type[], char n_dest[], char n_date[], int price)
{
	int pos = -1;
	pos = check(repo, destination, date);
	if (pos == -1)
		return 0;
	else {
		Offer temp;
		temp = create_offer(type, n_dest, n_date, price);
		update_TElem(&repo->array, temp, pos);
		return 1;
	}
}

int check(Repos* repo, char destination[], char date[]) {
	for (int i = 0; i < repo->array.count; i++)
		if ((strcmp(repo->array.data[i].destination, destination) == 0 && (strcmp(repo->array.data[i].date, date) == 0)))
			return i;
	return -1;
}

void init_repo(Repos* rep) {
	add_offer_r(rep, "Seaside", "USA", "22/10/2021", 4000);
	add_offer_r(rep, "Seaside", "Germany", "31/02/2022", 300);
	add_offer_r(rep, "Seaside", "England", "10/12/2020", 2000);
	add_offer_r(rep, "Seaside", "Italy", "05/09/2019", 500);
	add_offer_r(rep, "City break", "France", "11/10/2020", 300);
	add_offer_r(rep, "Mountain", "Nepal", "25/12/2022", 2500);
	add_offer_r(rep, "City break", "Belgium", "26/11/2023", 250);
	add_offer_r(rep, "Mountain", "Russia", "12/12/2019", 900);
	add_offer_r(rep, "Seaside", "Greece", "17/06/2020", 400);
	add_offer_r(rep, "Mountain", "Romania", "29/04/2021",200);

}

int get_count(Repos* repo)
{
	return repo->array.count;
}

void destroy_r(Repos* repo)
{
	if (repo == NULL)
		return;
	free(repo);
}

void search_r(Repos* repo, char search_dest[], Repos* repohere)
{
	//search_dest[strlen(search_dest) - 1] = '\0';

	if (strcmp(search_dest, "") == 0) {
		for (int i = 0; i < repo->array.count; i++)
			add_offer_r(repohere, repo->array.data[i].type, repo->array.data[i].destination, repo->array.data[i].date, repo->array.data[i].price);
	}
	else {
		for (int i = 0; i < repo->array.count; i++)

			if (strstr(repo->array.data[i].destination, search_dest) != NULL)
				add_offer_r(repohere, repo->array.data[i].type, repo->array.data[i].destination, repo->array.data[i].date, repo->array.data[i].price);


	}
}

void certain_search_r(Repos* repo, char search_type[], char search_date[],Repos* repohere)
{
	//"05/09/2019
	// 05/10/2021
	// 0123456789
	// MAI VEZI SI ALTE CAZURI
	// TRATEAZA DACA NU SE PUNE NIMIC IN REPO GEN NU ARE CE PUNE
	//strcmp(repo->array.data[i].date+6, search_date + 6) >= 0 && strncmp(repo->array.data[i].date + 3, search_date + 3, 2) >= 0)
	for (int i = 0; i < repo->array.count; i++) {
		if (strcmp(repo->array.data[i].type, search_type) == 0) {
			if (strcmp(repo->array.data[i].date + 6, search_date + 6) > 0)
				add_offer_r(repohere, repo->array.data[i].type, repo->array.data[i].destination, repo->array.data[i].date, repo->array.data[i].price);
			else if (strcmp(repo->array.data[i].date + 6, search_date + 6) == 0)
			{
				if(strncmp(repo->array.data[i].date + 3, search_date + 3, 2) >0)
					add_offer_r(repohere, repo->array.data[i].type, repo->array.data[i].destination, repo->array.data[i].date, repo->array.data[i].price);
				else if (strncmp(repo->array.data[i].date + 3, search_date + 3, 2) == 0)
				{
					if(strncmp(repo->array.data[i].date , search_date, 2) > 0)
						add_offer_r(repohere, repo->array.data[i].type, repo->array.data[i].destination, repo->array.data[i].date, repo->array.data[i].price);
				}
			}
				
		}
	}
}


