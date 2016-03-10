#ifndef HAMMING_CODES_CYCLIC_CODES_LAB_H
#define HAMMING_CODES_CYCLIC_CODES_LAB_H

#include <Polynomial.h>
#include <SimplePolynomial.h>
#include <Message.h>
#include <CodeConverter.h>
#include "CyclicLabView.h"
#include "LabTaskRunner.h"
#include "CyclicLabTask.h"

class CyclicCodesLab {

private:
    CyclicLabView *labView;

public:
    CyclicCodesLab();

    void setCyclicLabView(CyclicLabView &view);

};


#endif //HAMMING_CODES_CYCLIC_CODES_LAB_H
