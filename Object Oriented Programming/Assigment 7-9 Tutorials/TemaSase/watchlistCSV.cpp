#include "watchlistCSV.h"
#include <fstream>
#include <qdesktopservices.h>
#include <qurl.h>

void WatchlistCSV::read()
{
	QString file = R"(C:\Users\potat\Documents\TemaSase\tutorialeVirgula.csv)";
	QDesktopServices::openUrl(QUrl::fromLocalFile(file));

}

void WatchlistCSV::write()
{
	ofstream fout(this->file_name);
	for (auto& t : objects)
	{
		fout << t.get_title() << ',' << t.get_presenter() << ',' << t.get_duration() << ',' << t.get_likes() << ',' << t.get_link() << '\n';

	}
	fout.close();
	this->objects.clear();
}

void WatchlistCSV::set_data(vector<Tutorial> obj)
{
	this->objects = move(obj);
}

WatchlistCSV::WatchlistCSV()
{
	this->file_name = R"(C:\Users\potat\Documents\TemaSase\tutorialeVirgula.csv)";
}
