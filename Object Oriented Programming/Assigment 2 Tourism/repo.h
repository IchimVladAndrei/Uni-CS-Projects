#pragma once
#include "dynamic.h"
#include "domain.h"

typedef struct {
	DynamicArray array;

}Repos;
/// <summary>
/// This function creates a repo
/// </summary>
/// <param name="arr">what DA to use</param>
/// <returns>the created repo</returns>
Repos* createRepos(DynamicArray arr);
/// <summary>
/// This function checks if there is an  offer with these parameters.
/// </summary>
/// <param name="repo">where to look for</param>
/// <param name="destination"></param>
/// <param name="date"></param>
/// <returns>the position it is found,-1 if not found</returns>
int check(Repos* repo, char destination[], char date[]);
/// <summary>
/// This function adds to the repo a new offer with the given param.
/// </summary>
/// <param name="repo"></param>
/// <param name="type"></param>
/// <param name="destination"></param>
/// <param name="date"></param>
/// <param name="price"></param>
void add_offer_r(Repos* repo, char type[], char destination[], char date[], int price);

/// <summary>
/// This function removes from the repo an offer with the given param
/// </summary>
/// <param name="repo"></param>
/// <param name="destination"></param>
/// <param name="date"></param>
/// <returns></returns>
int delete_offer_r(Repos* repo, char destination[], char date[]);
/// <summary>
/// This function updates an offer with the same param
/// </summary>
/// <param name="repo"></param>
/// <param name="destination"></param>
/// <param name="date"></param>
/// <param name="type"></param>
/// <param name="n_dest"></param>
/// <param name="n_date"></param>
/// <param name="price"></param>
/// <returns></returns>
int update_offer_r(Repos* repo, char destination[], char date[], char type[], char n_dest[], char n_date[], int price);
/// <summary>
/// This function adds 10 elements to the inital repo
/// </summary>
/// <param name="rep"></param>
void init_repo(Repos* rep);
/// <summary>
/// This function gets the number of current elements in the repo
/// </summary>
/// <param name="repo"></param>
/// <returns></returns>
int get_count(Repos* repo);
/// <summary>
/// This function destroys the repo.
/// </summary>
/// <param name="repo"></param>
void destroy_r(Repos* repo);

/// <summary>
/// This function duplicates repo to a new repo
/// </summary>
/// <param name="repo"></param>
/// <returns>New repo</returns>
Repos duplicate(Repos* repo);
/// <summary>
/// This function does the copying values to a new repo
/// </summary>
/// <param name="repo"></param>
/// <param name="new_repo"></param>
void copy_repo(Repos* repo, Repos new_repo);

/// <summary>
/// This function searches in the repo for the searched destination and creates a new repo
/// </summary>
/// <param name="repo"></param>
/// <param name="search_dest"></param>
/// <param name="repohere"></param>
void search_r(Repos* repo, char search_dest[], Repos* repohere);
/// <summary>/// This function adds to a new repo the offers of type and after searched date/// </summary>/// <param name="repo"></param>/// <param name="search_type"></param>/// <param name="search_date"></param>/// <param name="repohere"></param>
void certain_search_r(Repos* repo, char search_type[], char search_date[],Repos*repohere);