#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/emulator.h"

// Global counters for tests
int total_tests = 0;
int passed_tests = 0;
int failed_tests = 0;

// Macros for assertions
#define ASSERT_EQUAL(actual, expected)                                                              \
    do {                                                                                            \
        total_tests++;                                                                              \
        if ((actual) == (expected)) {                                                               \
            passed_tests++;                                                                         \
            printf("[PASS] %s:%d - %s == %s\n", __FILE__, __LINE__, #actual, #expected);            \
        } else {                                                                                    \
            failed_tests++;                                                                         \
            printf("[FAIL] %s:%d - Expected %s, got %s\n", __FILE__, __LINE__, #expected, #actual); \
        }                                                                                           \
    } while (0)


#define ASSERT_NOT_EQUAL(actual, expected)                           \
    do {                                                             \
        total_tests++;                                               \
        if ((actual) != (expected)) {                                \
            passed_tests++;                                          \
            printf("[PASS] %s:%d - %s != %s\n",                      \
                   __FILE__, __LINE__, #actual, #expected);          \
        } else {                                                     \
            failed_tests++;                                          \
            printf("[FAIL] %s:%d - %s == %s (unexpected)\n",         \
                   __FILE__, __LINE__, #actual, #expected);          \
        }                                                            \
    } while (0)




void test_initializations();

#endif // TEST_FRAMEWORK_H