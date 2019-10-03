#include "SimBlock.h"
#include <iostream>

double dysysim::SimTime::delta_t = 1;
double dysysim::SimTime::t = 0;

std::map<int, dysysim::SimBlock *> dysysim::SimBlock::_allSimBlocks;
