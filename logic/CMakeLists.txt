CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(logic LANGUAGES CXX)

ADD_LIBRARY(logic source/logic.cc)

SET_TARGET_PROPERTIES(logic PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_INCLUDE_DIRECTORIES(logic PUBLIC header)

ADD_EXECUTABLE(test-logic test/tests.cc)
SET_TARGET_PROPERTIES(test-logic PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-logic stringify logic Catch2)

ENABLE_TESTING()
ADD_TEST(test-logic test-logic)

