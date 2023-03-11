//
// Created by seb & billy on 19/02/23.
//

#ifndef TETRIS_MESSAGEABLE_H
#define TETRIS_MESSAGEABLE_H

#include <vector>

enum messageType {GAME_START, PLAYER_DATA, DISCONNECT, GET_PLAYER_DATA, UNKNOWN};

#define SIZE_OF_MESSAGE_SIZE 4

/**
 * An abstract class of an object that can be sent to another instance of this application
 */
class Messageable {
public:
    /**
     * @return The type of message
     */
    virtual messageType getType();

    /**
     * Serialize and construct the data that will be send on the network to the following pattern :
     *      |size of the message padded to SIZE_OF_MESSAGE_SIZE char|the type(1 char)|the content|
     *
     * @param data the buffer of data
     */
    void toData(std::vector<char> &data);

private:
    /**
     * @param data the content serialize of the message. The first SIZE_OF_MESSAGE_SIZE + 1 char need to be left empty
     */
    virtual void serialize(std::vector<char> &data) = 0;

    /**
     * @param data the content (without the size of message or the type)
     */
    virtual void deserialize(std::vector<char> data) = 0;
};


#endif //TETRIS_MESSAGEABLE_H
