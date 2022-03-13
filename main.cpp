#include <array>
#include <swayipc-cpp/sway_socket.hpp>

using sock = swayipc::sway_socket;
using client = swayipc::client;
using output = swayipc::data::output_s;

const static std::string workspaceCommand = "workspace ";
static constexpr std::array<const char*, 3> multiheadDisplays = {"Unknown 0x313D 0x00000000", "Unknown 2367 AJMG79A000532", "Unknown 2367 AJMG79A000521"};


int main(int argc, char** argv) {
  if (argc != 2) {
    std::exit(EXIT_FAILURE);
  }

  const auto target = std::strtol(argv[1], nullptr, 10);

  sock socket;
  socket.connect();
  client conn = socket.get_client();

  auto outputs = conn.get_outputs();
  if (outputs.size() == 1) {
    conn.command(workspaceCommand + argv[1]);
    std::exit(EXIT_SUCCESS);
  }

  std::vector<std::pair<std::string, output>> outputsByName;
  outputsByName.reserve(outputs.size());
  for (auto& output : outputs) {
    outputsByName.emplace_back(std::move(*output.make) + ' ' + std::move(*output.model) + ' ' + std::move(*output.serial), std::move(output));
  }

  // put focused to end so that focused display doesn't change
  std::swap(outputsByName.back(), *std::find_if(outputsByName.begin(), outputsByName.end(), [](const auto& a) { return *a.second.focused;}));

  for (const auto& [name, output] : outputsByName) {
    const auto& currentWs = *output.current_workspace;
    const auto newWs =
        std::to_string
        (std::distance(multiheadDisplays.begin(), std::find(multiheadDisplays.begin(), multiheadDisplays.end(), name)) +
        ((target - 1) * multiheadDisplays.size()) +
        1);

    if (currentWs != newWs)
    {
      conn.command(workspaceCommand + currentWs);
      conn.command(workspaceCommand + newWs);
    }
  }

  return EXIT_SUCCESS;
}