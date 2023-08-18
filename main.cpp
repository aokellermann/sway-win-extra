#include <array>
#include <iostream>
#include <swayipc-cpp/sway_socket.hpp>

#include "client.h"
#include "container.h"
#include "env.h"
#include "util.h"
#include "workspace.h"

using namespace swe;

int main(int argc, const char **argv) {
  if (argc < 2) {
    std::cout << "Usage: sway_win_extra [command]\n";
    std::cout << "\tCommands:\n";
    std::cout << "\t\t- workspaces [number]\n";
    std::cout << "\t\t- move container to [number]";
    std::exit(EXIT_FAILURE);
  }

  if (swe::env::displayConfig.empty()) {
    std::cerr << "Environment variable $MON0 not set\n";
    std::exit(EXIT_FAILURE);
  }

  const auto cmd = argv[1];

  client::Client client;
  if (std::strcmp(cmd, "workspaces") == 0) {
    const auto target = std::strtoul(argv[argc - 1], nullptr, 10);
    workspace::changeAllWorkspaces(client, target);
  } else if (std::strcmp(cmd, "move_container_to") == 0) {
    const auto target = std::strtoul(argv[argc - 1], nullptr, 10);
    container::moveContainer(client, target);
  } else if (std::strcmp(cmd, "scratchpad_show_except") == 0) {
    const auto target = argv[2];
    container::scratchpadShowExcept(client, std::string(target));
  } else {
    std::cerr << "Unknown command\n";
    std::exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
