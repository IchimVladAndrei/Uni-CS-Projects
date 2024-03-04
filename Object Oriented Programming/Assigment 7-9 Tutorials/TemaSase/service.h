#pragma once
#include <cstdlib>
#include "dynamic.h"
#include "domain.h"
#include "repo.h"

class Service {
private:
	Repo& repo;
	Repo& repo_user;

public:
	//destructor
	//~Service();
	//creates a service
	Service(Repo& repo, Repo& repo_user);

	// adds to the service
	void add_s(string title, string presenter, string duration, int likes, string link);
	//removes from the service
	void remove_s(string title, string link);
	//updates from the service 
	void update_s(string title, string n_presenter, string n_duration, int n_likes, string link);
	/// <summary>
	/// returns the repository
	/// </summary>
	/// <returns></returns>
	vector<Tutorial>& get_repo();

	//
	const vector<Tutorial>& get_user_repo();
	int add_user_s(Tutorial temp2);
	int remove_user_s(Tutorial temp2, bool a);
	/// <summary>
	/// gets the size of the service
	/// </summary>
	/// <returns></returns>
	int get_size();

	vector<Tutorial> filter_tutorials(string presenter);

};