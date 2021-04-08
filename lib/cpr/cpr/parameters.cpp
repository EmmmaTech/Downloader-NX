#include "cpr/parameters.h"

#include <initializer_list>
#include <string>

#include "cpr/utilities.h"

namespace cpr {
Parameters::Parameters(const std::initializer_list<Parameter>& parameters) : CurlContainer<Parameter>(parameters) {}
} // namespace cpr
