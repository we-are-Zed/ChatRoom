#pragma once

#include <QString>
class Peer {
public:
    Peer(QString name, QString ip);

    void sendMessage();

    QString name;
    QString ip;
};