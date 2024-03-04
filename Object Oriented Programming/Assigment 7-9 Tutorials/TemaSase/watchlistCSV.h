#pragma once
#include "watchlist.h"

class WatchlistCSV :public Watchlist {
private:
	string file_name;
	vector<Tutorial>objects;
public:
	void read()override;
	void write()override;
	void set_data(vector < Tutorial > obj) override;
	~WatchlistCSV()override = default;
	WatchlistCSV();
};