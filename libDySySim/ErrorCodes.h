#ifndef ERRORCODES_H
#define ERRORCODES_H

#include <system_error>

enum class SimBlockErrc {
   IdIsNotUniqueError = 10,
   ConfigIdError,
   ConfigInputIdError,
   ConfigParameterError,
   ModelIsInconsistentError
};

namespace std {
template <>
struct is_error_code_enum<SimBlockErrc> : true_type {
};
} // namespace std

std::error_code make_error_code(SimBlockErrc ec);

#endif
