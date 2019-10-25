/**
 * Part of MR-Leo.
 * Linköping University
 * 
 * Author: Johan Lindqvist (johli392@student.liu.se)
 */

#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include "global.h"
#include "networkconnection.h"
#include <QHostAddress>
#include <QObject>

namespace MRLeo {

class ImageWriter : public QObject {
  Q_OBJECT

public:
  ImageWriter(QString path) : mPath(path) {}
  ~ImageWriter() {}

public slots:
  void writeImage(qint32 session, NetworkConnection::File file);
  void writeMat(qint32 session, quint32 frameid, cvMatPtr image);
  void setEnabled(bool enabled) {
    mEnabled = enabled;
  }

private:
  bool mEnabled = true;
  QString mPath;

};

}

#endif // IMAGEWRITER_H
