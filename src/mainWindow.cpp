/*------------------------------------------------------------------------------------------------------------------------------
//                   __     ___      _               _     ___           _ _ _                                
//                   \ \   / (_)_ __| |_ _   _  __ _| |   / _ \ ___  ___(_) | | ___  ___  ___ ___  _ __   ___ 
//                    \ \ / /| | '__| __| | | |/ _` | |  | | | / __|/ __| | | |/ _ \/ __|/ __/ _ \| '_ \ / _ \
//                     \ V / | | |  | |_| |_| | (_| | |  | |_| \__ \ (__| | | | (_) \__ \ (_| (_) | |_) |  __/
//                      \_/  |_|_|   \__|\__,_|\__,_|_|   \___/|___/\___|_|_|_|\___/|___/\___\___/| .__/ \___|
//                                                                                                |_|
//      
// File:   mainWindow.cpp
//
// Author: Silvano Catinella <catinella@yahoo.com>
//
// Description:
//
//
------------------------------------------------------------------------------------------------------------------------------*/
#include "mainWindow.hpp"
#include "plotBox.hpp"

#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDial>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QDebug>

//------------------------------------------------------------------------------------------------------------------------------
//                                       P R I V A T E   F U N C T I O N S
//------------------------------------------------------------------------------------------------------------------------------
static bool _rowToVect (QVector<double> &codedRow, const QString &sourceRow) {
	//
	// Description:
	//	This private function convert a CVS row in a vector of floating point numbers
	//
	// Returned data:
	//	true    The data have been correctly converted
	//    false   Corrupted source data
	//
	static const QRegularExpression regex(R"(^[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$)");
	QStringList                     fieldsList = sourceRow.split(CSVFIELDSPLITTER);
	QString                         tmp("");
	bool                            out = true;
	
	codedRow.clear();
	for (const QString &field : fieldsList) {
		tmp = field.trimmed();               // Space characters removing
		if (regex.match(field).hasMatch()) {
			//qDebug() << field << "is a number \n";
			codedRow.append(field.toDouble());
		} else {
			out = false;
			break;
		}
	}

	return(out);
}


static QVector<double> _yRescale (QVector<double> data, double scale) {
	QVector<double> out;
	out.clear();
	for (unsigned int t=0; t<data.size(); t++)
		out.append(data[t] * scale);
	return(out);
}


static QVector<QVector<double>> _paddingPoints (QVector<double> y0, QVector<double> y1, unsigned int nop) {
	//
	// Description:
	//	This function is used to add points in the signal reppresentation
	//
	QVector<float> m;
	QVector<double> slice;
	QVector<QVector<double>> out;
	
	out.clear();
	m.clear();
	
	// Linear factor calculating
	for (uint8_t ch = 0; ch < y0.size(); ch++) 
		m.append((y1[ch] - y0[ch]) / nop);
	
	// Padding points generating...
	for (unsigned int t=0; t < nop; t++) {
		slice.clear();
		for (uint8_t ch = 0; ch < y0.size(); ch++) 
			slice.append((y0[ch] + t * m[ch]));
		out.append(slice);
	}
	return(out);
}
//------------------------------------------------------------------------------------------------------------------------------
//                                        P U B L I C   M E T H O D S
//------------------------------------------------------------------------------------------------------------------------------

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent) {
	setWindowTitle("CSV Scope");
	resize(1000, 700);

	{
		openCsvAction = new QAction("Open CSV", this);
		exitAction    = new QAction("Exit", this);
		connect(openCsvAction, &QAction::triggered, this, &mainWindow::openCsv);
	}
	
	createMenus();
	createToolBar();
	createCentralWidget();
	createStatusBar();
	
	// Zoom selectors linking
	connect(yScaleDial, &QDial::valueChanged, this, &mainWindow::sendDataToDisplay);
	connect(xScaleDial, &QDial::valueChanged, this, &mainWindow::sendDataToDisplay);
	
	// Display resizing event management
	connect(plot, &plotBox::resized, this, &mainWindow::sendDataToDisplay);
	
	// Display scrolling management
	connect(
		xScrollBar, &QScrollBar::valueChanged, this, [this](int value) {
			scrollPos = value;
			sendDataToDisplay();
        	}
	);
}

