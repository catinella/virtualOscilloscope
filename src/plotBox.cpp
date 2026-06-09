/*------------------------------------------------------------------------------------------------------------------------------
//                   __     ___      _               _     ___           _ _ _                                
//                   \ \   / (_)_ __| |_ _   _  __ _| |   / _ \ ___  ___(_) | | ___  ___  ___ ___  _ __   ___ 
//                    \ \ / /| | '__| __| | | |/ _` | |  | | | / __|/ __| | | |/ _ \/ __|/ __/ _ \| '_ \ / _ \
//                     \ V / | | |  | |_| |_| | (_| | |  | |_| \__ \ (__| | | | (_) \__ \ (_| (_) | |_) |  __/
//                      \_/  |_|_|   \__|\__,_|\__,_|_|   \___/|___/\___|_|_|_|\___/|___/\___\___/| .__/ \___|
//                                                                                                |_|
//
// File:   plotBox.cpp
//
// Author: Silvano Catinella <catinella@yahoo.com>
//
// Description:
//	This class manage the Oscilloscope's display components: the main display, the X references bar and Y references bar
//
//		+-----+----------------------------------+
//		| +2  |-+-----+-----+-----+-----+-----+--|
//		|     | |     |     |     |     |     |  |
//		| +1  |-+-----+-----+-----+-----+-----+--|
//		|     | |     |     |     |     |     |  |
//		|  0  |-+-----+---(plotArea)----+-----+--|	
//		|     | |     |     |     |     |     |  |	
//		| -1  |-+-----+-----+-----+-----+-----+--|	
//		|     | |     |     |     |     |     |  |	
//		| -2  |-+-----+-----+-----+-----+-----+--|
//		+========================================+
//		|     | 00    01    02    03    04    05 |
//		+----------------------------------------+
//
//
//
// License:  LGPL ver 3.0
//
// 		This script is a free software; you can redistribute it and/or modify it under the terms	of the GNU
// 		Lesser General Public License as published by the Free Software Foundation; either version 3.0 of the License,
// 		or (at your option) any later version. 
//
//		For further details please read the full LGPL text file [https://www.gnu.org/licenses/lgpl-3.0.txt].
// 		You should have received a copy of the GNU General Public License along with this file; if not, write to the 
//
//			Free Software Foundation, Inc.,
//			59 Temple Place, Suite 330,
//			Boston, MA  02111-1307  USA
//
//
//
//                                                                                                               cols=128 tab=6
------------------------------------------------------------------------------------------------------------------------------*/
#include "plotBox.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPainter>
#include <mainWindow.hpp>

plotBox::plotBox(QWidget *parent) : QWidget(parent) {
	QHBoxLayout           *layout  = new QHBoxLayout(this);
	QVector<unsigned int> rows     = {};
	QVector<unsigned int> columns  = {};

	yBar  = new refsBar(refsBar::VERTICAL, this);
	//xBar  = new refsBar(refsBar::HORIZONTAL, this);
	pArea = new plotArea(this);

	connect(pArea, &plotArea::gridReady,
        this, [this](QVector<unsigned int> rows, QVector<unsigned int> columns) {
            yBar->setRefsPos(rows);
            //xBar->setRefsPos(columns);
      });
        
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	pArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	layout->addWidget(yBar);
	layout->addWidget(pArea, 1);
	
	pArea->rebuildGrid();

	setLayout(layout);
}

void plotBox::setDataPool (QVector<QVector<double>> &visibleData, QVector<bool> sigSelect) {
	pArea->setDataPool (visibleData, sigSelect);
}
	
void plotBox::paintEvent(QPaintEvent *arg) {
}
	

void plotBox::resizeEvent(QResizeEvent *arg) {
}
	
void plotBox::setXScale (int value) {
	xScale = value;
	update();
}

void plotBox::setYScale (int value) {
	yScale = value;
	update();
}
