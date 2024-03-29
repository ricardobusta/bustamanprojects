#-------------------------------------------------
#
# Project created by QtCreator 2012-03-24T10:12:36
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = QtCharacterMaker
TEMPLATE = app


SOURCES += \
    view/mainwindow.cpp \
    main.cpp \
    view/canvaswidget.cpp \
    qtcharactermaker.cpp \
    view/actions.cpp \
    view/options.cpp \
    view/canvaswidgetcontainer.cpp \
    view/editimagewidget.cpp \
    view/setcursorsizedialog.cpp \
    view/newimagefiledialog.cpp \
    view/colorpalettewidget.cpp \
    view/splashscreenwidget.cpp

HEADERS  += \
    view/mainwindow.h \
    view/canvaswidget.h \
    qtcharactermaker.h \
    view/actions.h \
    view/options.h \
    translations/tokens.h \
    view/canvaswidgetcontainer.h \
    view/editimagewidget.h \
    view/setcursorsizedialog.h \
    view/newimagefiledialog.h \
    view/colorpalettewidget.h \
    view/splashscreenwidget.h

FORMS    += \
    view/mainwindow.ui \
    view/setcursorsizedialog.ui \
    view/newimagefiledialog.ui

TRANSLATIONS += \
    translations/tokens_enus.ts \
    translations/tokens_ptbr.ts

RESOURCES += \
    translations/translations.qrc \
    icons/icons.qrc \
    images/images.qrc

