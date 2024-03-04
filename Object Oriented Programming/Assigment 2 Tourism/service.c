#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "service.h"


Service* create_service(Repos repo,UndoRedo undoredo)
{
	Service* service = (Service*)malloc(sizeof(Service));
	if (service == NULL)
		return NULL;
	service->repo = repo;
	service->undo_redo = undoredo;
	return service;
}

void destroy_s(Service* service) {
	if (service == NULL)
		return;
	free(service);
}

void add_offer_s(Service* service, char type[], char destination[], char date[], int price)
{
	add_offer_r(&service->repo, type, destination, date, price);
	add_reundo(&service->undo_redo, &service->repo);
}

int delete_offer_s(Service* service, char destination[], char date[])
{
	if (delete_offer_r(&service->repo, destination, date) == 0)
		return 0;
	else {

		
		add_reundo(&service->undo_redo, &service->repo);
		return 1;
	}
}

int update_offer_s(Service* service, char destination[], char date[], char type[], char n_dest[], char n_date[], int price) {
	if (update_offer_r(&service->repo, destination, date, type, n_dest, n_date, price) == 0)
		return 0;
	else {
		add_reundo(&service->undo_redo, &service->repo);
		return 1;
	}

}

void search_s(Service* service, char search_dest[], Repos* repohere)
{
	search_r(&service->repo, search_dest, repohere);
	sort_price(service, repohere);
}

void sort_price(Service* service, Repos* repohere) {
	
	for(int i=0;i<repohere->array.count-1;i++)
		for(int j=i+1;j<repohere->array.count;j++)
			if (repohere->array.data[i].price > repohere->array.data[j].price)
			{
				TElem aux;
				aux = repohere->array.data[i];
				repohere->array.data[i] = repohere->array.data[j];
				repohere->array.data[j] = aux;
			}
}

void certain_search_s(Service* service, char search_type[], char search_date[], Repos* repohere)
{
	certain_search_r(&service->repo, search_type, search_date, repohere);
}

void copy_repo_s(Service* service, UndoRedo* undoredo)
{
	service->repo.array.count = undoredo->data[undoredo->current_pos].array.count;
	service->repo.array.max_len = undoredo->data[undoredo->current_pos].array.max_len;
	for (int i = 0; i < undoredo->data[undoredo->current_pos].array.count; i++)
		service->repo.array.data[i] = undoredo->data[undoredo->current_pos].array.data[i];
}
