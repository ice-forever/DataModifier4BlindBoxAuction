#include "modmenu.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MODmenu w;
    w.setWindowTitle("盲盒拍卖会数据修改器 Github版");
    w.show();
    a.setWindowIcon(QIcon("myappico.ico"));
    return a.exec();
}
