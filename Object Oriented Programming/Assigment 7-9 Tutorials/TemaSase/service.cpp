


#include "service.h"
#include <vector>
#include <algorithm>
#include "exceptions.h"

Service::Service(Repo& repo, Repo& repo_user) :
	repo{ repo }, repo_user{ repo_user } {}

void Service::add_s(string title, string presenter, string duration, int likes, string link)
{
	this->repo.add_repo(title, presenter, duration, likes, link);
}

void Service::remove_s(string title, string link)
{
	this->repo.remove_repo(title, link);

}

void Service::update_s(string title, string n_presenter, string n_duration, int n_likes, string link)
{
	this->repo.update_repo(title, n_presenter, n_duration, n_likes, link);
}

vector<Tutorial>& Service::get_repo() { return this->repo.GetDA(); }

const vector<Tutorial>& Service::get_user_repo() {
	return this->repo_user.GetDA();
	//maybe cus it is const?
}

int Service::add_user_s(Tutorial temp2) {
	int index = this->repo_user.check_exists(temp2.get_title(), temp2.get_link());
	if (index == -1) {
		this->repo_user.add_repo(temp2.get_title(), temp2.get_presenter(), temp2.get_duration(), temp2.get_likes(), temp2.get_link());
		return 1;
	}
	return 0;

}

int Service::remove_user_s(Tutorial temp2, bool a) {
	int index2 = this->repo_user.check_exists(temp2.get_title(), temp2.get_link());
	if (index2 != -1) {

		if (a == true) {
			this->repo_user.update_repo(temp2.get_title(), temp2.get_presenter(), temp2.get_duration(), temp2.get_likes() + 1, temp2.get_link());
			this->repo.update_repo(temp2.get_title(), temp2.get_presenter(), temp2.get_duration(), temp2.get_likes() + 1, temp2.get_link());
		}
		this->repo_user.remove_repo(temp2.get_title(), temp2.get_link());
		return 1;
	}
	return 0;
}


int Service::get_size()
{
	return this->repo.get_size();
}


vector<Tutorial> Service::filter_tutorials(string presenter)
{
	if (presenter == "")
		return this->get_repo();
	else {
		vector<Tutorial>elements(get_repo().size());
		auto it = copy_if(this->get_repo().begin(), this->get_repo().end(), elements.begin(),
			[presenter](Tutorial tutorial) {
				
				if (tutorial.get_presenter() == presenter)
					return true;
				return false;
			});
		
		elements.resize(it - elements.begin());
		return elements;
	}
}


