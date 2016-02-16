#ifndef CONNECTING_H
#define CONNECTING_H

namespace dysysim {
class SimBlock;
}

void operator>>(dysysim::SimBlock& lhs, dysysim::SimBlock& rhs);

#endif // CONNECTING_H
