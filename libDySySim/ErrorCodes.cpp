#include "ErrorCodes.h"

namespace {

struct SimBlockErrCategory : std::error_category {
   const char *name() const noexcept override { return "dysysim"; }
   std::string message(int ev) const override
   {
      switch (static_cast<SimBlockErrc>(ev)) {
         case SimBlockErrc::IdIsNotUniqueError:
            return "id is not unique";
         case SimBlockErrc::ConfigIdError:
            return "config id value < 0";
         default:
            return "unknown error";
      }
   }
};

const SimBlockErrCategory simblockErrCategory;

} // namespace

std::error_code make_error_code(SimBlockErrc ec)
{
   return {static_cast<int>(ec), simblockErrCategory};
}
