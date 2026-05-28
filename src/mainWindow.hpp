/*------------------------------------------------------------------------------------------------------------------------------
//                   __     ___      _               _     ___           _ _ _                                
//                   \ \   / (_)_ __| |_ _   _  __ _| |   / _ \ ___  ___(_) | | ___  ___  ___ ___  _ __   ___ 
//                    \ \ / /| | '__| __| | | |/ _` | |  | | | / __|/ __| | | |/ _ \/ __|/ __/ _ \| '_ \ / _ \
//                     \ V / | | |  | |_| |_| | (_| | |  | |_| \__ \ (__| | | | (_) \__ \ (_| (_) | |_) |  __/
//                      \_/  |_|_|   \__|\__,_|\__,_|_|   \___/|___/\___|_|_|_|\___/|___/\___\___/| .__/ \___|
//                                                                                                |_|
//
// File:   mainWindow.hpp
//
// Author: Silvano Catinella <catinella@yahoo.com>
//
// Description:
//    The mainWindow object is responsible for data processing:
//      - loading CSV data
//      - selecting visible samples
//      - applying X/Y scaling and transformations
//      - converting samples into screen coordinates
//
//    The plotBox object acts only as a graphical renderer. It receives a vector of already processed points and is
//	responsible exclusively for displaying them.
//
// Data flow:
//
//    CSV data
//       ↓
//    mainWindow (processing / scaling / selection)
//       ↓
//    QVector<QPointF> visiblePoints
//       ↓
//    plotBox (rendering)
//       ↓
//    Screen
//
//
------------------------------------------------------------------------------------------------------------------------------*/

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QVector>
#include <QMainWindow>
#include <plotBox.hpp>
#include <QDial>
#include <QScrollBar>
#include <QListWidget>

#define CSVFIELDSPLITTER ','

static const std::array<QColor, 8> channelColors = {
	QColor(255, 255,   0),   // yellow
	QColor(  0, 255,   0),   // lime
	QColor(  0, 255, 255),   // cyan
	QColor(255,   0, 255),   // magenta
	QColor(255, 128,   0),   // orange
	QColor(255, 255, 255),   // white
	QColor(128, 255, 128),   // light green
	QColor(255, 128, 128)    // light red
};

class QWidget;
class QAction;

class mainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit mainWindow(QWidget *parent = nullptr);
	~mainWindow() override = default;
	
private:
	void createMenus();
	void createToolBar();
	void createCentralWidget();
	void createStatusBar();
	bool sendDataToDisplay();

	QScrollBar               *xScrollBar    = nullptr;
	unsigned int             scrollPos      = 0;
	QDial                    *xScaleDial    = nullptr;
	QDial                    *yScaleDial    = nullptr;
	QAction                  *openCsvAction = nullptr;
	QAction                  *exitAction    = nullptr;
	QVector<QVector<double>> dataPool       = {};
	plotBox                  *plot          = nullptr;
	QStringList              channelNames   = {};
	QListWidget              *signalsList   = nullptr;
	QVector<bool>            channelEnabled = {};

private slots:
	void openCsv();
};

#endif
