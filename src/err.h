#pragma once
#include <stdexcept>

namespace err {

std::runtime_error make(char const * msg, ...) noexcept;

} // !namespace err
