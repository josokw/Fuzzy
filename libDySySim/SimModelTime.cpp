#include "SimModelTime.h"

void dysysim::SimModelTime::set(double delta_t, double t_end)
{
   delta_t_ = delta_t;
   t_end_ = t_end;
}

bool dysysim::SimModelTime::simulation_is_on() const
{
   return t_n_ <= t_end_;
}
