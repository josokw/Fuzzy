#ifndef SIMBLOCKI_H
#define SIMBLOCKI_H

#include "SimBlock.h"
#include <initializer_list>
#include <vector>

namespace dysysim {

class SimBlockI: public SimBlock {
public:
   SimBlockI(int id, std::initializer_list<int> ids): SimBlock{id}, _ids{ids} {
      _blockType += "I";
   }
   SimBlockI(int id): SimBlockI{id, {}} {}
   virtual void next() const = 0;
protected:
   std::vector<int> _ids;
};

class TimedSimBlockI: public TimedSimBlock {
public:
   TimedSimBlockI(int id): TimedSimBlock{id} {
      _blockType = "Timed" + _blockType;
   }
   virtual ~TimedSimBlockI() = default;
};

class Log: public SimBlockI {
public:
   Log(std::initializer_list<int> ids): SimBlockI{-1, ids} {
      _blockType += "-Log"; }
   virtual void next() const {
//      std::cout << _blockType << " ";
      for (auto i: _ids) {
//         std::cout << i << " ";
//         auto sb {getSimBlock(i)};
//         std::cout << i << ": " << sb->getBlockType() << "  ";
      }
//      std::cout << std::endl;
   }
private:
   //std::ostream _ofs;
};

}

#endif // SIMBLOCKI_H
