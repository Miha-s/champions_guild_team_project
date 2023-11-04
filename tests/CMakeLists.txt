enable_testing()

add_executable(
  LexerTest
  lexer/LexerTest.cpp
)

add_executable(
  AlgorithmsTest
  algorithms/AlgorithmsTest.cpp
)

target_link_libraries(
  LexerTest
  parsing
  GTest::gtest_main
)

target_link_libraries(
  AlgorithmsTest
  grammar
  GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(LexerTest)
gtest_discover_tests(AlgorithmsTest)
