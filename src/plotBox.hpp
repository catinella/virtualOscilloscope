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
//	This class provides the object that manage the oscilloscope's display. Its main task is receive points, print them on
//	display area and connect all points with lines. That's it.
//
------------------------------------------------------------------------------------------------------------------------------*/
#ifndef PLOTBOX_HPP
#define PLOTBOX_HPP

#include <QWidget>

#define PLOTBOX_XGRIDSCALE 10
#define PLOTBOX_YGRIDSCALE 10

class plotBox : public QWidget {
	Q_OBJECT

public:
	explicit plotBox(QWidget *parent = nullptr);
	void     setDataPool(QVector<QVector<double>> &visibleData, QVector<bool> sigSelect);
	
protected:
	void paintEvent(QPaintEvent *) override;
	void resizeEvent(QResizeEvent *) override;

private:
	QPixmap gridLayer;
	void    rebuildGrid();
	void    draw();
	
	int                      xScale = 10;
	int                      yScale = 10;
	QVector<QVector<double>> dataPool = {};
	QVector<bool>            channelMap = {};

signals:
    void resized();
    
public slots:
	void setXScale(int value);
	void setYScale(int value);
};

#endif
