#include "ServerManager.hpp"
#include <memory>
#include <qmap.h>

ServerManager::ServerManager(){
    serverRoomList = std::make_unique<QMap<QString, std::shared_ptr<Room>>>();
}

void ServerManager::registerRoom(QString name, QString passWord){
    serverRoomList->insert(name, std::make_shared<Room>(name, passWord));
}