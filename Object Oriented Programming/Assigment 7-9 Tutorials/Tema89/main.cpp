
#include <QtWidgets/QApplication>
#include "../TemaSase/repo.h"
#include "../TemaSase/service.h"
#include "../TemaSase/domain.h"
#include "interface.h"
#include "interfaceAdmin.h"
#include "interfaceUser.h"
#include "typefile.h"
#include "../TemaSase/fileRepo.h"
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication::setFont(QFont("Arial", 12));
	Repo user_repos;
	FileRepo repos(R"(C:\Users\potat\Documents\TemaSase\tutoriale.txt)");
	Service serv(repos, user_repos);
	//Tema89 w;
	//w.show();
	Interface gui{ serv };
	gui.show();
	return a.exec();
}


