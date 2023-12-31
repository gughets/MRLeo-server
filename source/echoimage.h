/**
 * Part of MR-Leo.
 * Linköping University
 * 
 * Author: Johan Lindqvist (johli392@student.liu.se)
 */

#ifndef ECHOIMAGE_H
#define ECHOIMAGE_H

#include "global.h"
#include "networkconnection.h"
#include <QImage>
#include <QMutex>
#include <QObject>
#include <opencv/cxcore.hpp>
#include "imageprocesser.h"

namespace MRLeo {

/**
 * @brief The EchoImage class
 *
 * Example class that inherits ImageProcessor and runs OpenCV's
 * Canny Edge Detector on OpenCV Mat images and outputs the result
 * using sendImage() and sendFile() signals.
 */
class EchoImage : public ImageProcesser {
  Q_OBJECT

public:
  EchoImage(qint32 session, bool benchmarking);
  virtual ~EchoImage() override;
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

#endif // ECHOIMAGE_H
