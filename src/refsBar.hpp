/*------------------------------------------------------------------------------------------------------------------------------
//                   __     ___      _               _     ___           _ _ _                                
//                   \ \   / (_)_ __| |_ _   _  __ _| |   / _ \ ___  ___(_) | | ___  ___  ___ ___  _ __   ___ 
//                    \ \ / /| | '__| __| | | |/ _` | |  | | | / __|/ __| | | |/ _ \/ __|/ __/ _ \| '_ \ / _ \
//                     \ V / | | |  | |_| |_| | (_| | |  | |_| \__ \ (__| | | | (_) \__ \ (_| (_) | |_) |  __/
//                      \_/  |_|_|   \__|\__,_|\__,_|_|   \___/|___/\___|_|_|_|\___/|___/\___\___/| .__/ \___|
//                                                                                                |_|
//
// File:   refsBar.hpp
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
#pragma once
#include <refsBar.hpp>
#include <QVector>
#include <QWidget>

#define REFBAR_NUMSIZE 8

class refsBar : public QWidget {
	Q_OBJECT

public:
	enum towards_t {
		VERTICAL,
		HORIZONTAL
	};
	explicit refsBar     (towards_t barDir, QWidget *parent = nullptr);
	void     setScale    (float myScale);
	void     setRefsPos  (QVector<unsigned int> &positions);
	
protected:
	void paintEvent(QPaintEvent *event) override;

private:
	towards_t             dir;
	QVector<unsigned int> positions = {};
	float                 scale     = 1;
};
