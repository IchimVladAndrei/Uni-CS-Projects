#include "interfaceUser.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include <qdesktopservices.h>
#include <QMessageBox>

void interfaceUser::init_()
{

	this->createButton = new QPushButton{ "Create a watchlist" };
	this->seeButton = new QPushButton{ "See the watchlist" };
	this->openButton = new QPushButton{ "Open the watchlist" };
	QPushButton* toMainButton = new QPushButton{ "To home" };


	this->watchlistLW = new QListWidget{};
	QGridLayout* buttons_layout = new QGridLayout{};
	buttons_layout->addWidget(this->createButton, 0, 0);
	buttons_layout->addWidget(this->seeButton, 1, 0);
	buttons_layout->addWidget(this->openButton, 2, 0);
	buttons_layout->addWidget(toMainButton, 3, 0);
	QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(buttons_layout);

	this->setMinimumSize(400, 300);
	QObject::connect(toMainButton, &QPushButton::clicked, this, [this] {
		this->close();
		this->hide();
		emit backToInterfaceRequested();

		});




}

void interfaceUser::connectSS()
{
	QObject::connect(this->openButton, &QPushButton::clicked, this, &interfaceUser::open_applicaton);
	QObject::connect(this->createButton, &QPushButton::clicked, this, &interfaceUser::scroll_tutorials);
	QObject::connect(this->seeButton, &QPushButton::clicked, this, &interfaceUser::see_tutorials);

}
void interfaceUser::connect_new_buttons() {
	QObject::connect(this->addButton, &QPushButton::clicked, this, &interfaceUser::addtolist);
	QObject::connect(this->likeButton, &QPushButton::clicked, this, &interfaceUser::remove_tutorial_true);
	QObject::connect(this->dislikeButton, &QPushButton::clicked, this, &interfaceUser::remove_tutorial_false);
}



void interfaceUser::scroll_tutorials() {
	this->position = 0;
	QDialog* dialog = new QDialog{};
	this->nextButton = new QPushButton("NEXT");
	QObject::connect(this->nextButton, &QPushButton::clicked, this, &interfaceUser::display_next);
	this->addButton = new QPushButton("ADD");
	QVBoxLayout* main = new QVBoxLayout{};
	this->presenterLE = new QLineEdit();
	this->linkLE = new QLineEdit();
	this->likesLE = new QLineEdit();
	this->durationLE = new QLineEdit();
	this->titleLE = new QLineEdit();
	QPushButton* backButton = new QPushButton{ "Main Menu" };

	QDialog* presenter_dialog = new QDialog{};
	QLineEdit* presenter_searched = new QLineEdit(this);
	QFormLayout* presenter_layout = new QFormLayout(this);
	presenter_layout->addRow("What presenter you are looking for?", presenter_searched);
	presenter_dialog->setLayout(presenter_layout);
	connect(presenter_searched, &QLineEdit::returnPressed, presenter_dialog, &QDialog::accept);

	QFormLayout* tutorial_layout = new QFormLayout{};
	tutorial_layout->addRow("Title: ", this->titleLE);
	tutorial_layout->addRow("Presenter: ", this->presenterLE);
	tutorial_layout->addRow("Duration: ", this->durationLE);
	tutorial_layout->addRow("Likes: ", this->likesLE);
	tutorial_layout->addRow("Link: ", this->linkLE);
	dialog->setMinimumSize(512, 256);

	main->addLayout(tutorial_layout);

	main->addWidget(nextButton);
	main->addWidget(addButton);
	main->addWidget(backButton);
	main->addWidget(likeButton);
	main->addWidget(dislikeButton);
	QObject::connect(backButton, &QPushButton::clicked, this, [dialog] {
		//emit backToInterfaceRequested();
		dialog->close();

		});

	dialog->setLayout(main);

	dialog->show();
	if (presenter_dialog->exec() == QDialog::Accepted) {
		this->txt = presenter_searched->text();
		this->display_next();
	}
	this->connect_new_buttons();

}
interfaceUser::interfaceUser(Service& serv1, Watchlist* watch1, QWidget* parent) :serv{ serv1 }, watch{ watch1 }, QDialog{ parent }
{
	this->init_();
	this->connectSS();

}

void interfaceUser::open_applicaton()
{


	this->watch->set_data(this->serv.get_user_repo());
	this->watch->write();
	this->watch->read();

}

void interfaceUser::display_next() {
	string presenter = this->txt.toStdString();

	vector<Tutorial>elems = this->serv.filter_tutorials(presenter);
	if (elems.size() == 0) {
		QMessageBox::critical(this, "Error", "NO SUCH PRESENTER");

		return;
	}

	if (this->position == elems.size())
		this->position = 0;

	this->fillforms(elems);
	this->position += 1;

}
void interfaceUser::fillforms(vector < Tutorial >elems) {
	this->presenterLE->clear();
	this->linkLE->clear();
	this->likesLE->clear();
	this->durationLE->clear();
	this->titleLE->clear();
	Tutorial t = elems[this->position];
	this->presenterLE->setText(QString::fromStdString(t.get_presenter()));
	this->likesLE->setText(QString::fromStdString(to_string(t.get_likes())));
	this->durationLE->setText(QString::fromStdString(t.get_duration()));
	this->titleLE->setText(QString::fromStdString(t.get_title()));
	this->linkLE->setText(QString::fromStdString(t.get_link()));


	QUrl url(QString::fromStdString(t.get_link()));
	QDesktopServices::openUrl(url);
}

void interfaceUser::see_tutorials() {
	this->watchlistLW->clear();

	vector<Tutorial>elements = this->serv.get_user_repo();

	for (auto& element : elements)
	{
		this->watchlistLW->addItem(QString::fromStdString(element.get_title() + " " + element.get_presenter() + " " + element.get_duration() + " " + to_string(element.get_likes()) + " " + element.get_link()));
	}
	QDialog* printer = new QDialog{};
	QHBoxLayout* printer_layout = new QHBoxLayout{};
	printer_layout->addWidget(this->watchlistLW);
	printer->setLayout(printer_layout);
	printer->setMinimumSize(512, 256);
	printer->show();
}

void interfaceUser::hide_menu()
{
}


void interfaceUser::addtolist() {
	string presenter = this->txt.toStdString();

	vector<Tutorial>elems = this->serv.filter_tutorials(presenter);

	this->serv.add_user_s(elems[this->position - 1]);



}

void interfaceUser::remove_tutorial_true()
{
	string presenter = this->txt.toStdString();

	vector<Tutorial>elems = this->serv.filter_tutorials(presenter);

	this->serv.remove_user_s(elems[this->position - 1], true);

}

void interfaceUser::remove_tutorial_false() {
	string presenter = this->txt.toStdString();

	vector<Tutorial>elems = this->serv.filter_tutorials(presenter);
	this->serv.remove_user_s(elems[this->position - 1], false);

}

