#pragma once
#include "watchlist.h"
class WatchlistHTML :public Watchlist {
private:
	vector<Tutorial>objects;
	string file_name;

public:
	void write()override;
	void read()override;
	void set_data(vector<Tutorial>obj)override;
	WatchlistHTML();
	~WatchlistHTML()override = default;
};