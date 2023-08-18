#pragma once

#include <iostream>
#include <string>
#include <algorithm>

#include "client.h"
#include "env.h"

namespace swe::workspace {

std::size_t getTargetWorkspace(const std::string &name, std::size_t target) {
  const auto& displayConfig = env::displayConfig;
  return std::distance(displayConfig.begin(),
                       std::find(displayConfig.begin(), displayConfig.end(), name))
      + ((target - 1) * displayConfig.size()) + 1;
}

void changeAllWorkspaces(const client::Client& client, std::size_t target) {
  const auto& displayConfig = env::displayConfig;
  auto outputsByName = client.GetOutputs();
  if (outputsByName.size() == 1) {
    client.SetWorkspace(target);
  } else {

    if (outputsByName.size() != displayConfig.size()) {
      std::cerr << "Outputs not configured properly.\n";
      std::exit(1);
    }

    // put focused to end so that focused display doesn't change
    std::swap(outputsByName.back(), *std::find_if(outputsByName.begin(), outputsByName.end(), [](const auto &a) { return *a.second.focused; }));

    for (const auto &[name, output]: outputsByName) {
      const auto &currentWs = *output.current_workspace;
      const auto newWs = std::to_string(getTargetWorkspace(name, target));

      if (currentWs != newWs) {
        client.SetWorkspace(currentWs);
        client.SetWorkspace(newWs);
      }
    }
  }
}

}
