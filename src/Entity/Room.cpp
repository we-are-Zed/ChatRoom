#include "Room.hpp"

Room::Room(QString name, QString passWord){
    this->name = name;
    this->passWord = passWord;
    messages.clear();
    peers.clear();
}

void Room::addPeer(Peer&& peer){
    peers.append(peer);
}

QString Room::getPassWord(){
    return passWord;
}

QList<Peer> Room::getPeers(){
    return peers;
}

void Room::addMessage(Message&& message){
    messages.append(message);
}

void Room::removePeer(QString name){
    for (int i = 0; i < peers.size(); i++) {
        if (peers[i].name == name) {
            peers.removeAt(i);
            return;
        }
    }
}

