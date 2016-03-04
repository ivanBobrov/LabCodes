#ifndef CODES_SIMPLE_POLYNOMIAL_H
#define CODES_SIMPLE_POLYNOMIAL_H

#include <string>
#include <Polynomial.h>

class SimplePolynomial : public Polynomial {
private:
    int mSize;
    bool *container;

    void reAllocate(int newSize);

public:
    SimplePolynomial();
    SimplePolynomial(int polynomialLength, const bool* values);
    SimplePolynomial(const Polynomial& polynomial);
    ~SimplePolynomial();

    virtual int size() const;
    virtual bool getTerm(int power) const;
    virtual std::string toString() const;

    void setTerm(int power, bool value);
};


#endif //CODES_SIMPLE_POLYNOMIAL_H
