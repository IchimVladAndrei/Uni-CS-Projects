#include "watchlistHTML.h"
#include <fstream>
#include <qurl.h>
#include <qdesktopservices.h>
#include "../Tema89/interfaceUser.h"

void WatchlistHTML::write()
{
	ofstream fout(this->file_name);
	fout << "<!DOCTYPE html>\n";
	fout << "<html>\n";
	fout << "<head>\n";
	fout << "\t<title>Watchlist</title>\n";
	fout << "</head>\n";
	fout << "<body>\n";
	fout << "<table border=\"1\">\n";
	fout << "\t<tr>\n";
	fout << "\t\t<td>Title</td>\n";
	fout << "\t\t<td>Presenter</td>\n";
	fout << "\t\t<td>Duration</td>\n";
	fout << "\t\t<td>Link</td>\n";
	fout << "\t</tr>\n";
	for (auto& t : this->objects) {
		fout << "\t<tr>\n";
		fout << "\t\t<td>" << t.get_title() << "</td>\n";
		fout << "\t\t<td>" << t.get_presenter() << "</td>\n";
		fout << "\t\t<td>" << t.get_duration() << "</td>\n";
		fout << "\t\t<td>" << t.get_likes() << "</td>\n";
		fout << "\t\t<td><a href=\"" << t.get_link() << "\">Link</a></td>\n";
		fout << "\t</tr>\n";


	}
	fout << "</table>\n";
	fout << "</body>\n";
	fout << "</html>\n";


}

void WatchlistHTML::read()
{

	QString file = R"(C:\Users\potat\Documents\TemaSase\tutorialeWeb.html)";
	QDesktopServices::openUrl(QUrl::fromLocalFile(file));

}

void WatchlistHTML::set_data(vector<Tutorial> obj)
{
	this->objects = move(obj);
}

WatchlistHTML::WatchlistHTML()
{
	this->file_name = R"(C:\Users\potat\Documents\TemaSase\tutorialeWeb.html)";
}


