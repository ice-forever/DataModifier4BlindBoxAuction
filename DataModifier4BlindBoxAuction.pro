#����汾
#VERSION = 1.0
#����ͼ��
RC_ICONS = appico.ico
#����˵��
QMAKE_TARGET_DESCRIPTION = Ϊä����������ƺͿ�������Ϸ�����޸�������Ŀ��ַhttps://github.com/ice-forever/DataModifier4BlindBoxAuction
#��������
QMAKE_TARGET_PRODUCT = ä�������������޸���
#��������
#0x0800�����ϵͳ��ǰ����һ��
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


