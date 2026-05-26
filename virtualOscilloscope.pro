#------------------------------------------------------------------------------------------------------------------------------
#                   __     ___      _               _     ___           _ _ _                                
#                   \ \   / (_)_ __| |_ _   _  __ _| |   / _ \ ___  ___(_) | | ___  ___  ___ ___  _ __   ___ 
#                    \ \ / /| | '__| __| | | |/ _` | |  | | | / __|/ __| | | |/ _ \/ __|/ __/ _ \| '_ \ / _ \
#                     \ V / | | |  | |_| |_| | (_| | |  | |_| \__ \ (__| | | | (_) \__ \ (_| (_) | |_) |  __/
#                      \_/  |_|_|   \__|\__,_|\__,_|_|   \___/|___/\___|_|_|_|\___/|___/\___\___/| .__/ \___|
#                                                                                                |_|
#
# File:   virtualOscilloscope.pro
#
# Author: Silvano Catinella <catinella@yahoo.com>
#
# Description:
#	This file must be processed with qmake6 QT tool. It will generate you the Makefile you need to build the source code
#
#-------------------------------------------------------------------------------------------------------------------------------

QT += widgets gui
#include <QApplication>

CONFIG += c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = virtualOscilloscope

SOURCES += \
	main.cpp \
	mainWindow.cpp \
	plotBox.cpp

HEADERS += \
	mainWindow.hpp \
	plotBox.hpp

cleanall.target = cleanall
cleanall.depends = clean
cleanall.commands = rm -fv $$OUT_PWD/$$TARGET

QMAKE_EXTRA_TARGETS += cleanall
