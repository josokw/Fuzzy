#ifndef ERRORCODES_H
#define ERRORCODES_H

#include <system_error>

enum class SimBlockErrc {
   UnknownTypeError =10,
   IdIsNotUniqueError,
   ConfigIdError,
   ConfigInputIdError,
   ConfigParameterError,
   ConfigNumberOfParametersError,
   ConfigParameterRangeError,
   ModelIsInconsistentError
};

namespace std {
template <>
struct is_error_code_enum<SimBlockErrc> : true_type {
};
} // namespace std

[[nodiscard]] std::error_code make_error_code(SimBlockErrc ec);

struct SimBlockErrCategory : std::error_category {
   const char *name() const noexcept override { return "dysysim"; }
   std::string message(int ev) const override
   {
      switch (static_cast<SimBlockErrc>(ev)) {
         case SimBlockErrc::UnknownTypeError:
            return "unknown simulation block type";
         case SimBlockErrc::IdIsNotUniqueError:
            return "id simulation block is not unique";
         case SimBlockErrc::ConfigIdError:
            return "id simulation block value should be > 0";
         case SimBlockErrc::ConfigInputIdError:
            return "input id error";
         case SimBlockErrc::ConfigParameterError:
            return "parameter error";
         case SimBlockErrc::ConfigNumberOfParametersError:
            return "number of parameters not correct";
         case SimBlockErrc::ConfigParameterRangeError:
            return "parameter range error";
         case SimBlockErrc::ModelIsInconsistentError:
            return "model is inconsistent";
         default:
            return "SYSTEM ERROR: unknown error";
      }
   }
};

inline const SimBlockErrCategory simblockErrCategory;

#endif
