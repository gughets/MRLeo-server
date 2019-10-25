/**
 * Part of MR-Leo.
 * Linköping University
 * 
 * Author: Johan Lindqvist (johli392@student.liu.se)
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QByteArray>
#include <QImage>
#include <QSharedPointer>
#include <opencv/cxcore.hpp>
#include <string.h>
#include <QDebug>

namespace MRLeo {

typedef QSharedPointer<QByteArray> QByteArrayPtr;
typedef QSharedPointer<cv::Mat> cvMatPtr;

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define fDebug qDebug().noquote() << __FILENAME__ << ":"

}

#endif // GLOBAL_H
