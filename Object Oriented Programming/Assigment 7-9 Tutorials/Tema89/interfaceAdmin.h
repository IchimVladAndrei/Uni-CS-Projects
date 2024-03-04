#pragma once
#include <qdialog.h>
#include "../TemaSase/service.h"
#include "qpushbutton.h"
#include "qdialog.h"
#include "qwidget.h"
#include "qlineedit.h"
#include "qboxlayout.h"
#include "qlistwidget.h"
#include "qlabel.h"
#include "qformlayout.h"
#include "QtCharts/qchartview.h"
#include <QtCharts/QPieSeries>
#include "QtCharts/qpieseries.h"



class interfaceAdmin :public QDialog {
	Q_OBJECT
private:
	Service& serv;
	void init_();
	void connectSS();
	void populatelist();
	QPushButton* addButton, * removeButton, * updateButton, * print, * closeButton;
	QLineEdit* presenterLE, * titleLE, * likesLE, * linkLE, * durationLE;
	QListWidget* tutorialsPrint;
	/*QtCharts::QPieSeries* presenter_data;*/
public:
	interfaceAdmin(Service& serv1, QWidget* parent = nullptr);
	void add_admin_ui();
	void remove_admin_ui();
	void update_admin_ui();
	void onCloseButtonClicked();
	void plot_graph();

signals:
	void backToInterfaceRequested();

};

