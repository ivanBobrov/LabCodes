#ifndef CODES_SIMPLE_POLYNOMIAL_H
#define CODES_SIMPLE_POLYNOMIAL_H

#include <string>
#include <Polynomial.h>

class SimplePolynomial : public Polynomial {
private:
    int mSize;
    int allocSize;
    bool *container;

    void reAllocate(int newSize);
    void trim();

public:
    SimplePolynomial();
    SimplePolynomial(int polynomialPower, const bool* values);
    SimplePolynomial(const Polynomial& polynomial);
    ~SimplePolynomial();

    virtual int size() const;
    virtual bool getTerm(int power) const;
    virtual std::string toString() const;
    virtual void setTerm(int power, bool value);
    virtual bool isZero();
    virtual void add(const Polynomial &operand);
    virtual void product(const Polynomial &operand);
    virtual void division(const Polynomial &operand, Polynomial &remainder);

    void clear();
};


#endif //CODES_SIMPLE_POLYNOMIAL_H
