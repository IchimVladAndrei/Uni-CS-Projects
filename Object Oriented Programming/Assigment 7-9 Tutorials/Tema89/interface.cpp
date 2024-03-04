#include "interface.h"
#include "../TemaSase/watchlistCSV.h"
#include "../TemaSase/watchlistHTML.h"
#include <QVBoxLayout>
void Interface::init_()
{
	widget = new QWidget();
	QHBoxLayout* layout = new QHBoxLayout();

	this->dialog = new QDialog();


	dialog->setWindowModality(Qt::WindowModal);
	dialog->setMinimumHeight(240);
	dialog->setMinimumWidth(320);


	QLabel* typefile = new QLabel();
	typefile->setText("In what format you want to save the file:");

	typefile->setParent(dialog);
	QFont text_font{ "Arial",12 };
	typefile->setFont(text_font);
	typefile->show();

	QHBoxLayout* layout_type_files = new QHBoxLayout{ this };
	this->HTMLButton = new QPushButton{ "HTML format" };
	this->CSVButton = new QPushButton{ "CSV format" };
	this->HTMLButton->setParent(dialog);
	this->CSVButton->setParent(dialog);

	layout->addWidget(this->HTMLButton);
	layout->addWidget(this->CSVButton);
	layout->addWidget(typefile);


	this->dialog->setWindowTitle("File format selection");

	QFont buttons_type_files{ "Arial",12 };
	layout_type_files->addWidget(typefile);
	layout_type_files->addWidget(this->CSVButton);
	layout_type_files->addWidget(this->HTMLButton);
	dialog->setLayout(layout_type_files);


	QVBoxLayout* mainlayout = new QVBoxLayout();

	widget->setMinimumHeight(640);
	widget->setMinimumWidth(480);

	this->AdminButton = new QPushButton{ "Admin Mode" };
	this->UserButton = new QPushButton{ "User Mode" };
	this->AdminButton->setParent(widget);
	this->UserButton->setParent(widget);
	this->AdminButton->setFont(buttons_type_files);
	this->UserButton->setFont(buttons_type_files);


	QLabel* question = new QLabel();
	question->setText("As who you want to use the application?");
	question->setFont(text_font);
	question->setParent(widget);
	mainlayout->setSpacing(20);
	mainlayout->addWidget(question);
	mainlayout->addWidget(this->AdminButton);
	mainlayout->addWidget(this->UserButton);
	question->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	mainlayout->setAlignment(Qt::AlignCenter);
	widget->setWindowTitle("User selection");
	widget->setLayout(mainlayout);
	widget->setMinimumSize(512, 256);
	setCentralWidget(widget);
	widget->setDisabled(true);
	dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
	dialog->setMinimumSize(512, 256);
	dialog->show();

}


void Interface::connectSS()
{
	QObject::connect(this->CSVButton, &QPushButton::clicked, this, &Interface::on_CSV_button_clicked);
	QObject::connect(this->HTMLButton, &QPushButton::clicked, this, &Interface::on_HTML_button_clicked);
	QObject::connect(this->AdminButton, &QPushButton::clicked, this, &Interface::on_ADMIN_button_clicked);
	QObject::connect(this->UserButton, &QPushButton::clicked, this, &Interface::on_USER_button_clicked);


}



void Interface::on_HTML_button_clicked()
{
	this->dialog->close();
	this->widget->setDisabled(false);
	this->watchlist = new WatchlistHTML();

}

void Interface::on_CSV_button_clicked()
{
	this->dialog->close();
	this->widget->setDisabled(false);
	this->watchlist = new WatchlistCSV();

}

void Interface::on_ADMIN_button_clicked()
{
	this->close();
	interfaceAdmin* admin = new interfaceAdmin{ serv,this->widget };
	connect(admin, &interfaceAdmin::backToInterfaceRequested, this, &Interface::handleBackToInterfaceRequest);

	admin->showNormal();
}

void Interface::on_USER_button_clicked()
{
	this->close();
	interfaceUser* user = new interfaceUser{ serv,this->watchlist };
	connect(user, &interfaceUser::backToInterfaceRequested, this, &Interface::handleBackToInterfaceRequest);

	user->showNormal();
}
void Interface::handleBackToInterfaceRequest() {
	show();
}
Interface::Interface(Service& serv1, QWidget* parent) :serv{ serv1 }, QMainWindow{ parent }

{
	this->init_();
	this->connectSS();
}
