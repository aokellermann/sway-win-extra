
#pragma once

#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace swe::util {

template<typename InputIt, typename Delim>
std::string Join(InputIt first, InputIt last, Delim delimiter) {
  if (first == last)
    return {};

  std::ostringstream ss;
  ss << *(first++);

  while (first != last) {
    ss << delimiter << *(first++);
  }

  return ss.str();
}

}// namespace swe::util
