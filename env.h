#pragma once

#include <string>
#include <vector>

namespace swe::env {

std::vector<std::string> GetDisplayConfig() {
  std::vector<std::string> mons;
  const char *mon;
  char monKey[5] = "MON0";
  while ((mon = std::getenv(monKey)) != nullptr) {
    mons.emplace_back(mon);
    if (monKey[3]++ == '9')
      break;
  }
  return mons;
}

const static std::vector<std::string> displayConfig = GetDisplayConfig();

}// namespace swe::env
