QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cpp \
    model/calculator.cpp \
    model/model.cpp \
    model/model_graph.cpp \
    model/parcer.cpp \
    view/dialog.cpp \
    view/main.cpp \
    view/mainwindow.cpp \
    qcustomplot.cpp \


HEADERS += \
    common/calc_exception.h \
    common/operations_list.h \
    controller/controller.h \
    model/calculator.h \
    model/model.h \
    model/model_graph.h \
    model/parcer.h \
    model/tokens_list.h \
    view/dialog.h \
    view/mainwindow.h \
    qcustomplot.h \


FORMS += \
    view/dialog.ui \
#    view/graphwindow.ui \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
