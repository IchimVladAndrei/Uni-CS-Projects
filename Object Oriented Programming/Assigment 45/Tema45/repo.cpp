#include "repo.h"
#pragma once

Repo::Repo(DynamicArray<Tutorial>* DA) {
	this->DA = DA;
}
Repo::~Repo()
{
	delete this->DA;
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
	return this->DA->get_size_da();
}

DynamicArray<Tutorial>* Repo::GetDA()
{
	return this->DA;
}

int Repo::add_repo(string title, string presenter, string duration, int likes, string link)
{
	int pos = check_exists(title,link);
	if (pos == -1) {
		Tutorial temp(title, presenter, duration, likes, link);
		this->DA->Add(temp);
		return 0;
	}

	return 1;
}

int Repo::remove_repo(string title, string link)
{
	int pos = check_exists(title, link);
	if (pos != -1) {
		//Tutorial temp(title, (*this->DA)[pos].get_presenter(), (*this->DA)[pos].get_duration(), (*this->DA)[pos].get_likes(), link);
		this->DA->Delete(pos);
		return 0;
	}
	return 1;
}

int Repo::update_repo(string title, string n_presenter, string n_duration, int n_likes, string link)
{
	int pos = check_exists(title, link);
	if (pos != -1) {
		Tutorial temp(title, n_presenter, n_duration, n_likes, link);
		this->DA->Update(temp, pos);
		return 0;
	}
	return 1;
}

int Repo::check_exists(string title, string link)
{
	for (int i = 0; i < this->DA->get_size_da(); i++)
		if ((*this->DA)[i].get_title() == title && (*this->DA)[i].get_link() == link)
			return i;
	return -1;	
}
