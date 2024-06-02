#pragma once


#include "Message.hpp"
#include "Peer.hpp"
#include <QList>

class Room {
public:
    QString name;
    QString passWord;
    QList<Peer> peers;
    QList<Message> messages;

    Room(QString name, QString passWord);

    void addPeer(Peer &&peer);

    void removePeer(QString name);

    void addMessage(Message&& message);

    QList<Peer> getPeers();

    QList<Message> getMessages();

    QString getName();

    QString getPassWord();

    void setName(QString name);

    void setPassWord(QString passWord);

    void setPeers(QList<Peer> peers);

    void setMessages(QList<Message> messages);
};

