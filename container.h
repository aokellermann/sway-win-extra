#pragma once

#include "client.h"
#include "workspace.h"
#include "log.h"

namespace swe::container {

void moveContainerToWorkspace(const client::Client &client, ulong target) {
  LOG_INFO("moveContainerToWorkspace called with target=" << target);
  const auto outputsByName = client.GetOutputs();
  if (outputsByName.size() == 1) {
    LOG_INFO("Only one output, moving container directly");
    client.MoveContainerToWorkspace(target);
  } else {
    LOG_INFO("Multiple outputs, finding focused output");
    const auto &[name, output] = *std::find_if(outputsByName.begin(), outputsByName.end(), [](const auto &a) { return *a.second.focused; });
    const auto newWs = std::to_string(workspace::getTargetWorkspace(name, target));
    client.MoveContainerToWorkspace(newWs);
  }
}

void moveContainerToOutput(const client::Client &client, ulong target) {
  LOG_INFO("moveContainerToOutput called with target=" << target);
  const auto outputsByName = client.GetOutputs();
  if (outputsByName.size() == 1) {
    LOG_INFO("Only one output, nothing to do");
    return;
  }
  LOG_INFO("Moving container to output: " << env::displayConfig[target - 1]);
  client.MoveContainerToOutput(env::displayConfig[target - 1]);
}

}// namespace swe::container
