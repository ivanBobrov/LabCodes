#include <stdexcept>
#include "SimplePolynomial.h"

SimplePolynomial::SimplePolynomial() {
    int allocSize = 10;

    this->container = new bool[allocSize];
    std::fill(this->container, this->container + allocSize, 0);
    this->mSize = 0;
    this->allocSize = allocSize;
}

SimplePolynomial::SimplePolynomial(const Polynomial& polynomial) {
    int power = polynomial.power();
    this->mSize = power;
    this->allocSize = power + 1;
    this->container = new bool[power + 1];
    for (int i = 0; i <= power; i++) {
        this->container[i] = polynomial.getTerm(i);
    }

    trim();
}

SimplePolynomial::SimplePolynomial(int polynomialPower, const bool *values) {
    if (polynomialPower < 0) {
        throw std::invalid_argument("polynomial length must be positive number");
    }

    this->mSize = polynomialPower;
    this->allocSize = polynomialPower + 1;
    this->container = new bool[polynomialPower + 1];
    for (int i = 0; i <= polynomialPower; i++) {
        this->container[i] = values[i];
    }

    trim();
}

SimplePolynomial::~SimplePolynomial() {
    delete[] this->container;
}

SimplePolynomial SimplePolynomial::operator=(const SimplePolynomial &origin) {
    clear();
    for (int i = 0; i <= origin.power(); i++) {
        setTerm(i, origin.getTerm(i));
    }

    return *this;
}

int SimplePolynomial::power() const {
    return this->mSize;
}

bool SimplePolynomial::getTerm(int power) const {
    if (power < 0 || power > this->mSize) {
        return false;
    }

    return this->container[power];
}

void SimplePolynomial::setTerm(int power, bool value) {
    if (power < 0) {
        throw std::invalid_argument("power is negative");
    }

    if (power > this->mSize) {
        if (power >= this->allocSize) {
            reAllocate(power+1);
        }

        this->mSize = power;
        this->container[power] = value;
    } else if (power == this->mSize) {
        this->container[power] = value;
        trim();
    } else {
        this->container[power] = value;
    }
}


bool SimplePolynomial::isZero() {
    return mSize == 0 && !getTerm(0);
}

std::string SimplePolynomial::toString() const {
    std::string representation;
    for (int i = 0; i <= this->mSize; i++) {
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
    if (newSize == this->allocSize) {
        return;
    }

    bool* newContainer = new bool[newSize];
    int bound = newSize > this->allocSize ? this->allocSize : newSize;
    for (int i = 0; i < bound; i++) {
        newContainer[i] = this->container[i];
    }

    delete[] this->container;
    this->container = newContainer;
    this->allocSize = newSize;
}

void SimplePolynomial::trim() {
    int lastPositivePower = 0;

    for (int i = 0; i < allocSize; i++) {
        if (container[i]) {
            lastPositivePower = i;
        }
    }

    if (lastPositivePower < mSize) {
        mSize = lastPositivePower;
    }
}


void SimplePolynomial::clear() {
    for (int i = 0; i <= power(); i++) {
        setTerm(i, false);
    }

    mSize = 0;
}

void SimplePolynomial::add(const Polynomial &operand) {
    int maxBound = std::max(power(), operand.power());

    for (int i = 0; i <= maxBound; i++) {
        setTerm(i, getTerm(i) ^ operand.getTerm(i));
    }
}

void SimplePolynomial::product(const Polynomial &operand) {
    int maxBound = power() + operand.power();

    bool *out = new bool[maxBound+1];

    for (int i = 0; i <= maxBound; i++) {
        bool iValue = false;

        for (int j = 0; j <= i; j++) {
            bool add = getTerm(j) && operand.getTerm(i-j);
            iValue ^= add;
        }

        out[i] = iValue;
    }

    for (int i = 0; i <= maxBound; i++ ) {
        setTerm(i, out[i]);
    }

    delete[] out;
}

void SimplePolynomial::division(const Polynomial &operand, Polynomial &remainder) {
    if (operand.power() == 0 && operand.getTerm(0) == false) {
        throw std::invalid_argument("Division by zero");
    }

    for (int i = 0; i <= power(); i++) {
        remainder.setTerm(i, getTerm(i));
        setTerm(i, false);
    }

    SimplePolynomial factor;

    while (remainder.power() >= operand.power() && !remainder.isZero()) {
        factor.setTerm(remainder.power() - operand.power(), true);
        add(factor);

        factor.product(operand);
        remainder.add(factor);

        factor.clear();
    }
}