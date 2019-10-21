#ifndef FUZZYLOGIC
#define FUZZYLOGIC

#include "FuzzySet.h"
#include "FuzzyLogic.h"
#include "OutputFuzzySet.h"

enum class LogicModel { Zadeh, Lukasiewicz };

namespace {

LogicModel model{LogicModel::Zadeh};

}

void setLogicModel(LogicModel lm)
{
   model = lm;
}

OutputFuzzySet operator||(const FuzzySet &lhs, const FuzzySet &rhs)
{
   OutputFuzzySet result;

   switch (model) {
      case LogicModel::Zadeh:
         result.mbs_ = std::max(lhs.mbs_, rhs.mbs_);
         break;
      case LogicModel::Lukasiewicz:
         result.mbs_ = std::min(lhs.mbs_ + rhs.mbs_, 1.0);
         break;
   }

   return result;
}

OutputFuzzySet operator&&(const FuzzySet &lhs, const FuzzySet &rhs)
{
   OutputFuzzySet result;
   switch (model) {
      case LogicModel::Zadeh:
         result.mbs_ = std::min(lhs.mbs_, rhs.mbs_);
         break;
      case LogicModel::Lukasiewicz:
         result.mbs_ = std::max(lhs.mbs_ + rhs.mbs_ - 1.0, 0.0);
         break;
   }

   return result;
}

OutputFuzzySet operator!(const FuzzySet &rhs)
{
   OutputFuzzySet result;
   result.mbs_ = 1 - rhs.mbs_;

   return result;
}

#endif // FUZZYLOGIC
