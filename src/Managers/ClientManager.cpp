#include "ClientManager.hpp"
#include "Message.hpp"
#include "Peer.hpp"
#include "Room.hpp"
#include "ServerManager.hpp"
#include <memory>
#include <utility>

ClientManager::ClientManager(QString userName) : userName(std::move(userName)){
    roomList = std::make_shared<QMap<QString, Room>>();
    ip = "127.0.0.1";
}

ClientManager::~ClientManager() = default;

void ClientManager::createRoom(QString name, QString passWord, ServerManager& serverManager) {
    serverManager.registerRoom(name, passWord);
}

void ClientManager::joinRoom(QString name, QString passWord, ServerManager& serverManager) {
    if(serverManager.serverRoomList->contains(name)) {  // Check if the room exists in server
        auto room = (*serverManager.serverRoomList)[name];

        if(room->getPassWord() == passWord) {
            auto peer = Peer(userName, ip);
            this->currentRoom = room;
            room->addPeer(std::move(peer));
        } else {
            qDebug() << "Wrong password";
            return;
        }
    } else {
        qDebug() << "Room not found";
        return;
    }
}

void ClientManager::sendMessage(QString messageText) {
    auto room = this->currentRoom;
    if(room) {
        QDateTime now = QDateTime::currentDateTime();
        qint64 timestamp = now.toSecsSinceEpoch();
        QString timestampStr = QString::number(timestamp);
        Message message(userName, timestampStr, messageText);
        room->addMessage(std::move(message));
    }else{
        qDebug() << "You are not in a room";
    }
}

void ClientManager::leaveRoom() {
    if(currentRoom) {
        currentRoom->removePeer(userName);
        currentRoom = nullptr;
    } else {
        qDebug() << "You are not in a room";
    }
}