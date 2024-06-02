#pragma once

#include <grpcpp/grpcpp.h>
#include "chat.grpc.pb.h"
#include <memory>
#include <string>
#include <vector>

struct PeerInfo {
    std::string ip;
    std::string name;
};

/**
 * @class ChatClient
 * @brief A client class to interact with the LN_Chat gRPC service.
 *
 * This class provides methods to register clients, publish rooms, get room peers, and send heartbeat messages.
 * It manages the gRPC channel and stub creation internally.
 */
class RpcClient {
public:
    /**
     * @brief Constructs a new ChatClient object.
     *
     * @param ip The IP address of the gRPC server.
     * @param port The port number of the gRPC server.
     *
     * This constructor initializes the gRPC channel and stub for communication with the server.
     */
    RpcClient(const std::string &ip, const std::string &port);

    /**
     * @brief Destructor for ChatClient.
     *
     * Cleans up resources used by the ChatClient.
     */
    ~RpcClient();

    /**
     * @brief Registers a new client with the server.
     *
     * @param name The name of the client to register.
     * @param clientId Reference to a uint64_t variable where the client ID will be stored if registration is successful.
     * @return true if the client registration was successful, false otherwise.
     */
    bool RegisterClient(const std::string &name, uint64_t &clientId);

    /**
     * @brief Publishes a new room to the server.
     *
     * @param clientId The ID of the client publishing the room.
     * @param name The name of the room to publish.
     * @param password The password for the room.
     * @return true if the room was published successfully, false otherwise.
     */
    bool PublishRoom(uint64_t clientId, const std::string &name, const std::string &password);

    /**
     * @brief Retrieves the list of peers in a room from the server.
     *
     * @param clientId The ID of the client requesting the room peers.
     * @param name The name of the room.
     * @param password The password for the room.
     * @param peersIp Reference to a vector of strings where the IP addresses of the peers will be stored.
     * @return true if the room peers were retrieved successfully, false otherwise.
     */
    bool GetRoomPeers(uint64_t clientId, const std::string &name, const std::string &password,
                      std::vector<PeerInfo> &peersIp);

    /**
     * @brief Sends a heartbeat message to the server to keep the client connection alive.
     *
     * @param clientId The ID of the client sending the heartbeat.
     * @return true if the heartbeat was sent successfully, false otherwise.
     */
    bool HeartBeat(uint64_t clientId);

private:
    std::unique_ptr<LN_Chat::ChatService::Stub> stub_; ///< gRPC stub for interacting with the LN_Chat service.

    /**
     * @brief Constructs the address string from IP and port.
     *
     * @param ip The IP address.
     * @param port The port number.
     * @return A string in the format "ip:port".
     */
    std::string construct_address(const std::string &ip, const std::string &port);
};

