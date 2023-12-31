/**
 * Part of MR-Leo.
 * Linköping University
 * 
 * Author: Johan Lindqvist (johli392@student.liu.se)
 */

#ifndef MOCKCLIENT_H
#define MOCKCLIENT_H

#include "global.h"
#include "networkconnection.h"
#include <QObject>

class QTimer;
class QElapsedTimer;

namespace MRLeo {

class MRServer;

/**
 * @brief The MockClient class
 *
 * Acts as a client and reads images from the "Mock" directory
 * and emits them as new File objects. Used for testing the
 * ImageProcessor classes.
 */
class MockClient : public NetworkConnection {
  Q_OBJECT

public:
  MockClient();
  ~MockClient() override {}
  quint16 getPort() override { return 4412; }
  qint32 getSession() { return mSessionId; }
  QString getHost() { return "0.0.0.0"; }
  void stop() { mRun = false; }
  void start(unsigned long delay, int fps, bool repeat, bool webcam, QString path="", bool sendCommands=true);

private slots:
  void startThread(unsigned long delay, int fps, bool repeat, bool webcam, QString path, bool sendCommands);

signals:
  void startSignal(unsigned long delay, int fps, bool repeat, bool webcam, QString path, bool sendCommands);

private:
  bool mRun;
  qint32 mSessionId;
  QTimer* mRecurringTimer;
  QElapsedTimer *mElapsedTimer;
};

}

#endif // MOCKCLIENT_H
