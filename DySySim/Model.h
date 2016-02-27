#ifndef MODEL_H
#define MODEL_H

#include "DySySim.h"
#include <iosfwd>
#include <string>

namespace dysysim {

class Model
{
public:
   Model(const std::string& name, double delta_t_simulation,
         std::initializer_list<int> ids):
      _name{name}, _time{0, delta_t_simulation}, _logger{ids} {}
   virtual ~Model() = default;
   std::ostream& write(std::ostream& os) const;
   void simulate(int steps);
private:
   std::string _name;
   Time _time;
   Log _logger;
   void connect();
};

}

#endif // MODEL_H
