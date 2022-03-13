#pragma once

#include <string>
#include <array>

#include "util.h"

namespace swe::env
{
std::vector<std::string> GetDisplayConfig()
{
  auto mons = std::getenv("MONS");
  if (mons == nullptr) return {};
  return util::Split(mons);
}
}
