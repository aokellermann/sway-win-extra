#pragma once

#include "client.h"
#include "workspace.h"

namespace swe::container {

void moveContainerToWorkspace(const client::Client &client, ulong target) {
  const auto outputsByName = client.GetOutputs();
  if (outputsByName.size() == 1) {
    client.MoveContainerToWorkspace(target);
  } else {
    const auto &[name, output] = *std::find_if(outputsByName.begin(), outputsByName.end(), [](const auto &a) { return *a.second.focused; });
    const auto newWs = std::to_string(workspace::getTargetWorkspace(name, target));

    client.MoveContainerToWorkspace(newWs);
  }
}

void moveContainerToOutput(const client::Client &client, ulong target) {
  const auto outputsByName = client.GetOutputs();
  if (outputsByName.size() == 1) {
    return;
  }

  client.MoveContainerToOutput(env::displayConfig[target - 1]);
}

}// namespace swe::container
