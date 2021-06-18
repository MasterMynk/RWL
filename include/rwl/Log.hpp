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
  constexpr void log(const char *const &callerName = "Unknown",
                     const Printables &...printables) {
    if constexpr (Level == LogLevel::Error) {
      printf(RED "[%s]: " RESET, callerName);
      (std::cout << ... << printables) << '\n';
    } else {
#if RWL_DEBUG == 1
      printf("%s[%s]: " RESET,
             (Level == LogLevel::Warning  ? YELLOW
              : Level == LogLevel::Status ? GREEN
                                          : FAINT),
             callerName);
      (std::cout << ... << printables) << std::endl;
#endif
    }
  }
} // namespace rwl::impl
