#pragma once
#include "Message.hpp"
#include "ServerManager.hpp"
#include "Room.hpp"

#include <QMap>
#include <memory>
#include <qmap.h>

#include <QDebug>
#include <qobject.h>
#include <QString>
#include <QDateTime>



class ClientManager {

public:
    ClientManager(QString userName);
    ~ClientManager();
    void createRoom(QString name, QString passWord, ServerManager& serverManager);
    void joinRoom(QString name, QString password, ServerManager& serverManager);
    void leaveRoom();
    void sendMessage(QString messageText);
    void exportMessage();
    void loadMessage();
    void getRoomList();

    QString ip;
    QString userName;
    std::shared_ptr<Room> currentRoom;
    std::shared_ptr<QMap<QString, Room>> roomList;
};