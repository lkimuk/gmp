//   ___ __  __ ___
//  / __|  \/  | _ \ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/ version 0.4.0
//  \___|_|  |_|_|   https://github.com/lkimuk/gmp
//
// SPDX-FileCopyrightText: 2023-2026 Miles Li <https://www.cppmore.com/>
// SPDX-License-Identifier: MIT
//
// This file is part of the GMP (Generative Metaprogramming) library.
// Full project source: https://github.com/lkimuk/gmp

#ifndef GMP_SERIALIZATION_DETAIL_TEXT_HPP_
#define GMP_SERIALIZATION_DETAIL_TEXT_HPP_

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

namespace gmp::detail {

inline bool is_valid_utf8(std::string_view text) noexcept {
  const auto continuation = [](unsigned char c) { return c >= 0x80 && c <= 0xbf; };
  for (std::size_t i = 0; i < text.size();) {
    const auto first = static_cast<unsigned char>(text[i]);
    if (first <= 0x7f) {
      ++i;
      continue;
    }
    if (first >= 0xc2 && first <= 0xdf) {
      if (i + 1 >= text.size() || !continuation(static_cast<unsigned char>(text[i + 1])))
        return false;
      i += 2;
      continue;
    }
    if (first >= 0xe0 && first <= 0xef) {
      if (i + 2 >= text.size())
        return false;
      const auto second = static_cast<unsigned char>(text[i + 1]);
      const auto third = static_cast<unsigned char>(text[i + 2]);
      if (!continuation(third))
        return false;
      if (first == 0xe0   ? (second < 0xa0 || second > 0xbf)
          : first == 0xed ? (second < 0x80 || second > 0x9f)
                          : !continuation(second))
        return false;
      i += 3;
      continue;
    }
    if (first >= 0xf0 && first <= 0xf4) {
      if (i + 3 >= text.size())
        return false;
      const auto second = static_cast<unsigned char>(text[i + 1]);
      if (first == 0xf0   ? (second < 0x90 || second > 0xbf)
          : first == 0xf4 ? (second < 0x80 || second > 0x8f)
                          : !continuation(second))
        return false;
      if (!continuation(static_cast<unsigned char>(text[i + 2])) ||
          !continuation(static_cast<unsigned char>(text[i + 3])))
        return false;
      i += 4;
      continue;
    }
    return false;
  }
  return true;
}

inline void append_utf8(std::string &output, std::uint32_t code_point) {
  if (code_point <= 0x7f) {
    output.push_back(static_cast<char>(code_point));
  } else if (code_point <= 0x7ff) {
    output.push_back(static_cast<char>(0xc0 | (code_point >> 6)));
    output.push_back(static_cast<char>(0x80 | (code_point & 0x3f)));
  } else if (code_point <= 0xffff) {
    output.push_back(static_cast<char>(0xe0 | (code_point >> 12)));
    output.push_back(static_cast<char>(0x80 | ((code_point >> 6) & 0x3f)));
    output.push_back(static_cast<char>(0x80 | (code_point & 0x3f)));
  } else {
    output.push_back(static_cast<char>(0xf0 | (code_point >> 18)));
    output.push_back(static_cast<char>(0x80 | ((code_point >> 12) & 0x3f)));
    output.push_back(static_cast<char>(0x80 | ((code_point >> 6) & 0x3f)));
    output.push_back(static_cast<char>(0x80 | (code_point & 0x3f)));
  }
}

} // namespace gmp::detail

#endif // GMP_SERIALIZATION_DETAIL_TEXT_HPP_
