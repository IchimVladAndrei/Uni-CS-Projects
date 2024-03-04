


#include "console.h"
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <limits>



Console::Console(Service& service) :
	service{ service } {}
void Console::solve()
{
	bool temp0 = false;
	while (!temp0) {
		string type;
		cout << "How you want to save the file?\n1.CSV\n2.HTML\n";
		cin >> type;
		cout << "\n";
		switch (type[0]) {
		case '1':
			this->watchlist = new WatchlistCSV();
			temp0 = true;
			break;
		case '2':
			this->watchlist = new WatchlistHTML();
			temp0 = true;
			break;
		default:
			cout << "Not valid!";
			break;
		}
	}
	bool temp = false;
	while (!temp) {

		string cmd;
		cout << "1.Admin" << endl << "2.User\n";
		cin >> cmd;
		cout << endl;
		switch (cmd[0]) {
		case '1': {
			admin_mode();
			break; }

		case '2': {
			user_mode();
			break; }

		case 'x':
			delete this->watchlist;
			temp = true;
			break;
		default:
			cout << "Option not valid!" << endl;

		}
	}

}
int Console::wishlist() {
	int i = 0;
	vector<Tutorial> elements(this->service.get_repo().size());
	string presenter_temp;
	cout << "What presenter you want to see?\n";
	cin.ignore();
	getline(cin, presenter_temp);
	this->service.filter_tutorials(elements, presenter_temp);
	if (!elements.empty()) {
		while (i < elements.size())
		{
			if (i == 0) {
				cout << "\nTitle: " << elements[i].get_title() <<
					" Presenter: " << elements[i].get_presenter() <<
					" Duration: " << elements[i].get_duration() <<
					" Likes: " << elements[i].get_likes() <<
					" Link: " << elements[i].get_link() << endl << endl;
				string a = elements[i].get_link();
				wstring temp = wstring(a.begin(), a.end());
				LPCWSTR wtemp = temp.c_str();
				ShellExecute(0, 0, wtemp, 0, 0, SW_SHOW);
				menu_wishlist();
				i++;
			}
			string cmd;
			cout << ">>";
			cin >> cmd;
			if (cmd != "1" && cmd != "2" && cmd != "3" && cmd != "b")
				cout << "Not ok\n";
			else {
				switch (cmd[0]) {
				case '1':
				{
					if (this->service.add_user_s(elements[i]) == 1)
						cout << "The tutorial has been added to the watchlist!\n";
					break;
				}
				case '2':
				{
					i++;
					if (i < elements.size())
					{
						cout << "\n Title: " << elements[i].get_title() <<
							" Presenter: " << elements[i].get_presenter() <<
							" Duration: " << elements[i].get_duration() <<
							" Likes: " << elements[i].get_likes() <<
							" Link: " << elements[i].get_link() << endl << endl;
						string a = elements[i].get_link();
						wstring temp = wstring(a.begin(), a.end());
						LPCWSTR wtemp = temp.c_str();
						ShellExecute(0, 0, wtemp, 0, 0, SW_SHOW);
						menu_wishlist();
					}
					else i = 0;
					break;
				}
				case '3':
				{
					string cmd;
					cout << "\nDid you liked the tutorial? Yes/No\n";
					cin >> cmd;
					if (cmd == "Yes") {
						if (this->service.remove_user_s(elements[i], true) == 1)
							return 1;
						cout << "Deleted\n";

					}
					else if (cmd == "No") {
						if (this->service.remove_user_s(elements[i], false) == 1)
							return 1;
						cout << "Deleted\n";

					}
					else cout << "Invalid input\n";


				}
				case 'b':
				{

					return -2;
				}
				default:
					cout << "Not ok while!\n";
					break;
				}
			}
		}
	}

}
void Console::see_wishlist() {
	this->watchlist->set_data(this->service.get_user_repo());
	this->watchlist->write();
	this->watchlist->read();//rename function;

}

///Modes

