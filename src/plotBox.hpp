/*------------------------------------------------------------------------------------------------------------------------------
//                   __     ___      _               _     ___           _ _ _                                
//                   \ \   / (_)_ __| |_ _   _  __ _| |   / _ \ ___  ___(_) | | ___  ___  ___ ___  _ __   ___ 
//                    \ \ / /| | '__| __| | | |/ _` | |  | | | / __|/ __| | | |/ _ \/ __|/ __/ _ \| '_ \ / _ \
//                     \ V / | | |  | |_| |_| | (_| | |  | |_| \__ \ (__| | | | (_) \__ \ (_| (_) | |_) |  __/
//                      \_/  |_|_|   \__|\__,_|\__,_|_|   \___/|___/\___|_|_|_|\___/|___/\___\___/| .__/ \___|
//                                                                                                |_|
//
// File:   plotBox.hpp
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
// License:  LGPL ver 3.0
//
// 	This script is a free software; you can redistribute it and/or modify it under the terms	of the GNU Lesser General
//	Public License as published by the Free Software Foundation; either version 3.0 of the License,	or (at your option)
//	any later version. 
/
//	For further details please read the full LGPL text file [https://www.gnu.org/licenses/lgpl-3.0.txt].
// 	You should have received a copy of the GNU General Public License along with this file; if not, write to the 
//
//		Free Software Foundation, Inc.,
//		59 Temple Place, Suite 330,
//		Boston, MA  02111-1307  USA
//
//
//
//                                                                                                               cols=128 tab=6
------------------------------------------------------------------------------------------------------------------------------*/
#pragma once

#include <QWidget>
#include <refsBar.hpp>
#include <plotArea.hpp>


class plotBox : public QWidget {
	Q_OBJECT

public:
	explicit plotBox(QWidget *parent = nullptr);
	void     setDataPool(QVector<QVector<double>> &visibleData, QVector<bool> sigSelect);
	void     set_xScale(int value);
	void     set_yScale(int value);
	
protected:
	void paintEvent(QPaintEvent *) override;
	void resizeEvent(QResizeEvent *) override;

private:
	refsBar      *yBar  = nullptr;
	refsBar      *xBar  = nullptr;
	plotArea     *pArea = nullptr;
	unsigned int xScale = 10;
	unsigned int yScale = 10;

signals:
    void resized();
};

