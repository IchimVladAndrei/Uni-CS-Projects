#include "service.h"

Service::~Service()
{
	delete this->repo;
	delete this->repo_user;
}

Service::Service(Repo* repo,Repo* repo_user)
{
	this->repo = repo;
	this->repo_user = repo_user;
}


int Service::add_s(string title, string presenter, string duration, int likes, string link)
{
	if (this->repo->add_repo(title, presenter, duration, likes, link) == 0)
		return 0;
	return 1;
}

int Service::remove_s(string title, string link)
{
	if (this->repo->remove_repo(title, link) == 0)
		return 0;
	return 1;

}

int Service::update_s(string title, string n_presenter, string n_duration, int n_likes, string link)
{	if(this->repo->update_repo(title, n_presenter, n_duration, n_likes, link)==0)
		return 0;
return 1;
}

DynamicArray<Tutorial>* Service::get_repo()
{

	return this->repo->GetDA();
}

DynamicArray <Tutorial>* Service::get_user_repo() {
	return this->repo_user->GetDA();}

//trebuie pt user
int Service::add_user_s(Tutorial temp2) {
	int index = this->repo_user->check_exists(temp2.get_title(), temp2.get_link());
	if (index == -1) {
		this->repo_user->add_repo(temp2.get_title(), temp2.get_presenter(), temp2.get_duration(), temp2.get_likes(), temp2.get_link());
		return 1;
	}
	return 0;
	////
}

int Service::remove_user_s(Tutorial temp2,bool a) {
	int index2 = this->repo_user->check_exists(temp2.get_title(), temp2.get_link());
	if (index2 != -1) {
		this->repo_user->remove_repo(temp2.get_title(),temp2.get_link());
		if (a == true) {
			this->repo_user->update_repo(temp2.get_title(), temp2.get_presenter(), temp2.get_duration(), temp2.get_likes() + 1, temp2.get_link());
			this->repo->update_repo(temp2.get_title(), temp2.get_presenter(), temp2.get_duration(), temp2.get_likes() + 1, temp2.get_link());
		}
		return 1;
	}
	else return 0;
	///
}


int Service::get_size()
{
	return this->get_repo()->get_size_da();
}

Repo* Service::change_repo(string temp_presenter)
{
	Repo* temp = this->repo;
	DynamicArray<Tutorial>* copy = new DynamicArray<Tutorial>(100);
	Repo* repo_searched = new Repo(copy);
	if (temp_presenter == "")
		return this->repo;
	for (int i = 0; i < this->repo->get_size(); i++)
		if ((*this->repo->GetDA())[i].get_presenter() == temp_presenter)
			repo_searched->add_repo((*this->repo->GetDA())[i].get_title(), temp_presenter, (*this->repo->GetDA())[i].get_duration(), (*this->repo->GetDA())[i].get_likes(),
				(*this->repo->GetDA())[i].get_link());
	this->repo = repo_searched;
	//delete copy;
	//delete repo_searched;
	return temp;
	
}

void Service::change_back(Repo* temp)
{
	this->repo = temp;
}


