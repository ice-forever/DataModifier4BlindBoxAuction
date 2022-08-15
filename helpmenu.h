#ifndef HELPMENU_H
#define HELPMENU_H
#include <QWidget>
namespace Ui {
class helpmenu;
}

class helpmenu : public QWidget
{
    Q_OBJECT

public:
    explicit helpmenu(QWidget *parent = nullptr);
    ~helpmenu();

private:
    Ui::helpmenu *ui;
};

#endif // HELPMENU_H
