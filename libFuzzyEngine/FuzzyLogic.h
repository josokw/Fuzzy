#ifndef FUZZYLOGIC_H
#define FUZZYLOGIC_H

#include <iostream>

class FuzzySet;
class OutputFuzzySet;

enum class LogicModel { Zadeh, Lukasiewicz };

std::ostream& operator<<(std::ostream& os, const LogicModel rhs);

#define USING_LUKASIEWICZ                                                      \
   using lukasiewicz::operator||;                                              \
   using lukasiewicz::operator&&;                                              \
   using lukasiewicz::operator!

#define USING_ZADEH                                                            \
   using zadeh::operator||;                                                    \
   using zadeh::operator&&;                                                    \
   using zadeh::operator!

namespace zadeh {

OutputFuzzySet operator||(const FuzzySet &lhs, const FuzzySet &rhs);
OutputFuzzySet operator&&(const FuzzySet &lhs, const FuzzySet &rhs);
OutputFuzzySet operator!(const FuzzySet &rhs);

} // namespace zadeh

namespace lukasiewicz {

OutputFuzzySet operator||(const FuzzySet &lhs, const FuzzySet &rhs);
OutputFuzzySet operator&&(const FuzzySet &lhs, const FuzzySet &rhs);
OutputFuzzySet operator!(const FuzzySet &rhs);

} // namespace lukasiewicz

#endif // FUZZYLOGIC_H
