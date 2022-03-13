#pragma once

#include <memory>
#include <swayipc-cpp/sway_socket.hpp>
#include <utility>

#include "env.h"

namespace swe {

class Client {
  using output = swayipc::data::output_s;
  using outputs = std::vector<std::pair<std::string, output>>;

public:
  explicit Client() {
    _sock.connect();
    _client = std::make_unique<swayipc::client>(&_sock);
  }

  [[nodiscard]] outputs GetOutputs() const {
    auto rawOutputs = _client->get_outputs();

    outputs outputsByName;
    outputsByName.reserve(rawOutputs.size());
    for (auto &output: rawOutputs) {
      outputsByName.emplace_back(GetOutputName(output), std::move(output));
    }

    return outputsByName;
  }

  void SetWorkspace(ulong target) const { SetWorkspace(std::to_string(target)); }

  void SetWorkspace(const std::string &target) const {
    const static std::string workspaceCommand("workspace ");
    _client->command(workspaceCommand + target);
  }

  void MoveContainer(ulong target) const { MoveContainer(std::to_string(target)); }

  void MoveContainer(const std::string &target) const {
    const static std::string workspaceCommand("move container to workspace ");
    _client->command(workspaceCommand + target);
  }

private:
  static std::string GetOutputName(const output &output) {
    std::stringstream sstr;
    sstr << *output.make << ' ' << *output.model << ' ' << *output.serial;
    return sstr.str();
  }

  swayipc::sway_socket _sock;
  std::unique_ptr<swayipc::client> _client;
};
}