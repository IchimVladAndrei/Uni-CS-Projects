#pragma once
#include "repo.h"
#include "reundo.h"
typedef struct {
	Repos repo;
	UndoRedo undo_redo;
}Service;
/// <summary>
/// This function creates the service
/// </summary>
/// <param name="repo"></param>
/// <param name="undoredo"></param>
/// <returns>the service created</returns>
Service* create_service(Repos repo,UndoRedo undoredo);
/// <summary>
/// This function destroys the service created
/// </summary>
/// <param name="service"></param>
void destroy_s(Service* service);
/// <summary>
/// This functions adds an offer to the service
/// </summary>
/// <param name="service"></param>
/// <param name="type"></param>
/// <param name="destination"></param>
/// <param name="date"></param>
/// <param name="price"></param>
void add_offer_s(Service* service, char type[], char destination[], char date[], int price);

/// <summary>
/// This function deletes an offer to the service 
/// </summary>
/// <param name="service"></param>
/// <param name="destination"></param>
/// <param name="date"></param>
/// <returns></returns>
int delete_offer_s(Service* service, char destination[], char date[]);

/// <summary>
/// This function updates an offer from the service.
/// </summary>
/// <param name="service"></param>
/// <param name="destination"></param>
/// <param name="date"></param>
/// <param name="type"></param>
/// <param name="n_dest"></param>
/// <param name="n_date"></param>
/// <param name="price"></param>
/// <returns></returns>
int update_offer_s(Service* service, char destination[], char date[], char type[], char n_dest[], char n_date[], int price);

/// <summary>
/// This function helps for the searching of certain destination and its sorting by price
/// </summary>
/// <param name="service"></param>
/// <param name="search_dest"></param>
/// <param name="repohere"></param>
void search_s(Service* service, char search_dest[], Repos* repohere);

/// <summary>
/// This function sorts by price in ascending order/// </summary>
/// <param name="service"></param>
/// <param name="repohere"></param>
void sort_price(Service* service, Repos* repohere);

/// <summary>
/// This function performes a search for certain type and after a certain date
/// </summary>
/// <param name="service"></param>
/// <param name="search_type"></param>
/// <param name="search_date"></param>
/// <param name="repohere"></param>
void certain_search_s(Service* service,char search_type[],char search_date[],Repos* repohere);

/// <summary>/// This function creates an copy of the repo/// </summary>/// <param name="service"></param>/// <param name="undoredo"></param>
void copy_repo_s(Service* service, UndoRedo* undoredo);