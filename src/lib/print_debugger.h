#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

namespace Utilities {
namespace PrintDebugger {
#define PRINT_STREAM stdout
#define PRINT_FLUSH fflush(PRINT_STREAM);
#define PRINT(string)              \
  do {                             \
    fprintf(PRINT_STREAM, string); \
  } while (0)
#define PRINT_NOW(fmt, ...)                  \
  do {                                       \
    fprintf(PRINT_STREAM, fmt, __VA_ARGS__); \
    PRINT_FLUSH                              \
  } while (0)
#define PRINT_HEADER1(headerString)                                            \
  do {                                                                         \
    PRINT_NOW("\n%s:%d %s: %s\n=======================\n", __FILE__, __LINE__, \
              __func__, headerString);                                         \
  } while (0)
#define PRINT_HEADER2(headerString)                                            \
  do {                                                                         \
    PRINT_NOW("\n%s:%d %s: %s\n-----------------------\n", __FILE__, __LINE__, \
              __func__, headerString);                                         \
  } while (0)
#define PRINT_VARIABLE(x_format, x)                                       \
  do {                                                                    \
    PRINT_NOW("%d:   %s: %s: " x_format "\n", __LINE__, __func__, #x, x); \
  } while (0)
#define PRINT_BLOCK if (true)
#define PRINT_ERROR(fmt, ...)    \
  do {                           \
    PRINT("ERROR: ");            \
    PRINT_NOW(fmt, __VA_ARGS__); \
    PRINT("\n");                 \
    exit(1);                     \
  } while (0)

#define DEBUG_STREAM PRINT_STREAM
#define DEBUG_PRINT(fmt, ...) fprintf(DEBUG_STREAM, fmt, __VA_ARGS__)
#define DEBUG_FLUSH fflush(DEBUG_STREAM);

#ifdef DEBUG
#define DEBUG_BLOCK if (true)
#define DEBUG_LITERAL(s) \
  do {                   \
    DEBUG_PRINT(s);      \
  } while (0)
#define DEBUG_NOW(fmt, ...)        \
  do {                             \
    DEBUG_PRINT(fmt, __VA_ARGS__); \
    DEBUG_FLUSH                    \
  } while (0)
#define DEBUG_HEADER1(headerString)                                            \
  do {                                                                         \
    DEBUG_NOW("\n%s:%d %s: %s\n=======================\n", __FILE__, __LINE__, \
              __func__, headerString);                                         \
  } while (0)
#define DEBUG_HEADER2(headerString)                                            \
  do {                                                                         \
    DEBUG_NOW("\n%s:%d %s: %s\n-----------------------\n", __FILE__, __LINE__, \
              __func__, headerString);                                         \
  } while (0)
#define DEBUG_VARIABLE(x_format, x)                                       \
  do {                                                                    \
    DEBUG_NOW("%d:   %s: %s: " x_format "\n", __LINE__, __func__, #x, x); \
  } while (0)
#else
#define DEBUG_LITERAL(s)
#define DEBUG_NOW(fmt, ...)
#define DEBUG_BLOCK if (false)
#define DEBUG_HEADER1(headerString)
#define DEBUG_HEADER2(headerString)
#define DEBUG_VARIABLE(fmt, ...)
#endif
}
}
