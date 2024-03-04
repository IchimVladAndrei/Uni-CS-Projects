#include "console.h"
#include <iostream>
#include <cstdlib>
#include <Windows.h>
Console::Console()
{
}

Console::~Console()
{
	delete this->service;
}

Console::Console(Service* service,Validator* validator)
{
	this->service = service;
	this->validator = validator;

}

void Console::admin_print()
{
	cout << "1.ADD" << endl;
	cout << "2.REMOVE" << endl;
	cout << "3.UPDATE" << endl;
	cout << "b.BACK" << endl;
}

void Console::solve()
{
	bool temp = false;
	while (!temp) {
		string cmd;
		cout << "1.Admin" << endl << "2.User\n";
		cin >> cmd;
		cout << endl;
		switch (cmd[0]) {
		case '1': {
			admin();
			break; }

		case '2': {
			user_mode();
			break; }
		case 'x':
			temp = true;
			break;
		default:
			cout << "Option not valid!" << endl;
			
		}
	}
}

void menu_wishlist() {
	cout << "1.Add\n";
	cout << "2.Next\n";
	cout << "3.Delete from watch list\n";
	cout << "b.Back\n";
}

void menu_user_mode() {
	cout << "1.Create wishlist\n";
	cout << "2.See wishlist\n";
	cout << "b.Back\n";
}

int Console::wishlist() {
	int i = 0;
	string presenter_temp;
	cout << "What presenter you want to see?";
	cin.ignore();
	//cin >> presenter_temp;
	getline(cin, presenter_temp);
	
		Repo* here;
	here = this->service->change_repo(presenter_temp);

	
	while (i < this->service->get_size())
	{		if (i == 0) {
				cout << " Title: " << (*this->service->get_repo())[i].get_title() <<
					" Presenter: " << (*this->service->get_repo())[i].get_presenter() <<
					" Duration: " << (*this->service->get_repo())[i].get_duration() <<
					" Likes: " << (*this->service->get_repo())[i].get_likes() <<
					" Link: " << (*this->service->get_repo())[i].get_link() << endl;
				string a = (*this->service->get_repo())[i].get_link();
				wstring temp = wstring(a.begin(), a.end());
				LPCWSTR wtemp = temp.c_str();
				ShellExecute(0, 0, wtemp, 0, 0, SW_SHOW);
				///cumva sa nu fie repetat
				menu_wishlist();
		}
			string cmd;
			cout << ">>\n";
			cin >> cmd;
			if (cmd != "1" && cmd != "2" && cmd != "3" && cmd != "b")
				cout << "Not ok\n";
			else {
				switch (cmd[0]) {
				case '1':
				{
					if (this->service->add_user_s((*this->service->get_repo())[i]) == 1)

					break;
				}
				case '2':
				{
					i++;
					if (i < this->service->get_size())
					{
						cout << " Title: " << (*this->service->get_repo())[i].get_title() <<
							" Presenter: " << (*this->service->get_repo())[i].get_presenter() <<
							" Duration: " << (*this->service->get_repo())[i].get_duration() <<
							" Likes: " << (*this->service->get_repo())[i].get_likes() <<
							" Link: " << (*this->service->get_repo())[i].get_link() << endl;
						string a = (*this->service->get_repo())[i].get_link();
						wstring temp = wstring(a.begin(), a.end());
						LPCWSTR wtemp = temp.c_str();
						ShellExecute(0, 0, wtemp, 0, 0, SW_SHOW);
						//CONVERT STRING TO LSCWRT
						menu_wishlist();
					}
					else i=0;
					break;
				}
				case '3':
				{
					string cmd;
					cout << "\nDid you liked the tutorial? Yes/No\n";
					cin >> cmd;
					if (cmd == "Yes") {
						if (this->service->remove_user_s((*this->service->get_repo())[i], true) == 1);
						return 1;
						cout << "Deleted\n";
					}
					else if (cmd == "No") {
						if (this->service->remove_user_s((*this->service->get_repo())[i], false) == 1);
						return 1;
						cout << "Deleted\n";
					}
					else cout << "Invalid input";

					
				}
				case 'b':
				{
					this->service->change_back(here);
					delete here;
					return -2;
				}
				default:
					cout<<"Not ok while!";
					break;
				}
			}

		}
	this->service->change_back(here);
	delete here;
	}
//}

void Console::user_mode() {
	bool cond = false;
	while (!cond) {
		menu_user_mode();
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
		case 'b':
			cond = true;
			break;
		default:
			cout << "Not ok!";
		}
	}
}

	void Console::admin() {
		bool temp = false;
		while (!temp) {
			admin_print();
			string cmd;
			cout <<"\n>> ";
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
				
			}
		}
	}

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
		if (!this->validator->validate_title(title) || !this->validator->validate_presenter(presenter)
			|| !this->validator->validate_duration(duration) || !this->validator->validate_likes(likes)
			|| !this->validator->validate_link(link))
			cout << "\n The info about the tutorial isn't correct!\n";
		else
		{
			if (this->service->add_s(title, presenter, duration, likes, link) == 0)
				cout << "\nThe tutorial has been added\n";
			else cout << "\nWe couldn't add the tutorial\n";
		}
	}

	void Console::remove_admin_ui()
	{
		string link, title;
		cout << "\n Title is:\n";
		cin >> title;
		cout << "\nThe link of the tutorial is:\n";
		cin >> link;
		if (!this->validator->validate_title(title) || !this->validator->validate_link(link))
			cout << "\n The info about the tutorial isn't correct!\n";
		else {
			if (this->service->remove_s(title, link) == 0)
				cout << "\nThe tutorial has been removed succesfully\n";
			else
				cout << "\nWe couldn't remove the tutorial\n";
		}
	}

	void Console::print_help()
	{
		for (int i = 0; i < this->service->get_size(); i++)
			
			cout << " Title: " << (*this->service->get_repo())[i].get_title() <<
			" Presenter: " << (*this->service->get_repo())[i].get_presenter() << 
			" Duration: " << (*this->service->get_repo())[i].get_duration() << 
			" Likes: " << (*this->service->get_repo())[i].get_likes() << 
			" Link: " << (*this->service->get_repo())[i].get_link() << endl;
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

		if(!this->validator->validate_title(title) || !this->validator->validate_presenter(n_presenter)
			|| !this->validator->validate_duration(n_duration) || !this->validator->validate_likes(n_likes)
			|| !this->validator->validate_link(link))
			cout<<"\nThe info about the tutorial isn't correct\n";
		else {
			if (this->service->update_s(title, n_presenter, n_duration, n_likes, link) == 0)
				cout << "\nTutorial updated succesfully\n";
			else cout << "\nWe couldn't update the tutorial\n";

		}

		

	}

	void Console::print_wishlist(){
	
		for (int i = 0; i < this->service->get_user_repo()->get_size_da(); i++)

			cout << " Title: " << (*this->service->get_user_repo())[i].get_title() <<
			" Presenter: " << (*this->service->get_user_repo())[i].get_presenter() <<
			" Duration: " << (*this->service->get_user_repo())[i].get_duration() <<
			" Likes: " << (*this->service->get_user_repo())[i].get_likes() <<
			" Link: " << (*this->service->get_user_repo())[i].get_link() << endl;
	}
	
