/*------------------------------------------------------------------------------------------------------------------------------
//                   __     ___      _               _     ___           _ _ _                                
//                   \ \   / (_)_ __| |_ _   _  __ _| |   / _ \ ___  ___(_) | | ___  ___  ___ ___  _ __   ___ 
//                    \ \ / /| | '__| __| | | |/ _` | |  | | | / __|/ __| | | |/ _ \/ __|/ __/ _ \| '_ \ / _ \
//                     \ V / | | |  | |_| |_| | (_| | |  | |_| \__ \ (__| | | | (_) \__ \ (_| (_) | |_) |  __/
//                      \_/  |_|_|   \__|\__,_|\__,_|_|   \___/|___/\___|_|_|_|\___/|___/\___\___/| .__/ \___|
//                                                                                                |_|
//
// File:   plotArea.hpp
//
// Author: Silvano Catinella <catinella@yahoo.com>
//
// Description:
//	This class provides the object that manage the oscilloscope's display. Its main task is receive points, print them on
//	display area and connect all points with lines. That's it.
//
//	Symbols:
//		PLOTAREA_XGRID  It sets the number of pixels between two vertical lines
//		PLOTAREA_YGRID  It sets the pixels number between two horizontal lives
//		PLOTAREA_LRAT   It sets the number of (vertical or horizontal) gray lines between before a lighter one
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
#pragma once

#include <QWidget>
#include <refsBar.hpp>

#define PLOTAREA_XGRID 10
#define PLOTAREA_YGRID 10
#define PLOTAREA_LRAT  5

class plotArea : public QWidget {
	Q_OBJECT

public:
	explicit plotArea    (QWidget *parent = nullptr);
	void     setDataPool (QVector<QVector<double>> &visibleData, QVector<bool> sigSelect);
	void     rebuildGrid ();
	
protected:
	void     paintEvent  (QPaintEvent *) override;
	void     resizeEvent (QResizeEvent *) override;

private:
	void     draw        ();
	
	QPixmap                  gridLayer;
	int                      xScale     = 10;
	int                      yScale     = 10;
	/*
	QVector<unsigned int>    yRefsPos   = {};
	QVector<unsigned int>    xRefsPos   = {};
	*/
	QVector<QVector<double>> dataPool   = {};
	QVector<bool>            channelMap = {};
	
signals:
    void resized();
    void gridReady(QList<unsigned int>yRefsPos, QList<unsigned int>xRefsPos);
    
public slots:
	void setXScale(int value);
	void setYScale(int value);
};
