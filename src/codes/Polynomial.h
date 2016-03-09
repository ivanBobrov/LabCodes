#ifndef CODES_POLYNOMIAL_H
#define CODES_POLYNOMIAL_H

#include <string>

/**
 * Polynomial is an abstract class for binary polynomial - polynomial with
 * coefficients 0 or 1. It should provide all operations available for binary
 * numbers. Polynomial largest degree must be non-zero and look order must be
 * from lower-degree term to upper i.e. term with index zero means constant
 * term.
 */
class Polynomial {
public:

    /**
     * Returns size of Polynomial i.e. polynomial degree. Constant polynomial
     * must return zero.
     */
    virtual int power() const = 0;

    /**
     * Returns coefficient of term with index <code>power</code>. Look
     * order is from lower degree term to upper i.e. term with index 0 means
     * constant term.
     */
    virtual bool getTerm(int power) const = 0;

    /**
     * Sets term with index <code>power</code>.
     */
    virtual void setTerm(int power, bool value) = 0;

    virtual bool isZero() = 0;

    virtual void clear() = 0;

    /**
     * Returns string representation of binary Polynomial
     */
    virtual std::string toString() const = 0;

    virtual void add(const Polynomial &operand) = 0;

    virtual void product(const Polynomial &operand) = 0;

    virtual void division(const Polynomial &operand, Polynomial &remainder) = 0;
};


#endif //CODES_POLYNOMIAL_H
