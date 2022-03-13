#include <array>
#include <swayipc-cpp/sway_socket.hpp>
#include <iostream>
#include <algorithm>

#include "client.h"
#include "env.h"

static std::vector<std::string> displayConfig;

std::size_t getTargetWorkspace(const std::string& name, std::size_t target) {
  return std::distance(displayConfig.begin(),
                                      std::find(displayConfig.begin(), displayConfig.end(), name)) +
      ((target - 1) * displayConfig.size()) +
      1;
}

void changeAllWorkspaces(const swe::Client& client, std::size_t target) {
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

void moveContainer(const swe::Client& client, ulong target)
{
  const auto outputsByName = client.GetOutputs();
  if (outputsByName.size() == 1) {
    client.MoveContainer(target);
  } else {
    const auto &[name, output] = *std::find_if(outputsByName.begin(), outputsByName.end(), [](const auto &a) { return *a.second.focused; });
    const auto newWs = std::to_string(getTargetWorkspace(name, target));

    client.MoveContainer(newWs);
  }
}

int main(int argc, const char** argv) {
  if (argc < 3) {
    std::cout << "Usage: sway_win_extra [command] [number]\n";
    std::cout << "\tCommands\n:";
    std::cout << "\t\t- workspaces";
    std::cout << "\t\t- move container to";
    std::exit(EXIT_FAILURE);
  }

  displayConfig = swe::env::GetDisplayConfig();
  if (displayConfig.empty()) {
    std::cerr << "Environment variable $MONS not set\n";
    std::exit(EXIT_FAILURE);
  }

  const auto cmd = swe::util::Join(&argv[1], &argv[argc - 1], ' ');
  const auto target = std::strtoul(argv[argc - 1], nullptr, 10);

  swe::Client client;
  if (std::strcmp(cmd.c_str(), "workspaces") == 0) {
    changeAllWorkspaces(client, target);
  } else if (std::strcmp(cmd.c_str(), "move container to") == 0) {
    moveContainer(client, target);
  }

  return EXIT_SUCCESS;
}