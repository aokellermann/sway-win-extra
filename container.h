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

std::optional<std::string> getOtherScratchpadShowing(const client::Client &client, const std::string &except) {
  const auto root = client.GetTree();
  for (const auto &output: root.nodes) {
    if (output.current_workspace.has_value()) {
      for (const auto &workspace: output.nodes) {
        if (workspace.name == output.current_workspace.value()) {
          for (const auto &floating: workspace.floating_nodes) {
            if (floating.app_id.has_value() && floating.app_id.value().starts_with("scratch") && floating.app_id.value() != except) {
              return floating.app_id.value();
            }
          }
        }
      }
    }
  }
  return std::nullopt;
}

void scratchpadShowExcept(const client::Client &client, const std::string &except) {
  if (const auto appId = getOtherScratchpadShowing(client, except); appId.has_value()) {
    client.ToggleScratchpad(appId.value());
  }
}

}// namespace swe::container
