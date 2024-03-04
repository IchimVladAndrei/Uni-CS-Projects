#include "typefile.h"
#include "qlabel.h"
#include "qlayout.h"
#include "../TemaSase/service.h"
void Typefile::init_()
{
}

void Typefile::conncectSignalsAndSlots()
{
}

Typefile::Typefile(Service& serv1, QWidget* parent) :serv{ serv1 }, QDialog{ parent }
{
	this->init_();
	this->conncectSignalsAndSlots();
}
