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

    SimplePolynomial operator=(const SimplePolynomial &origin);
    SimplePolynomial operator=(const Polynomial &origin) { operator=((SimplePolynomial) origin); return *this; };

    virtual int power() const;
    virtual bool getTerm(int power) const;
    virtual std::string toString() const;
    virtual void setTerm(int power, bool value);

    virtual bool isZero();
    virtual void clear();

    virtual void add(const Polynomial &operand);
    virtual void product(const Polynomial &operand);
    virtual void division(const Polynomial &operand, Polynomial &remainder);
};

#endif //CODES_SIMPLE_POLYNOMIAL_H
