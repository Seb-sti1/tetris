//
// Created by seb & billy on 01/03/23.
//

#include <vector>
#include <poll.h>
#include "communicator.h"

namespace com {
    bool sendMsg(int socket, Messageable& msg)
    {
        std::vector<char> data;
        msg.toData(data);

        return sendData(socket, data);
    }

    bool sendData(int socket, std::vector<char>& data)
    {
        // Send a response to the client
        if (send(socket, data.data(), data.size(), 0) < 0) {
            std::cerr << "Error sending message to client\n";
            // TODO exception
            return false;
        }
        return true;
    }

    bool dataPresent(int socket)
    {
        auto ufds = new pollfd;
        ufds->fd = socket;
        ufds->events = POLLIN;

        return poll(ufds, 2, 1000) > 0;
    }

    bool receiveData(int socket, std::vector<char>& buffer)
    {
        // Receive data from the client
        size_t num_bytes = recv(socket, buffer.data(), buffer.size(), 0);
        std::cout << "Received " << num_bytes << " bytes from client\n";

        return num_bytes > 0;
    }
}