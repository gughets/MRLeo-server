/**
 * Part of MR-Leo.
 * Linköping University
 * 
 * Author: Johan Lindqvist (johli392@student.liu.se)
 */

#include "imagewriter.h"
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>

namespace MRLeo {

void ImageWriter::writeImage(qint32 session, NetworkConnection::File file)
{
  if (!mEnabled || file.type != NetworkConnection::FileType::IMAGE) {
    return;
  }
  QDir dir(mPath);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
  QString filename =
      QString(dir.path() + QDir::separator() + "mrleo_image_%1_%2_%3.jpg")
      .arg(session).arg(file.type).arg(file.id);
  fDebug << "Writing: " << filename;
  QFile filestream(filename);
  filestream.open(QIODevice::WriteOnly);
  filestream.write(*file.data);
  filestream.close();
}


void ImageWriter::writeMat(qint32 session, quint32 frameid, cvMatPtr image)
{
  if (!mEnabled) {
    return;
  }
  QDir dir(mPath);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
  QString filename =
      QString(dir.path() + QDir::separator() + "mrleo_mat_%1_%2.jpg")
      .arg(session).arg(frameid);
  std::vector<int> params(2);
  params[0] = cv::IMWRITE_JPEG_QUALITY;
  params[1] = 100; // 0-100
  imwrite(filename.toStdString().c_str(), *image, params);
}

}

