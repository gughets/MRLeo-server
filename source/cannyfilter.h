/**
 * Part of MR-Leo.
 * Linköping University
 * 
 * Author: Johan Lindqvist (johli392@student.liu.se)
 */

#ifndef CANNYFILTER_H
#define CANNYFILTER_H

#include "global.h"
#include "networkconnection.h"
#include <QImage>
#include <QMutex>
#include <QObject>
#include <opencv/cxcore.hpp>
#include "imageprocesser.h"

namespace MRLeo {

/**
 * @brief The CannyFilter class
 *
 * Example class that inherits ImageProcessor and runs OpenCV's
 * Canny Edge Detector on OpenCV Mat images and outputs the result
 * using sendImage() and sendFile() signals.
 */
class CannyFilter : public ImageProcesser {
  Q_OBJECT

public:
  CannyFilter(qint32 session) { mSession = session; }
  void setConfig(QJsonObject) override {}
  void setCalibrateMode(bool) override {}
  void calibrateCamera() override {}
  void setUserInteractionConfiguration(QJsonObject) override {}

protected:
  virtual void process(qint32 session, quint32 frameid, cvMatPtr image) override;

private:
  double medianMat(cv::Mat Input);
};

}

#endif // CANNYFILTER_H
