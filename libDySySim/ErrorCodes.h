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

struct SimBlockErrCategory : std::error_category {
   const char *name() const noexcept override { return "dysysim"; }
   std::string message(int ev) const override
   {
      switch (static_cast<SimBlockErrc>(ev)) {
         case SimBlockErrc::IdIsNotUniqueError:
            return "id is not unique";
         case SimBlockErrc::ConfigIdError:
            return "config id value < 0";
         case SimBlockErrc::ConfigInputIdError:
            return "input id error";
         case SimBlockErrc::ConfigParameterError:
            return "parameter error";
         case SimBlockErrc::ModelIsInconsistentError:
            return "model is inconsistent";
         default:
            return "unknown error";
      }
   }
};

inline const SimBlockErrCategory simblockErrCategory;

#endif
