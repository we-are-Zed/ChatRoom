#include "ClientController.hpp"
#include "ServerManager.hpp"

ClientController::ClientController() {
}

void ClientController::createRoom(ClientManager clientManager, ServerManager serverManager) {
    clientManager.createRoom("room1", "1234", serverManager);
}

void ClientController::joinRoom(ClientManager clientManager, ServerManager serverManager) {
    clientManager.joinRoom("room1", "1234", serverManager);
}

void ClientController::sendMessage(ClientManager clientManager) {
    clientManager.sendMessage("Hello");
}

void ClientController::leaveRoom(ClientManager clientManager) {
    clientManager.leaveRoom();
}
