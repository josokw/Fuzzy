#ifndef FUZZYLOGIC
#define FUZZYLOGIC

class FuzzySet;
class OutputFuzzySet;

enum class LogicModel { Zadeh, Lukasiewicz };

void setLogicModel(LogicModel lm);

OutputFuzzySet operator||(const FuzzySet &lhs, const FuzzySet &rhs);
OutputFuzzySet operator&&(const FuzzySet &lhs, const FuzzySet &rhs);
OutputFuzzySet operator!(const FuzzySet &rhs);

#endif // FUZZYLOGIC
