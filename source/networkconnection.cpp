/**
 * Part of MR-Leo.
 * Linköping University
 * 
 * Author: Johan Lindqvist (johli392@student.liu.se)
 */

#include "networkconnection.h"
#include <mutex>

namespace MRLeo {

/**
 * @brief NetworkConnection::setSendImagesForSession
 * @param session
 * @param enabled
 */
void NetworkConnection::setSendImagesForSession(qint32 session, bool enabled)
{
  mSendImagesForSessionListMutex.lock();
  mSendImagesForSessionList.insert(session, enabled);
  mSendImagesForSessionListMutex.unlock();
}

/**
 * @brief NetworkConnection::sendImagesForSession
 * @param sessionId
 * @return
 */
bool NetworkConnection::sendImagesForSession(qint32 sessionId)
{
  mSendImagesForSessionListMutex.lock();
  bool retval = mSendImagesForSessionList.value(sessionId, false);
  mSendImagesForSessionListMutex.unlock();
  return retval;
}

/**
 * @brief NetworkConnection::getProcessingTimes
 * @return
 */
QMap<quint32, qint64> NetworkConnection::getProcessingTimes(qint32 session)
{
  mTimeLogsMutex.lock();
  auto timelogs = mTimeLogs.value(session, nullptr);
  mTimeLogsMutex.unlock();
  QMap<quint32, qint64> retMap;
  if (timelogs) {
    retMap = *timelogs;
    retMap.detach();
  }
  retMap.remove(retMap.lastKey());
  return retMap;
}


}
