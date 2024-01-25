#pragma once

#include <fstream>
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

std::vector<std::string> GetDisplayConfigFile() {
  std::vector<std::string> mons;
  std::string configFile;
  const auto configHomeC = std::getenv("XDG_CONFIG_HOME");
  if (configHomeC == nullptr) {
    const auto homeC = std::getenv("HOME");
    if (homeC == nullptr) {
      std::cout << "Couldn't read either $HOME or $XDG_CONFIG_HOME environment variables\n";
      std::exit(1);
    } else {
      configFile = std::filesystem::path(homeC) / ".config";
    }
  } else {
    configFile = configHomeC;
  }

  configFile = std::filesystem::path(configFile) / "sway_win_extra";

  std::ifstream fstr(configFile.c_str());
  std::stringstream sstr;
  sstr << fstr.rdbuf();
  std::string config = sstr.str();

  while (std::isspace(config[config.size() - 1])) {
    config.pop_back();
  }

  std::string next;
  for (auto &c: config) {
    if (c == '\n') {
      mons.emplace_back(next);
      next.clear();
    } else {
      next += c;
    }
  }
  mons.emplace_back(next);

  for (auto& mon : mons) std::cout << mon << "\n";

  return mons;
}

const static std::vector<std::string> displayConfig = GetDisplayConfigFile();

}// namespace swe::env
