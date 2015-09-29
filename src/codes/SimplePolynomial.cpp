#include "SimplePolynomial.h"

SimplePolynomial::SimplePolynomial(int polynomialLength) {
    if (polynomialLength < 0) {
        //TODO: exception
    }

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
        //TODO: exception
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

bool SimplePolynomial::getTerm(int termIndex) const {
    if (termIndex < 0 || termIndex >= this->mSize) {
        //TODO: exception
    }

    return this->container[termIndex];
}

void SimplePolynomial::setTerm(int index, bool value) {
    if (index < 0 || index > this->mSize) {
        //TODO: exception
    }

    this->container[index] = value;
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
