#include "SimBlock.h"
#include <iostream>

double dysysim::CommonTime::TsimStep = 1;
double dysysim::CommonTime::t = 0;

std::map<int, dysysim::SimBlock*> dysysim::SimBlock::_allSimBlocks;
