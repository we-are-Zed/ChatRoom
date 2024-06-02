#pragma once

#include <QString>
#include <memory>
#include <qlist.h>
#include <qmap.h>
#include "Room.hpp"

class ServerManager {
public:
    ServerManager();
    void registerRoom(QString name, QString passWord);

    std::unique_ptr<QMap<QString, std::shared_ptr<Room>>> serverRoomList;
};