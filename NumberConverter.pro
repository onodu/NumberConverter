#-------------------------------------------------
#
# Project created by QtCreator 2018-01-14T22:52:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NumberConverter
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14

# in order gcc not to warn
QMAKE_CXXFLAGS += -isystem$$[QT_INSTALL_HEADERS]\
	-isystemK:\1\0\source\boost_1_67_0


SOURCES += main.cpp\
		MainWindow.cpp\
		NumberConverter.cpp

HEADERS  += MainWindow.h\
		NumberConverter.h

FORMS    += MainWindow.ui


