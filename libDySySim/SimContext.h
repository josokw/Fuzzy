#ifndef SIMCONTEXT_H
#define SIMCONTEXT_H

#include "ErrorCodes.h"

#include <map>
#include <memory>
#include <system_error>
#include <vector>

namespace dysysim {

class SimBlock;

/// SimTime contains simulation time data.
class SimTime
{
public:
   SimTime() = default;
   ~SimTime() = default;

   double delta_t{1};
   double end_t{0.0};
   int width_t{8};
   int precision_t{3};
   double t{0};

   void set(double delta, double end);
   double output() const { return t; }
   void reset() { t = 0.0; }
   void next() { t += delta_t; }
   bool simulation_is_on() const;
};

/// SimContext owns all simulation state: blocks, execution sequence, and time.
/// Replaces the previous static globals on SimBlock.
class SimContext
{
public:
   SimContext() = default;
   ~SimContext() = default;

   SimContext(const SimContext &) = delete;
   SimContext &operator=(const SimContext &) = delete;

   SimTime sim_time;

   void clear();
   bool idIsUnique(int id) const;
   std::error_code addSimBlock(int id, std::shared_ptr<SimBlock> pSB);
   std::error_code setExeSequence();
   void setExeSequence(std::vector<int> &exeSequence);
   void initSimBlocks();
   void exeSimBlocks();

   std::shared_ptr<SimBlock> getSimBlock(int id);
   double time() const { return sim_time.t; }

private:
   std::map<int, std::shared_ptr<SimBlock>> allSimBlocks_;
   std::vector<int> exeSequence_;
};

} // namespace dysysim

#endif // SIMCONTEXT_H
