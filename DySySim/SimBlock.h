#ifndef SIMBLOCK_H
#define SIMBLOCK_H

namespace dysysim {

class CommonTime {
public:
   CommonTime() = default;
   ~CommonTime() = default;
   static void next() { t += TsimStep; }
   static double TsimStep;
   static double t;
};

class SimBlock {
public:
   SimBlock(): _out{0.0} {}
   SimBlock(double initValue): _out{initValue} {}
   virtual ~SimBlock() = default;
   double output() const { return _out; }
protected:
   double _out;
};

class TimedSimBlock: public SimBlock {
public:
   TimedSimBlock(): SimBlock{} {}
   TimedSimBlock(double initValue): SimBlock{initValue} {}
   virtual ~TimedSimBlock() = default;
protected:
   CommonTime tc;
};

}

#endif // SIMBLOCK_H
