/**
 * Part of MR-Leo.
 * Linköping University
 * 
 * Author: Johan Lindqvist (johli392@student.liu.se)
 */

#ifndef TCPBUILDER_H
#define TCPBUILDER_H

#include "global.h"
#include "networkconnection.h"
#include <QObject>

namespace MRLeo {

/**
 * @brief The TcpBuilder class
 *
 * Concatenates the TCP byte stream for a single session and parses it. Objects in the stream (images, json text, control messages)
 * are packaged as NetworkConnection::File objects and sent out to listeners using Qt signal fileReady().
 */
class TcpBuilder : public QObject {
  Q_OBJECT

public:
  TcpBuilder(qint32 session);

public slots:
  void readData(qint32 session, QByteArrayPtr data);

signals:
  void fileReady(qint32 session, NetworkConnection::File file);

private:
  explicit TcpBuilder();
  qint32 mSession;
  qint32 mNumReceivedBytes;
  QByteArrayPtr mData;
  qint32 mFileTransferSize;
  qint32 mFileTransferId;
  qint16 mFileTransferType;
  bool mBufferInitialized;
  bool mBufferSent;
};

}

#endif // TCPBUILDER_H
