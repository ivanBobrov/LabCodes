#include <stdexcept>
#include "SimplePolynomial.h"

SimplePolynomial::SimplePolynomial() {
    int polynomialLength = 1;

    this->container = new bool[polynomialLength];
    std::fill(this->container, this->container + polynomialLength, 0);
    this->mSize = polynomialLength;
}

SimplePolynomial::SimplePolynomial(const Polynomial& polynomial) {
    int size = polynomial.size();
    this->mSize = size;
    this->container = new bool[size];
    for (int i = 0; i < size; i++) {
        this->container[i] = polynomial.getTerm(i);
    }
}

SimplePolynomial::SimplePolynomial(int polynomialLength, const bool *values) {
    if (polynomialLength < 0) {
        throw std::invalid_argument("polynomial length must be positive number");
    }

    this->mSize = polynomialLength;
    this->container = new bool[polynomialLength];
    for (int i = 0; i < polynomialLength; i++) {
        this->container[i] = values[i];
    }
}

SimplePolynomial::~SimplePolynomial() {
    delete[] this->container;
}

int SimplePolynomial::size() const {
    return this->mSize;
}

bool SimplePolynomial::getTerm(int power) const {
    if (power < 0 || power >= this->mSize) {
        return false;
    }

    return this->container[power];
}

void SimplePolynomial::setTerm(int power, bool value) {
    if (power < 0) {
        throw std::invalid_argument("power is negative");
    }

    if (power >= this->mSize) {
        reAllocate(power+1);
    }

    this->container[power] = value;
}

std::string SimplePolynomial::toString() const {
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

void SimplePolynomial::reAllocate(int newSize) {
    if (newSize == this->mSize) {
        return;
    }

    bool* newContainer = new bool[newSize];
    for (int i = 0; i < newSize > this->mSize ? this->mSize : newSize; i++) {
        newContainer[i] = this->container[i];
    }

    delete[] this->container;
    this->container = newContainer;
    this->mSize = newSize;
}
