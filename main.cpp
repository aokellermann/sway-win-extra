#include <array>
#include <iostream>
#include <swayipc-cpp/sway_socket.hpp>

#include "client.h"
#include "container.h"
#include "env.h"
#include "util.h"
#include "workspace.h"
#include "log.h"

using namespace swe;

int main(int argc, const char **argv) {
  LOG_INFO("Program started");
  if (argc < 2) {
    LOG_INFO("No command provided");
    LOG_INFO("Usage: sway_win_extra [command]");
    LOG_INFO("\tCommands:");
    LOG_INFO("\t\t- workspaces [number]");
    LOG_INFO("\t\t- move container to [number]");
    LOG_INFO("\t\t- move container to output [number]");
    std::exit(EXIT_FAILURE);
  }

  if (swe::env::displayConfig.empty()) {
    LOG_ERROR("Environment variable $MON0 not set");
    std::exit(EXIT_FAILURE);
  }

  const auto cmd = argv[1];
  LOG_INFO("Command: " << cmd);

  client::Client client;
  if (std::strcmp(cmd, "workspaces") == 0) {
    LOG_INFO("Executing workspaces command");
    const auto target = std::strtoul(argv[argc - 1], nullptr, 10);
    workspace::changeAllWorkspaces(client, target);
  } else if (std::strcmp(cmd, "move_container_to") == 0) {
    LOG_INFO("Executing move_container_to command");
    const auto target = std::strtoul(argv[argc - 1], nullptr, 10);
    container::moveContainerToWorkspace(client, target);
  } else if (std::strcmp(cmd, "move_container_to_output") == 0) {
    LOG_INFO("Executing move_container_to_output command");
    const auto target = std::strtoul(argv[argc - 1], nullptr, 10);
    container::moveContainerToOutput(client, target);
  } else {
    LOG_ERROR("Unknown command");
    std::exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
