#pragma once
#include <qdialog.h>
#include "../TemaSase/service.h"
#include "../TemaSase/watchlist.h"
#include "../TemaSase/watchlistHTML.h"
#include "../TemaSase/watchlistCSV.h"
#include "qpushbutton.h"
#include "qwidget.h"
#include "qdialog.h"
#include "qlistwidget.h"
#include "../TemaSase/exceptions.h"

class interfaceUser :public QDialog {
	Q_OBJECT
private:
	int position;
	Service& serv;
	Watchlist* watch;
	QString txt;
	void init_();
	void connectSS();
	void connect_new_buttons();
	QPushButton* seeButton, * createButton, * openButton;
	QPushButton* addButton, * nextButton;
	QPushButton* likeButton = new QPushButton{ "Liked it" };
	QPushButton* dislikeButton = new QPushButton{ "Not liked it" };
	QListWidget* seeingLW, * watchlistLW;
	QLineEdit* presenterLE, * titleLE, * likesLE, * linkLE, * durationLE;
	QWidget* mainWidget;

public:
	void scroll_tutorials();
	interfaceUser(Service& serv1, Watchlist* watch1, QWidget* parent = nullptr);
	~interfaceUser() {};
	void fillforms(vector < Tutorial >elems);
	void open_applicaton();
	void display_next();
	void see_tutorials();
	static void hide_menu();
	void addtolist();
	void remove_tutorial_true();
	void remove_tutorial_false();
	void remove_tutorial();
signals:
	void backToInterfaceRequested();
};