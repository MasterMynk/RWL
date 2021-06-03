#pragma once
#include <stdio.h>

#define SET_COLOR(x) "\x1b[" #x "m"

#define RED SET_COLOR(31)
#define GREEN SET_COLOR(32)
#define YELLOW SET_COLOR(33)
#define RESET SET_COLOR(0)

#if RWL_DEBUG == 1
  #define LOG(level, text) printf("%s: %s%s",\
  level == LogLevel::Error ? RED "[ERROR]"\
  : level ==  LogLevel::Status ? GREEN "[Status]"\
  : YELLOW "[Warning]", RESET, (text))
#else
  #define LOG(level, text)
#endif

namespace rwl {
  enum class LogLevel {
    Error = 1,
    Status,
    Warning,
  };
} // namespace rwl
