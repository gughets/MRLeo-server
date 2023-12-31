/**
 * Part of MR-Leo.
 * Linköping University
 *
 * Author: Johan Lindqvist (johli392@student.liu.se)
 */

#ifndef IMAGEPROCESSER_H
#define IMAGEPROCESSER_H

#include "global.h"
#include "networkconnection.h"
#include <QImage>
#include <QMutex>
#include <QObject>

class QElapsedTimer;

namespace MRLeo {

class ImageProcesser : public QObject
{
  Q_OBJECT

public:
  QImage qImageFromMat(cv::Mat img);
  QByteArrayPtr jpegFromQImage(
      QImage image, bool addmetadata=false, int metadata=0);
  QByteArrayPtr jpegFromMat(
      cv::Mat image, bool addmetadata=false, int metadata=0);
  cv::Mat matFromQImage(QImage img);

  ImageProcesser();
  virtual ~ImageProcesser() {}

  const QMap<quint32, qint32> getProcessingTimes();

signals:
  void sendFile(qint32 session, NetworkConnection::File file);
  void sendQImage(qint32 session, quint32 frameid, QImage image);

public slots:
  void setEmitJPEG(bool enable) { mEmitJPEG = enable; }
  void setEmitQImage(bool enable) { mEmitQImage = enable; }
  void setIdentifyColorFrame(bool enable) { mIdentifyColorFrame = enable; }
  virtual void setDebugMode(bool enable) { mDebugMode = enable; }
  void setAllowAllSources(bool allow) { mAllowAllSources = allow; }
  void setJpgegQualityLevel(int level) { mJpegQualityLevel = level; }
  void setLogTime(bool enable) { mLogTime = enable; }
  void triggerActionA();
  void triggerActionB();
  void triggerActionC();
  void addFileToProcessQueue(qint32 session, NetworkConnection::File file);
  void addMatToProcessQueue(qint32 session, quint32 frameid, cvMatPtr image);
  void addQImageToProcessQueue(qint32 session, quint32 frameid, QImage image);
  void processFile(qint32 session, NetworkConnection::File file);
  void processMat(qint32 session, quint32 frameid, cvMatPtr image);
  void processQImage(qint32 session, quint32 frameid, QImage image);
  virtual void setConfig(QJsonObject calibration) = 0;
  virtual void setCalibrateMode(bool enabled) = 0;
  virtual void calibrateCamera() = 0;
  virtual void setUserInteractionConfiguration(QJsonObject obj) = 0;

protected:
  virtual void process(qint32 session, quint32 frameid, cvMatPtr image) = 0;

  qint32 mSession;
  QMutex mProcessQueueMutex;
  NetworkConnection::File mFileProcessQueue;
  cvMatPtr mMatProcessQueue;
  QImage mQImageProcessQueue;
  quint32 mMatQueuePosition = 0;
  quint32 mFileQueuePosition = 0;
  quint32 mQImageQueuePosition = 0;
  bool mBenchmarking = false;
  bool mEmitJPEG = false;
  bool mEmitQImage = false;
  bool mTriggeredA = false;
  bool mTriggeredB = false;
  bool mTriggeredC = false;
  bool mDebugMode = false;
  bool mAllowAllSources = false;
  bool mIdentifyColorFrame = false;
  int mSkippedImages = 0;
  bool mLogTime = false;
  int mJpegQualityLevel = 80;
  int mImagesLogJpegSize = 10;
  QMap<quint32, qint64> mProcessingStartedTimes;
  QMap<quint32, qint64> mProcessingFinishedTimes;
  QElapsedTimer* mUptime;
  bool mRunning;
};

}

#endif // IMAGEPROCESSER_H
