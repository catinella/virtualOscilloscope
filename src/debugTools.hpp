#pragma once
#include <QDebug>

#define QDBG qDebug() << __PRETTY_FUNCTION__ << "[LINE: " << __LINE__ << "]: "
