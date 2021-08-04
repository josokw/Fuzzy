#ifndef SIMMODELTIME_H
#define SIMMODELTIME_H

namespace dysysim {

/// SimModelTime contains simulation time data shared by every SimBlock.
/// \todo Use in SimModel
class SimModelTime final
{
public:
   SimModelTime() = default;
   ~SimModelTime() = default;

   void set(double delta_t, double t_end);
   void reset() { t_n_ = 0.0; }
   void next() { t_n_ += delta_t_; }
   bool simulation_is_on() const;
   double operator()() const { return t_n_; }

private:
   double delta_t_ = 0.0;
   double t_end_ = 0.0;
   double t_n_ = 0.0;
};

} // namespace dysysim

#endif
