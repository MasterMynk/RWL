#pragma once
#include <stdio.h>

#define SET_COLOR(x) "\x1b[" #x "m"

#define RED SET_COLOR(31)
#define RESET SET_COLOR(0)
#define GREEN SET_COLOR(32)
#define YELLOW SET_COLOR(33)

namespace rwl::impl {
  enum class LogLevel {
    Error = 1,
    Status,
    Warning,
  };

  template <LogLevel Level = LogLevel::Status, typename... Printables>
  void log(const Printables &...printables) {
#if RWL_DEBUG == 1
    printf("%s]:%s ",
           Level == LogLevel::Error     ? RED "[ERROR"
           : Level == LogLevel::Warning ? YELLOW "[WARNING"
                                        : GREEN "[STATUS",
           RESET);

    (std::cout << ... << printables);
    putc('\n', stdout);
#endif
  }
} // namespace rwl::impl
