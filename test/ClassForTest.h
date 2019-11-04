//
// Created by 2ToThe10th
//

#ifndef GAME_TEST_CLASSFORTEST_H_
#define GAME_TEST_CLASSFORTEST_H_

#include <string>
class ClassForTest {
private:
  std::string language;
  std::string pattern;

public:
  ClassForTest(std::string language, std::string pattern)
      : language(language), pattern(pattern) {}

  unsigned int Do();
};

#endif // GAME_TEST_CLASSFORTEST_H_
