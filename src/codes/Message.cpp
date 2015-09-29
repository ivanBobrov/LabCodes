#include "Message.h"


Message::Message(int size) {
    if (size < 0) {
        //TODO: exception
    }

    this->mSize = size;
    this->containerCapacity = size > MINIMUM_CAPACITY ? size : MINIMUM_CAPACITY;
    this->container = new bool[containerCapacity];
    std::fill(this->container, this->container + size, 0);
}

Message::Message(int size, const bool *values) {
    if (size < 0) {
        //TODO: exception
    }

    this->mSize = size;
    this->containerCapacity = size > MINIMUM_CAPACITY ? size : MINIMUM_CAPACITY;
    this->container = new bool[containerCapacity];
    std::copy(values, values + size, container);
}

Message::Message(const Message &origin) {
    int size = origin.mSize;
    this->mSize = size;
    this->containerCapacity = origin.containerCapacity;
    this->container = new bool[containerCapacity];
    std::copy(origin.container, origin.container + size, this->container);
}

Message::~Message() {
    delete[] container;
}

int Message::size() const {
    return mSize;
}

bool Message::getBit(int index) const {
    if (index < 0 || index >= mSize) {
        //TODO: throw exception
        return false;
    }

    return container[index];
}

void Message::setBit(int index, bool value) {
    if (index < 0 || index >= mSize) {
        //TODO: throw exception
        return;
    }

    container[index] = value;
}

void Message::switchBit(int index) {
    if (index < 0 || index >= mSize) {
        //TODO: throw exception
        return;
    }

    container[index] = !container[index];
}

void Message::appendBit(bool value) {
    if (mSize < containerCapacity) {
        container[mSize] = value;
        mSize++;

        return;
    }

    expandCapacity(mSize * (CAPACITY_SCALE_FACTOR - 1));

    container[mSize] = value;
    mSize++;
}

void Message::clear() {
    mSize = 0;
}


std::string Message::toString() const {
    //TODO: replace with ternary operator
    std::string representation;
    for (int i = 0; i < this->mSize; i++) {
        bool val = this->container[i];
        if (val) {
            representation.append("1");
        } else {
            representation.append("0");
        }
    }

    return representation;
}


std::string Message::toReverseString() const {
    std::string representation;
    for (int i = mSize - 1; i >= 0; i--) {
        bool value = container[i];
        if (value) {
            representation.append("1");
        } else {
            representation.append("0");
        }
    }

    return representation;
}

std::vector<bool> Message::toBoolVector() const {
    std::vector<bool> vector;
    for (int i = 0; i < mSize; i++) {
        vector.push_back(container[i]);
    }

    return vector;
}

bool Message::equals(Message &other) {
    if (mSize != other.mSize) {
        return false;
    }

    for (int i = 0; i < mSize; i++) {
        if (container[i] != other.container[i]) {
            return false;
        }
    }

    return true;
}

void Message::expandCapacity(int count) {
    bool *newContainer = new bool[containerCapacity + count];
    std::copy(container, container + mSize, newContainer);
    delete[] container;

    container = newContainer;
    containerCapacity += count;
}
