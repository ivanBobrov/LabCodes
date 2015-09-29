#ifndef CODES_SIMPLE_POLYNOMIAL_H
#define CODES_SIMPLE_POLYNOMIAL_H

#include <string>
#include <Polynomial.h>

class SimplePolynomial : public Polynomial {
private:
    int mSize;
    bool *container;

public:
    SimplePolynomial(int polynomialLength);
    SimplePolynomial(int polynomialLength, const bool* values);
    SimplePolynomial(const Polynomial& polynomial);
    ~SimplePolynomial();

    virtual int size() const;
    virtual bool getTerm(int termIndex) const;
    virtual std::string toString() const;

    void setTerm(int index, bool value);
};


#endif //CODES_SIMPLE_POLYNOMIAL_H
