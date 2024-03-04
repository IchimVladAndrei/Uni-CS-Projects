#include "exceptions.h"
#include "fileRepo.h"

vector<Tutorial> FileRepo::read_data()
{
	ifstream in(this->file_name);
	vector<Tutorial> objects;
	Tutorial current;
	while (in >> current) {
		objects.push_back(current);
	}
	return objects;
}

void FileRepo::write_data(vector<Tutorial> data)
{
	ofstream out(this->file_name);
	for (auto d : data)
		out << d << '\n';
}

Tutorial FileRepo::get_entity(int pos)
{
	vector<Tutorial>obj = read_data();

	return obj[pos];
}

FileRepo::FileRepo(string file)
{
	this->file_name = file;
	this->objects = read_data();
}

void FileRepo::add_repo(string title, string presenter, string duration, int likes, string link)
{
	int pos = check_exists(title, link);
	if (pos == -1) {
		Tutorial temp(title, presenter, duration, likes, link);
		objects.push_back(temp);
		write_data(objects);
	}

	else
		throw RepoExceptions("The tutorial already exist in file repo");
}

void FileRepo::remove_repo(string title, string link)
{
	int pos = check_exists(title, link);
	if (pos != -1) {
		objects.erase(this->objects.begin() + pos);

	}
	else throw RepoExceptions("The tutorial doesn't exist in file repo");
}

void FileRepo::update_repo(string title, string n_presenter, string n_duration, int n_likes, string link)
{
	int pos = check_exists(title, link);
	if (pos != -1) {
		Tutorial temp(title, n_presenter, n_duration, n_likes, link);
		objects[pos] = temp;
		write_data(objects);
	}
	else throw RepoExceptions("The tutorial doesn't exist in file repo");
}

int FileRepo::check_exists(string title, string link)
{
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].get_title() == title && objects[i].get_link() == link)
			return i;

	return -1;
}

int FileRepo::get_size()
{
	return objects.size();
}

