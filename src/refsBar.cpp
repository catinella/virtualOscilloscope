/*------------------------------------------------------------------------------------------------------------------------------
//                   __     ___      _               _     ___           _ _ _                                
//                   \ \   / (_)_ __| |_ _   _  __ _| |   / _ \ ___  ___(_) | | ___  ___  ___ ___  _ __   ___ 
//                    \ \ / /| | '__| __| | | |/ _` | |  | | | / __|/ __| | | |/ _ \/ __|/ __/ _ \| '_ \ / _ \
//                     \ V / | | |  | |_| |_| | (_| | |  | |_| \__ \ (__| | | | (_) \__ \ (_| (_) | |_) |  __/
//                      \_/  |_|_|   \__|\__,_|\__,_|_|   \___/|___/\___|_|_|_|\___/|___/\___\___/| .__/ \___|
//                                                                                                |_|
//
// File:   refsBar.cpp
//
// Author: Silvano Catinella <catinella@yahoo.com>
//
// Description:
//	This class provides objects to manage the oscilloscope's (X/Y) references bars
//
// License:  LGPL ver 3.0
//
// 	This script is a free software; you can redistribute it and/or modify it under the terms	of the GNU 	Lesser General
//	Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your option)
//	any later version. 
//
//	For further details please read the full LGPL text file [https://www.gnu.org/licenses/lgpl-3.0.txt].
// 	You should have received a copy of the GNU General Public License along with this file; if not, write to the 
//
//			Free Software Foundation, Inc.,
//			59 Temple Place, Suite 330,
//			Boston, MA  02111-1307  USA
//
//
//                                                                                                               cols=128 tab=6
------------------------------------------------------------------------------------------------------------------------------*/
#include <refsBar.hpp>
#include <QPainter>
#include <debugTools.hpp>

refsBar::refsBar (towards_t barDir, QWidget *parent): QWidget{parent}, dir{barDir} {
	setFixedWidth(50);
	return;
}

void refsBar::setScale (float scale_a) {
	scale = scale_a;
	return;
}

void refsBar::setRefsPos (QVector<unsigned int> &positions_a) {
	positions = positions_a;
	QDBG << "POSITIONS = " << positions.size() << "\n";
	update();
	return;
}

void refsBar::paintEvent(QPaintEvent *) {
	//
	// Descriptiom:
	//	It prints the vertical bar of reference measures
	//
	//	QT standard coordinates system:
	//
	//	(0,0)
	//	  +-------------> x+
	//	  |
	//	  |
	//	  |
	//	  v
	//	 y+
	//
	QPainter p(this);
	float    valueFloat = 0.0, maxValue = 0.0, valueStep = 0.0;
	QString  valueString("");
	
	p.setPen(Qt::black);

	QFont f = p.font();
	f.setPointSize(REFBAR_NUMSIZE);
	p.setFont(f);

	QFontMetrics fm(p.font());
	int textHeight = fm.height();

	if (dir == VERTICAL) {
		maxValue   = (height() / 2.0f) / scale;  // The higher ref value
		valueStep  = (2.0f * maxValue) / (positions.size());
		
		// [!] yRefsPos.size() should be always odd number
		for (int t = (positions.size() - 1); t >= 0; t--) {
			div_t hp = div((unsigned int)positions.size(), 2);
			valueFloat = ((hp.quot - t) * valueStep);
			valueString = QString("%1").arg(valueFloat, 6, 'f', 2, QChar('0'));
			p.drawText(
				0,
				(positions[t] - textHeight/2),
				(width() - 4), 16,
				Qt::AlignRight | Qt::AlignVCenter, valueString
			);
		}
		
	} else {
		maxValue   = width() / scale;
		valueStep  = maxValue / (positions.size() - 1);
		
		for (unsigned int t = 0; t< positions.size(); t++) {
			valueFloat = (t * valueStep);
			valueString = QString::number(valueFloat, 'f', 2);
			p.drawText(
				(positions[t]),
				(height() / 2),
				40, 16,
				Qt::AlignRight | Qt::AlignVCenter, valueString
			);
		}
	}

	return;
}
