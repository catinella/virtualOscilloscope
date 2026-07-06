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
#	Customized rules:
#		cleanall   It cleans all dinamically created files except Makefile
#		install    It install the application executable file in your system
#		uninstall  It removes the file from your system
#
#-------------------------------------------------------------------------------------------------------------------------------

QT += widgets gui
#include <QApplication>

CONFIG += c++17
CONFIG -= app_bundle
GDB = $$(GDB)

equals(GDB, 1) {
	message("*** DEBUG BUILD ***")
	CONFIG += debug
	CONFIG -= release
	QMAKE_CXXFLAGS += -g -O0
	QMAKE_CFLAGS   += -g -O0
} else {
	message("*** RELEASE BUILD ***")
	CONFIG -= debug
	CONFIG += release
	QMAKE_CXXFLAGS += -O2
	QMAKE_CFLAGS   += -O2
}

TEMPLATE = app
TARGET = virtualOscilloscope

PREFIX = /usr/local

SOURCES += main.cpp mainWindow.cpp plotBox.cpp refsBar.cpp plotArea.cpp

HEADERS += mainWindow.hpp plotBox.hpp refsBar.hpp plotArea.hpp

cleanall.target   = cleanall
cleanall.depends  = clean
cleanall.commands = rm -fv $$OUT_PWD/$$TARGET Makefile

install.target   = install
install.depends  = $$TARGET
install.commands = install --verbose --mode 555 --own root $$TARGET $$PREFIX/bin

uninstall.target   = uninstall
uninstall.depends  = 
uninstall.commands = rm -fv $$PREFIX/bin/$$TARGET

QMAKE_EXTRA_TARGETS += cleanall install uninstall
