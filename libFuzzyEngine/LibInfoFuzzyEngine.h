#ifndef LIBINFOFUZZYENGINE_H
#define LIBINFOFUZZYENGINE_H

#include <string>

namespace fuzzy {

const std::string libName{"FuzzyEngine"};
const std::string libMajorVersion{"0"};
const std::string libMinorVersion{"9"};
const std::string libRevisionVersion{"1"};

const std::string libVersion{libMajorVersion + "." + libMinorVersion + "." +
                             libRevisionVersion};
} // namespace fuzzy

#endif
