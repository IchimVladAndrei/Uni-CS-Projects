#include "interfaceAdmin.h"
#include "../TemaSase/validator.h"
#include <QMessageBox>
#include <QToolTip>
#include "../TemaSase/exceptions.h"



void interfaceAdmin::init_()
{
	this->addButton = new QPushButton{ "Add" };
	this->removeButton = new QPushButton{ "Remove" };
	this->updateButton = new QPushButton{ "Update" };
	this->closeButton = new QPushButton{ "CLOSE" };
	this->tutorialsPrint = new QListWidget{};
	this->presenterLE = new QLineEdit();
	this->linkLE = new QLineEdit();
	this->likesLE = new QLineEdit();
	this->durationLE = new QLineEdit();
	this->titleLE = new QLineEdit();
	QVBoxLayout* layout = new QVBoxLayout(this);
	QGridLayout* buttons_layout = new QGridLayout();
	QFormLayout* tutorial_layout = new QFormLayout{};

	buttons_layout->addWidget(this->addButton, 0, 0);
	buttons_layout->addWidget(this->removeButton, 1, 0);
	buttons_layout->addWidget(this->updateButton, 2, 0);
	buttons_layout->addWidget(closeButton);
	QObject::connect(closeButton, &QPushButton::clicked, this, [this] {
		this->close();
		this->hide();
		emit backToInterfaceRequested();

		});
	tutorial_layout->addRow("Title: ", this->titleLE);
	tutorial_layout->addRow("Presenter: ", this->presenterLE);
	tutorial_layout->addRow("Duration: ", this->durationLE);
	tutorial_layout->addRow("Likes: ", this->likesLE);
	tutorial_layout->addRow("Link: ", this->linkLE);

	layout->addLayout(tutorial_layout);
	layout->addWidget(this->tutorialsPrint);
	layout->addLayout(buttons_layout);


}

void interfaceAdmin::connectSS()
{

	QObject::connect(this->addButton, &QPushButton::clicked, this, &interfaceAdmin::add_admin_ui);
	QObject::connect(this->removeButton, &QPushButton::clicked, this, &interfaceAdmin::remove_admin_ui);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &interfaceAdmin::update_admin_ui);

}

void interfaceAdmin::onCloseButtonClicked() {
	this->hide();
	QWidget* parent = this->parentWidget();
	parent->showNormal();

}



void interfaceAdmin::populatelist()
{
	this->tutorialsPrint->clear();
	vector<Tutorial> elements = this->serv.get_repo();
	for (auto& element : elements)
		this->tutorialsPrint->addItem(QString::fromStdString(element.get_title() + " " + element.get_presenter() + " " + element.get_duration() + " " + to_string(element.get_likes()) + " " + element.get_link()));
}

interfaceAdmin::interfaceAdmin(Service& serv1, QWidget* parent) :serv{ serv1 }, QDialog{ parent }
{
	this->setParent(parent);
	this->init_();
	this->populatelist();
	this->connectSS();
}

void interfaceAdmin::add_admin_ui()
{
	string title = this->titleLE->text().toStdString();
	string presenter = this->presenterLE->text().toStdString();
	string duration = this->durationLE->text().toStdString();
	string link = this->linkLE->text().toStdString();
	string likes = this->likesLE->text().toStdString();

	if (!Validator::validate_title(title) || !Validator::validate_presenter(presenter)
		|| !Validator::validate_duration(duration) || !Validator::validate_likes(stoi(likes))
		|| !Validator::validate_link(link))
	{
		QMessageBox::critical(this, "Error", "Input validation error");
		return;
	}
	else {
		try {
			this->serv.add_s(title, presenter, duration, stoi(likes), link);

		}
		catch (...) {
			QMessageBox::critical(this, "Error", "The item couldn't be added");
			return;
		}
	}
	this->populatelist();

}

void interfaceAdmin::remove_admin_ui()
{
	string title = this->titleLE->text().toStdString();

	string link = this->linkLE->text().toStdString();

	if (!Validator::validate_title(title) || !Validator::validate_link(link))
	{

		QMessageBox::critical(this, "Error", "Input validation error");
		return;

	}
	else {

		try {
			this->serv.remove_s(title, link);
		}
		catch (RepoExceptions) {
			QMessageBox::critical(this, "Error", "The item couldn't be deleted");
			return;
		}



	}
	this->populatelist();
}

void interfaceAdmin::update_admin_ui()
{



	string title = this->titleLE->text().toStdString();
	string n_presenter = this->presenterLE->text().toStdString();
	string n_duration = this->durationLE->text().toStdString();
	string link = this->linkLE->text().toStdString();
	string n_likes = this->likesLE->text().toStdString();
	if (!Validator::validate_title(title) || !Validator::validate_presenter(n_presenter)
		|| !Validator::validate_duration(n_duration) || !Validator::validate_likes(stoi(n_likes))
		|| !Validator::validate_link(link)) {
		QMessageBox::critical(this, "Error", "Input validation error");
		return;
	}
	else {
		try {
			this->serv.update_s(title, n_presenter, n_duration, stoi(n_likes), link);
		}
		catch (...) {
			QMessageBox::critical(this, "Error", "The item couldn't be updated");
		}
	}
	this->populatelist();
}

void interfaceAdmin::plot_graph()
{
	QDialog* graphs = new QDialog{};
	QHBoxLayout* main_layout = new QHBoxLayout{};


}