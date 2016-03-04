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
     * Returns size of Polynomial i.e. polynomial degree
     */
    virtual int size() const = 0;

    /**
     * Returns coefficient of term with index <code>termIndex</code>. Look
     * order is from lower degree term to upper i.e. term with index 0 means
     * constant term.
     */
    virtual bool getTerm(int power) const = 0;

    /**
     * Returns string representation of binary Polynomial
     */
    virtual std::string toString() const = 0;
};


#endif //CODES_POLYNOMIAL_H
