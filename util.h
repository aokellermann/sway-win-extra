
#pragma once

#include <iterator>
#include <vector>
#include <string>
#include <sstream>

namespace swe::util
{

std::vector<std::string> Split(std::string&& s)
{
  std::vector<std::string> results;

    std::stringstream ss(std::move(s));
    std::string str;
    while (getline(ss, str, ',')) {
      results.emplace_back(std::move(str));
    }

    return results;
}

template <typename InputIt>
std::string Join(InputIt first, InputIt last, const std::string& delimiter) {
  if (first == last) return {};

  std::ostringstream ss;
  ss << *(first++);

  while (first != last) {
    ss << delimiter << *(first++);
  }

  return ss.str();
}

}
