#pragma once
#include <vector>
#include "domain.h"
class Watchlist {
public:
	virtual void read() = 0;
	virtual void write() = 0;
	virtual ~Watchlist() = default;
	virtual void set_data(vector<Tutorial> objects) = 0;
};