void Console::user_mode() {
	bool cond = false;
	while (!cond) {
		menu_user_mode();

		try {
			string cmd;
			cout << ">>";
			cin >> cmd;

			switch (cmd[0]) {
			case '1':

				wishlist();
				break;
			case '2':
				print_wishlist();
				break;
			case '3':
				see_wishlist();
				break;
			case 'b':
				cond = true;
				break;
			default:
				cout << "Not ok!";
			}

		}
		catch (RepoExceptions& message) {
			cout << message.what();
			cout << endl;
			cin.clear();
			cin.ignore();
		}
	}

}
void Console::admin_mode() {
	bool temp = false;
	while (!temp) {
		admin_print();
		try {
			string cmd;
			cout << "\n>> ";

			cin >> cmd;
			switch (cmd[0]) {
			case '1':
				add_admin_ui();
				break;
			case '2':
				remove_admin_ui();
				break;
			case '3':
				update_admin_ui();
				break;
			case 'p':
				print_help();
				break;
			case 'b':
				temp = true;
				break;
			default:
				cout << "\nOption not valid\n";
				break;
			}
		}
		catch (ValidatorExceptions& message) {
			cout << message.what();
			cout << endl;
			cin.clear(); // clear the error state of the input stream
			cin.ignore(); // discard any remaining input
		}
		catch (RepoExceptions& message) {
			cout << message.what();
			cout << endl;
			cin.clear(); // clear the error state of the input stream
			cin.ignore(); // discard any remaining input

		}
	}
}

///Admin modes

void Console::add_admin_ui() {
	string link, presenter, duration, title;
	int likes;
	cout << "\n Title is:\n";
	cin >> title;
	cout << "\nPresenter is:\n";
	cin >> presenter;
	cout << "\nDuration is:\n";
	cin >> duration;
	cout << "\nThe number of likes is:\n";
	cin >> likes;
	cout << "\nThe link of the tutorial is:\n";
	cin >> link;

	if (!Validator::validate_title(title) || !Validator::validate_presenter(presenter)
		|| !Validator::validate_duration(duration) || !Validator::validate_likes(likes)
		|| !Validator::validate_link(link))
		throw ValidatorExceptions("The info about the tutorial isn't correct!");

	else
	{
		this->service.add_s(title, presenter, duration, likes, link);
		cout << "\nThe tutorial has been added\n";

	}

}
void Console::remove_admin_ui()
{
	string link, title;
	cout << "\n Title is:\n";
	cin >> title;
	cout << "\nThe link of the tutorial is:\n";
	cin >> link;
	if (!Validator::validate_title(title) || !Validator::validate_link(link))
		throw ValidatorExceptions("The info about the tutorial isn't correct!");
	else {
		this->service.remove_s(title, link);
		cout << "\nThe tutorial has been removed succesfully\n";

	}
}
void Console::update_admin_ui() {
	string link, title;
	cout << "\n Title is:\n";
	cin >> title;
	cout << "\nThe link of the tutorial is:\n";
	cin >> link;

	string n_presenter, n_duration;
	int n_likes;


	cout << "\nNEW presenter is:\n";
	cin >> n_presenter;
	cout << "\nNEW duration is:\n";
	cin >> n_duration;
	cout << "\nNEW number of likes is:\n";
	cin >> n_likes;

	if (!Validator::validate_title(title) || !Validator::validate_presenter(n_presenter)
		|| !Validator::validate_duration(n_duration) || !Validator::validate_likes(n_likes)
		|| !Validator::validate_link(link))
		throw ValidatorExceptions("The info about the tutorial isn't correct!");
	else {
		this->service.update_s(title, n_presenter, n_duration, n_likes, link);
		cout << "\nTutorial updated succesfully\n";


	}



}

///Printing 

void Console::print_help()
{
	for (auto x : this->service.get_repo())

		cout << " Title: " << x.get_title() <<
		" Presenter: " << x.get_presenter() <<
		" Duration: " << x.get_duration() <<
		" Likes: " << x.get_likes() <<
		" Link: " << x.get_link() << endl;
}
void Console::print_wishlist() {

	for (auto i : this->service.get_user_repo())

		cout << " Title: " << i.get_title() <<
		" Presenter: " << i.get_presenter() <<
		" Duration: " << i.get_duration() <<
		" Likes: " << i.get_likes() <<
		" Link: " << i.get_link() << endl;
}

///Menus

void Console::menu_user_mode() {
	cout << "1.Create wishlist\n";
	cout << "2.See wishlist\n";
	cout << "3.Open wishlist\n";
	cout << "b.Back\n";
}
void Console::admin_print()
{
	cout << "1.ADD a tutorial" << endl;
	cout << "2.REMOVE a tutorial" << endl;
	cout << "3.UPDATE a tutorial" << endl;
	cout << "b.BACK" << endl;
	cout << "p.PRINT the tutorials";
}
void Console::menu_wishlist() {
	cout << "1.ADD the tutorial\n";
	cout << "2.NEXT\n";
	cout << "3.DELETE from watch list\n";
	cout << "b.Back\n";
}
