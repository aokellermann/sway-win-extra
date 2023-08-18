#pragma once

#include "client.h"
#include "workspace.h"

namespace swe::container {

void moveContainer(const client::Client& client, ulong target)
{
  const auto outputsByName = client.GetOutputs();
  if (outputsByName.size() == 1) {
    client.MoveContainer(target);
  } else {
    const auto &[name, output] = *std::find_if(outputsByName.begin(), outputsByName.end(), [](const auto &a) { return *a.second.focused; });
    const auto newWs = std::to_string(workspace::getTargetWorkspace(name, target));

    client.MoveContainer(newWs);
  }
}

std::optional<std::string> isScratchpadShowing(const client::Client& client) {
  const auto root = client.GetTree();
  for (const auto &output: root.nodes) {
    if (output.current_workspace.has_value()) {
      for (const auto &workspace: output.nodes) {
        if (workspace.name == output.current_workspace.value()) {
          for (const auto &floating: workspace.floating_nodes) {
            if (floating.app_id.has_value() && floating.app_id.value().starts_with("scratch")) {
              return floating.app_id.value();
            }
          }
        }
      }
    }
  }
  return std::nullopt;
}

void toggleScratchPadIfShowing(const client::Client& client) {
  if (const auto appId = isScratchpadShowing(client); appId.has_value()) {
    client.ToggleScratchpad(appId.value());
  }
}

}
