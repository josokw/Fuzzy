#ifndef CONNECTING_H
#define CONNECTING_H

#include "DySySim.h"

namespace dysysim {
class SimBlock;
}

dysysim::SimBlock& operator>(dysysim::SimBlock& lhs, dysysim::SimBlock& rhs);

dysysim::SimBlock& operator+(dysysim::SimBlock& lhs, dysysim::SimBlock& rhs);

#endif // CONNECTING_H
