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
   SimBlock() = default;
   virtual ~SimBlock() = default;
   virtual double output() const = 0;
};

class TimedSimBlock: public SimBlock {
public:
   TimedSimBlock(): SimBlock{} {}
   virtual ~TimedSimBlock() = default;
   virtual double output() const override = 0;
protected:
   CommonTime tc;
};

}

#endif // SIMBLOCK_H
