


#include "repo.h"
#include "exceptions.h"
#pragma once

Repo::Repo() {
}


void Repo::init_repo()
{
	add_repo("Class", "Charlie", "12:40", 1000, "www.a");
	add_repo("Template", "Charlie", "11:00", 423, "www.b");
	add_repo("Overload", "Andrew", "50:40", 345, "www.c");
	add_repo("Reference", "Andrew", "32:11", 765, "www.d");
	add_repo("Referenca", "Bndrew", "12:11", 762, "www.e");
	add_repo("Referencb", "Cndrew", "22:11", 763, "www.f");
	add_repo("Referencc", "Dndrew", "42:11", 764, "www.g");
	add_repo("Referencd", "Endrew", "52:11", 789, "www.h");
	add_repo("Referencf", "Fndrew", "12:11", 767, "www.i");
	add_repo("Referencg", "Gndrew", "10:11", 742, "www.o");
}

int Repo::get_size()
{
	return this->objects.size();
}

vector<Tutorial>& Repo::GetDA() {
	return this->objects;
}

void Repo::add_repo(string title, string presenter, string duration, int likes, string link)
{
	int pos = check_exists(title, link);
	if (pos == -1) {
		Tutorial temp(title, presenter, duration, likes, link);
		this->objects.push_back(temp);
	}

	else
		throw RepoExceptions("The tutorial already exists");
}

void Repo::remove_repo(string title, string link)
{
	int pos = check_exists(title, link);
	if (pos != -1) {
		this->objects.erase(this->objects.begin() + pos);

	}
	else throw RepoExceptions("The tutorial doesn't exists");
}

void Repo::update_repo(string title, string n_presenter, string n_duration, int n_likes, string link)
{
	int pos = check_exists(title, link);
	if (pos != -1) {
		Tutorial temp(title, n_presenter, n_duration, n_likes, link);
		this->objects[pos] = temp;

	}
	else throw RepoExceptions("The tutorial doesn't exists");

}

int Repo::check_exists(string title, string link)
{
	int i = 0;
	for (auto& e : this->objects) {
		if (e.get_title() == title && e.get_link() == link)
			return i;
		i++;
	}
	return -1;
}
