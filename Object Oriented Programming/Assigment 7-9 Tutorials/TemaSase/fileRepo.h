#pragma once
#include <fstream>
#include "repo.h"

class FileRepo : public Repo {
private:
	string file_name;
	vector<Tutorial> read_data();
	void write_data(vector<Tutorial> data);
	Tutorial get_entity(int pos);
public:
	FileRepo(string file);
	void add_repo(string title, string presenter, string duration, int likes, string link) override;
	void remove_repo(string title, string link) override;
	void update_repo(string title, string n_presenter, string n_duration, int n_likes, string link) override;
	int check_exists(string title, string link) override;
	int get_size() override;
	/*const  vector<Tutorial>& getDA() override;*/
};