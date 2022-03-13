#include <array>
#include <swayipc-cpp/sway_socket.hpp>
#include <iostream>

#include "client.h"
#include "env.h"

static std::vector<std::string> displayConfig;

void changeAllWorkspaces(const swe::Client& client, ulong target) {
  auto outputsByName = client.GetOutputs();
  if (outputsByName.size() == 1) {
    client.SetWorkspace(target);
    std::exit(EXIT_SUCCESS);
  }

  if (outputsByName.size() != displayConfig.size()) {
    std::cerr << "Outputs not configured properly.\n";
    std::exit(1);
  }

  // put focused to end so that focused display doesn't change
  std::swap(outputsByName.back(), *std::find_if(outputsByName.begin(), outputsByName.end(), [](const auto &a) { return *a.second.focused; }));

  for (const auto &[name, output]: outputsByName) {
    const auto &currentWs = *output.current_workspace;
    const auto newWs =
        std::to_string(std::distance(displayConfig.begin(), std::find(displayConfig.begin(), displayConfig.end(), name)) + ((target - 1) * displayConfig.size()) + 1);

    if (currentWs != newWs) {
      client.SetWorkspace(currentWs);
      client.SetWorkspace(newWs);
    }
  }
}

int main(int argc, char** argv) {
  if (argc != 3) {
    std::exit(EXIT_FAILURE);
  }

  displayConfig = swe::env::GetDisplayConfig();
  if (displayConfig.empty()) {
    std::cerr << "Environment variable $MONS not set\n";
    std::exit(1);
  }

  const auto cmd = argv[1];

  swe::Client client;

  if (std::strcmp(cmd, "workspaces") == 0) {
    const auto target = std::strtoul(argv[2], nullptr, 10);
    changeAllWorkspaces(client, target);
  }

  return EXIT_SUCCESS;
}