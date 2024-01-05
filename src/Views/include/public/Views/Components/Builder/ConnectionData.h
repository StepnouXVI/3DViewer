#pragma once

#include <QObject>
#include <functional>

class ConnectionData : public QObject {
  Q_OBJECT

 private:
  QObject *receiver_;
  std::function<void()> slot_;

 public:
  ConnectionData(QObject *receiver, std::function<void()> slot);

  QObject *getReceiver();
  void runSlot();
};
