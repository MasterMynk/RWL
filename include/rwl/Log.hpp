#pragma once
#include <iostream>
#include <stdio.h>

#define SET_COLOR(x) "\x1b[" #x "m"

// Got these codes from https://en.wikipedia.org/wiki/ANSI_escape_code#Colors

#define RESET SET_COLOR(0)
#define BOLD SET_COLOR(1)
#define FAINT SET_COLOR(2)
#define RED SET_COLOR(31)
#define GREEN SET_COLOR(32)
#define YELLOW SET_COLOR(33)

namespace rwl::impl {
  enum class LogLevel { Error = 1, Warning, Status, NoImp };

  template <LogLevel Level = LogLevel::Status, typename... Printables>
  void log(const Printables &...printables) {
    if (Level == LogLevel::Error) {
      puts(RED "[ERROR]: " RESET);
      (std::cout << ... << printables) << '\n';
    } else {
#if RWL_DEBUG == 1
      std::cout << (Level == LogLevel::Warning  ? YELLOW "[WARNING]: "
                    : Level == LogLevel::Status ? GREEN "[STATUS]: "
                                                : FAINT "[NOT IMP]: ");
      std::cout << RESET;
      (std::cout << ... << printables) << std::endl;
#endif
    }
  }
} // namespace rwl::impl
