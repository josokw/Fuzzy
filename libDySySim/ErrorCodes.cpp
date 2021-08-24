#include "ErrorCodes.h"

std::error_code make_error_code(SimBlockErrc ec)
{
   return {static_cast<int>(ec), simblockErrCategory};
}
