#include <Views/Components/Builder/ConnectionData.h>

ConnectionData::ConnectionData(QObject* receiver, std::function<void()> slot)
    : receiver_(receiver), slot_(slot) {}

QObject* ConnectionData::getReceiver() { return receiver_; }

void ConnectionData::runSlot() { slot_(); }
