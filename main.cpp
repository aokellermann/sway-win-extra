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
  if (argc < 3) {
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

  const auto cmd = swe::util::Join(&argv[1], &argv[argc - 1], ' ');
  const auto target = std::strtoul(argv[argc - 1], nullptr, 10);

  client::Client client;
  if (std::strcmp(cmd.c_str(), "workspaces") == 0) {
    workspace::changeAllWorkspaces(client, target);
  } else if (std::strcmp(cmd.c_str(), "move container to") == 0) {
    container::moveContainer(client, target);
  } else {
    std::cerr << "Unknown command\n";
    std::exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
