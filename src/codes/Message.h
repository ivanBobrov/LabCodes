#ifndef CODES_MESSAGE_H
#define CODES_MESSAGE_H

#include <string>
#include <vector>

//TODO: docs
class Message {
private:
    static const int MINIMUM_CAPACITY = 4;
    static const int CAPACITY_SCALE_FACTOR = 2;

    int mSize;
    int containerCapacity;
    bool *container;

    void expandCapacity(int count);

public:

    Message(int size = 0);
    Message(int size, const bool *values);
    Message(const Message& origin);
    ~Message();

    int size() const;
    bool getBit(int index) const;
    void setBit(int index, bool value);
    void switchBit(int index);
    void appendBit(bool value);
    void clear();

    std::string toString() const;
    std::string toReverseString() const;
    std::vector<bool> toBoolVector() const;
    bool equals(Message& other);
};


#endif //CODES_MESSAGE_H
