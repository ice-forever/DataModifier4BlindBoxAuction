#程序版本
#VERSION = 1.0
#程序图标
RC_ICONS = appico.ico
#程序说明
QMAKE_TARGET_DESCRIPTION = 为盲盒拍卖会设计和开发的游戏数据修改器。项目地址https://github.com/ice-forever/DataModifier4BlindBoxAuction
#程序名称
QMAKE_TARGET_PRODUCT = 盲盒拍卖会数据修改器
#程序语言
#0x0800代表和系统当前语言一致
RC_LANG = 0x0800

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    helpmenu.cpp \
    main.cpp \
    modmenu.cpp

HEADERS += \
    helpmenu.h \
    modmenu.h

FORMS += \
    helpmenu.ui \
    modmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


