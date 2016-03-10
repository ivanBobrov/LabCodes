#ifndef HAMMING_CODES_CYCLIC_CODES_LAB_H
#define HAMMING_CODES_CYCLIC_CODES_LAB_H

#include <Polynomial.h>
#include <SimplePolynomial.h>
#include <Message.h>
#include <CodeConverter.h>
#include "CyclicLabView.h"
#include "LabTaskRunner.h"
#include "CyclicLabTask.h"

class ICyclicCodesLab {
public:
    virtual void buttonStartClicked() = 0;
};

class CyclicCodesLab : public ICyclicCodesLab {

private:
    CyclicLabView *labView = nullptr;

public:
    CyclicCodesLab();

    virtual void buttonStartClicked();

    void setCyclicLabView(CyclicLabView &view);

};


#endif //HAMMING_CODES_CYCLIC_CODES_LAB_H
