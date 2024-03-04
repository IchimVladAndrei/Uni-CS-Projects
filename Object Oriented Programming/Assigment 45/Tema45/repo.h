#pragma once
#include <cstdlib>
#include "dynamic.h"
#include "domain.h"
class Repo {
private:
	DynamicArray<Tutorial>* DA;
public:
	//destructor
	~Repo();
	/// <summary>
	/// initialize the repo with the certain entities
	/// </summary>
	void init_repo();

	//returns the size of the repo
	int get_size();

	/// <summary>
	/// returns the dynamic array
	/// </summary>
	/// <returns></returns>
	DynamicArray<Tutorial>* GetDA();

	Repo(DynamicArray<Tutorial>* DA);

	/// <summary>
	/// adds to the repo
	/// </summary>
	/// <param name="title"></param>
	/// <param name="presenter"></param>
	/// <param name="duration"></param>
	/// <param name="likes"></param>
	/// <param name="link"></param>
	/// <returns>0 for succes,1 otherwise</returns>
	int add_repo(string title, string presenter, string duration, int likes, string link);
	/// <summary>
	/// removes from the repo if the entity exists
	/// </summary>
	/// <param name="title"></param>
	/// <param name="link"></param>
	/// <returns>0 for succes, 1 otherwise</returns>
	int remove_repo(string title, string link);
	/// <summary>
	/// updates an entity found by title and link and updates the rest of the slots
	/// </summary>
	/// <param name="title"></param>
	/// <param name="n_presenter"></param>
	/// <param name="n_duration"></param>
	/// <param name="n_likes"></param>
	/// <param name="link"></param>
	/// <returns>0 for succes, 1 other wise</returns>
	int update_repo(string title, string n_presenter, string n_duration, int n_likes, string link);
	/// <summary>
	/// returns the position of the found enitity 
	/// </summary>
	/// <param name="title"></param>
	/// <param name="link"></param>
	/// <returns>pos if it is found, -1 otherwise</returns>
	int check_exists(string title,string link);
	//delete update;

	//Tutorial& operator [] (int pos) {
		//return(*this->DA)[pos];
	//}

	
};