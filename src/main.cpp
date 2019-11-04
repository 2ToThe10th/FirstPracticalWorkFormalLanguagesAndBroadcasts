#ifdef DEBUG
#include <gtest/gtest.h>
#endif
#include "FiniteStateMachine.h"
#include <algorithm>
#include <iostream>

int main() {

#ifdef DEBUG
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
#endif

  std::string language;
  std::cin >> language;

  auto finite_state_machine = new FiniteStateMachine(language);
  finite_state_machine->Invert();

  std::string pattern;
  std::cin >> pattern;

  std::reverse(pattern.begin(), pattern.end());

  std::cout << finite_state_machine->FindAnswer(pattern);

  delete finite_state_machine;
  return 0;
}
