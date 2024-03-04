#pragma once
#include <QMainWindow>
#include "qpushbutton.h"
#include "qmainwindow.h"
#include "qlabel.h"
#include "qdialog.h"
#include "interfaceAdmin.h"
#include "interfaceUser.h"

#include "../TemaSase/service.h"
#include "../TemaSase/watchlist.h"

class Interface :public QMainWindow
{
	Q_OBJECT
private:

	Service& serv;
	Watchlist* watchlist;
	void init_();
	void connectSS();
	QPushButton* AdminButton, * UserButton;
	QPushButton* HTMLButton, * CSVButton;
	QDialog* dialog;
	QWidget* widget;
	void on_HTML_button_clicked();
	void on_CSV_button_clicked();
	void on_ADMIN_button_clicked();
	void on_USER_button_clicked();

public:
	Interface(Service& serv1, QWidget* parent = nullptr);
public slots:
	void handleBackToInterfaceRequest();
};