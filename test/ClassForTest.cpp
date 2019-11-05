//
// Created by 2ToThe10th
//

#include "ClassForTest.h"
#include "FiniteStateMachine.h"
#include <algorithm>
unsigned int ClassForTest::Do() {
  auto *finite_state_machine = new FiniteStateMachine(language);
  finite_state_machine->Invert();
  std::reverse(pattern.begin(), pattern.end());
  unsigned int return_answer = finite_state_machine->FindAnswer(pattern);
  delete finite_state_machine;
  return return_answer;
}
