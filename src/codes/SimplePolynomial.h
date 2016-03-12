#ifndef CODES_SIMPLE_POLYNOMIAL_H
#define CODES_SIMPLE_POLYNOMIAL_H

#include <string>
#include <vector>
#include <Polynomial.h>

class SimplePolynomial : public Polynomial {
private:
    static const int DEFAULT_ALLOC_SIZE = 10;

    int mSize;
    int allocSize;
    bool *container;

    void reAllocate(int newSize);
    void trim();

public:
    SimplePolynomial();
    SimplePolynomial(const Polynomial& polynomial);
    SimplePolynomial(int polynomialPower, const bool* values);
    SimplePolynomial(const std::vector<bool> &vector);
    ~SimplePolynomial();

    SimplePolynomial operator=(const SimplePolynomial &origin);
    SimplePolynomial operator=(const Polynomial &origin) { operator=((SimplePolynomial) origin); return *this; };

    virtual int power() const;
    virtual bool getTerm(int power) const;
    virtual void setTerm(int power, bool value);
    virtual std::string toString() const;

    virtual bool isZero();
    virtual bool equals(const Polynomial& operand);
    virtual void clear();

    virtual void add(const Polynomial &operand);
    virtual void product(const Polynomial &operand);
    virtual void division(const Polynomial &operand, Polynomial &remainder);
};

#endif //CODES_SIMPLE_POLYNOMIAL_H
