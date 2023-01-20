#ifndef MODMENU_H
#define MODMENU_H

#include <QWidget>
#include <QMainWindow>
#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QTextCodec>
#include <QFile>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QVector>
#include <QStandardItemModel>
#include <QDebug>
#include <QString>
#include <QtAlgorithms>
#include <QDateTime>
#include "helpmenu.h"

namespace Ui {
class MODmenu;
}

class MODmenu : public QWidget
{
    Q_OBJECT

public:
    explicit MODmenu(QWidget *parent = nullptr);
    ~MODmenu();
    void flashtablefromvector();
    int uidFindLocation(qlonglong uid);
    void savejson();
    void checkfirstrun();
    helpmenu *help;
private slots:
void on_datatable_cellChanged(int row, int column);
void on_inputname_textChanged(const QString &arg1);


void on_changescoreButton_clicked();

void on_pushButton_2_clicked();

void on_addscore_textChanged(const QString &arg1);

void on_changescore_textChanged(const QString &arg1);

void on_pushButton_clicked();

void on_readfile_clicked();

void on_writefile_clicked();

void on_calculate_clicked();

void on_inputdataba_clicked();

void on_help_clicked();
private:
    Ui::MODmenu *ui;
};
int jietijiesuan(int source);
#endif // MODMENU_H
