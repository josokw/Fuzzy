#include "SimBlock.h"
#include <iostream>

double dysysim::SimTime::TsimStep = 1;
double dysysim::SimTime::t = 0;

std::map<int, dysysim::SimBlock*> dysysim::SimBlock::_allSimBlocks;
