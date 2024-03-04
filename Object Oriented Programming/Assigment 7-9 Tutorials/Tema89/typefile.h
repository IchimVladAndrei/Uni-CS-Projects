#pragma once
#include <qdialog.h>
#include "qpushbutton.h"
#include "../TemaSase/service.h"
class Typefile :public QDialog {
private:
	Service& serv;
	void init_();
	void conncectSignalsAndSlots();
	QPushButton* HTMLButton, * CSVButton;
public:
	Typefile(Service& serv1, QWidget* parent = nullptr);
	//becareful
};