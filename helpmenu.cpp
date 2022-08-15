#include "helpmenu.h"
#include "ui_helpmenu.h"
helpmenu::helpmenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helpmenu)
{
    ui->setupUi(this);
    this->setWindowTitle("说明界面");
}
helpmenu::~helpmenu()
{
    delete ui;
}