//------------------------------------------------------------------------------------------------------------------------------
//                                        P R I V A T E   M E T H O D S
//------------------------------------------------------------------------------------------------------------------------------

void mainWindow::createMenus() {
	QMenu *fileMenu = menuBar()->addMenu("File");

	fileMenu->addAction(openCsvAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
}

void mainWindow::createToolBar() {
	QToolBar *toolbar = addToolBar("Main toolbar");

	toolbar->addAction(openCsvAction);
}

/*
void mainWindow::createCentralWidget() {
	//
	// Description:
	//	it creates the oscilloscope's display
	//
	QWidget *central = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(central);
	
	plot = new plotBox(central);
	
	QWidget *controls = new QWidget(central);
	QHBoxLayout *ctrlLayout = new QHBoxLayout(controls);
	
	xScaleDial = new QDial(controls);
	xScaleDial->setRange(1,100);
	xScaleDial->setValue(10);
	
	yScaleDial = new QDial(controls);
	yScaleDial->setRange(1,100);
	yScaleDial->setValue(10);
	
	ctrlLayout->addWidget(new QLabel("X scale"));
	ctrlLayout->addWidget(xScaleDial);
	
	ctrlLayout->addStretch();   // spazio
	
	ctrlLayout->addWidget(new QLabel("Y scale"));
	ctrlLayout->addWidget(yScaleDial);
	
	layout->addWidget(plot, 4);     // display
	layout->addWidget(controls, 1); // pannello basso
	
	xScrollBar = new QScrollBar(Qt::Horizontal, controls);
	xScrollBar->setMinimum(0);
	xScrollBar->setMaximum(0);
	xScrollBar->setValue(0);
	ctrlLayout->addWidget(xScrollBar);
}
*/

void mainWindow::createCentralWidget() {
	QWidget     *central = new QWidget(this);
	QVBoxLayout *layout  = new QVBoxLayout(central);

	plot = new plotBox(central);

	QWidget     *controls       = new QWidget(central);
	QVBoxLayout *controlsLayout = new QVBoxLayout(controls);
	QHBoxLayout *dialLayout     = new QHBoxLayout();

	xScrollBar = new QScrollBar(Qt::Horizontal, controls);
	xScrollBar->setMinimum(0);
	xScrollBar->setMaximum(0);
	xScrollBar->setValue(0);

	xScaleDial = new QDial(controls);
	xScaleDial->setRange(1, 100);
	xScaleDial->setValue(50);

	yScaleDial = new QDial(controls);
	yScaleDial->setRange(1, 100);
	yScaleDial->setValue(50);

	signalsList = new QListWidget(controls);
	signalsList->setMinimumWidth(160);
	signalsList->setMaximumHeight(90);

	signalsList->setStyleSheet(
		"background-color: rgb(30,30,30);"
		"color: rgb(220,220,220);"
		"border: 1px solid rgb(60,60,60);"
		"selection-background-color: rgb(70,70,70);"
	);

	controlsLayout->addWidget(xScrollBar);
	controlsLayout->addLayout(dialLayout);

	dialLayout->addWidget(new QLabel("X scale", controls));
	dialLayout->addWidget(xScaleDial);

	dialLayout->addStretch();

	//dialLayout->addWidget(signalsList);
	QVBoxLayout *signalsLayout = new QVBoxLayout();
	signalsLayout->addSpacing(30);
	signalsLayout->addWidget(signalsList);
	dialLayout->addLayout(signalsLayout);

	dialLayout->addStretch();

	dialLayout->addWidget(new QLabel("Y scale", controls));
	dialLayout->addWidget(yScaleDial);

	layout->addWidget(plot, 4);
	layout->addWidget(controls, 1);

	setCentralWidget(central);
}
void mainWindow::createStatusBar() {
	statusBar()->showMessage("Ready");
}

bool mainWindow::sendDataToDisplay() {
	//
	// Description:
	//	This method consider the X and Y scale, the display size, then send the representable data to the (plotBox)
	//	virtual device's display
	//
	// Returned data:
	//	false   Not available data to display
	//	true    Data have been correctlty sent to the display
	//
	bool status = false;
	if (dataPool.size() > 0) {
		QVector<QVector<double>> subSet, tmpSet;
		double             xScale = std::pow(100.0, ((double)xScaleDial->value() - 50)/50);
		double             yScale = std::pow(100.0, ((double)yScaleDial->value() - 50)/50);
		const unsigned int maxDrawablePoints = plot->width();
		bool               end = false;
		unsigned int       t = scrollPos;
		
		subSet.clear();
		tmpSet.clear();
		
		while (subSet.size() < maxDrawablePoints && end == false) {
			if (xScale >= 1.0) {
				if ((t * xScale) < dataPool.size()) {
					subSet.append(_yRescale(dataPool[round(t * xScale)], yScale));
				} else
					end = true;
					
			} else if (t == 0) {
				subSet.append(_yRescale(dataPool[0], yScale));
				
			} else {
				tmpSet = _paddingPoints(dataPool[t-1], dataPool[t], round(1/xScale));
				for (QVector<QVector<double>>::iterator it = tmpSet.begin(); it < tmpSet.end(); it++)
					subSet.append(_yRescale(*it, yScale));
			}
			t++;
			
		}
		
		plot->setDataPool(subSet);

		status = true;
	}
	return(status);
}
//------------------------------------------------------------------------------------------------------------------------------
//                                                    S L O T S
//------------------------------------------------------------------------------------------------------------------------------

void mainWindow::openCsv() {
	//
	// Description:
	//	This is the action associated to the "open-csv" button.
	//
	QString fileName = QFileDialog::getOpenFileName(this, "Open CSV file", QString(), "CSV files (*.csv);;All files (*)" );
	
	if (fileName.isEmpty() == false) {
		QFile file(fileName);
		//qDebug() << __FUNCTION__ << "(" << __LINE__ << "): " << fileName;

		if (file.open(QIODevice::ReadOnly | QIODevice::Text) == false) {
			QString tmp = "I cannot open the " + fileName + "file";
			QMessageBox::warning(this, "ERROR!", tmp);

		} else {
			QVector<double> csvItem;
			QTextStream     in(&file);
			uint8_t         numOfFields = 0;
			bool            err = false;
			QString         rowString("");
			bool            flineFlag = true;

			// Old data removing...
			dataPool.clear();
			channelNames.clear();
			
			while (in.atEnd() == false) {
				rowString = in.readLine();
				if (_rowToVect (csvItem, rowString)) {
					// Dtata collecting
					if (numOfFields == 0 || numOfFields == csvItem.size()) {
						numOfFields = csvItem.size();
						dataPool.append(csvItem);
						xScrollBar->setMaximum(std::max(0, (int)dataPool.size() - plot->width()));
					}
					if (flineFlag) {
						for (uint8_t x = 0; x < csvItem.size(); x++)
							channelNames << QString("Field-") + QString::number(x);
					}

				} else if (flineFlag) {
					// Field names recording
					channelNames = rowString.split(",");
					qDebug() << "Found labels: " << channelNames << "\n";

				} else {
					// ERROR!
					qDebug() << "-->" << rowString;
					QMessageBox::warning(this, "ERROR!", "Corrupted data");
					err = true;
				}
				flineFlag = false;
			}

			if (err == false) {
				QListWidgetItem *item = nullptr;
				QColor          color;

				statusBar()->showMessage("Loaded: " + fileName);
				QMessageBox::information(this, "CSV selected", fileName);
				sendDataToDisplay();

				signalsList->clear();

				for (int i = 0; i < channelNames.size(); ++i) {
					item = new QListWidgetItem(channelNames[i]);
					item->setForeground(channelColors[i]);
					signalsList->addItem(item);
				}
			}
		}
	}
}


