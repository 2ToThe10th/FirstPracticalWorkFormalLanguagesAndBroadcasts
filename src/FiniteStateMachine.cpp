#include <iostream>
#include <stack>
//
// Created by 2ToThe10th
//

#include "FiniteStateMachine.h"
void FiniteStateMachine::Error() {
  std::cout << "Error\n";
  exit(0);
}

FiniteStateMachine::FiniteStateMachine(std::string &language) {

  struct PartMachine {
    unsigned int start_vertex;
    unsigned int finish_vertex;

    PartMachine(unsigned int start_vertex, unsigned int finish_vertex)
        : start_vertex(start_vertex), finish_vertex(finish_vertex) {}
  };

  std::stack<PartMachine> stack_for_machine;

  for (auto symbol : language) {

    if (symbol == 'a') {
      states.emplace_back();
      states.back().AddA(states.size());
      states.emplace_back();
      stack_for_machine.emplace(states.size() - 2, states.size() - 1);
    }
    if (symbol == 'b') {
      states.emplace_back();
      states.back().AddB(states.size());
      states.emplace_back();
      stack_for_machine.emplace(states.size() - 2, states.size() - 1);
    }
    if (symbol == 'c') {
      states.emplace_back();
      states.back().AddC(states.size());
      states.emplace_back();
      stack_for_machine.emplace(states.size() - 2, states.size() - 1);
    }
    if (symbol == '1') {
      states.emplace_back();
      states.back().AddEpsilon(states.size());
      states.emplace_back();
      stack_for_machine.emplace(states.size() - 2, states.size() - 1);
    }
    if (symbol == '+') {
      if (stack_for_machine.size() < 2) {
        Error();
      }
      PartMachine second_machine = stack_for_machine.top();
      stack_for_machine.pop();
      PartMachine first_machine = stack_for_machine.top();
      stack_for_machine.pop();
      states.emplace_back();
      states.back().AddEpsilon(first_machine.start_vertex);
      states.back().AddEpsilon(second_machine.start_vertex);
      states[first_machine.finish_vertex].AddEpsilon(states.size());
      states[second_machine.finish_vertex].AddEpsilon(states.size());
      states.emplace_back();
      stack_for_machine.emplace(states.size() - 2, states.size() - 1);
    }
    if (symbol == '.') {
      if (stack_for_machine.size() < 2) {
        Error();
      }
      PartMachine second_machine = stack_for_machine.top();
      stack_for_machine.pop();
      PartMachine first_machine = stack_for_machine.top();
      stack_for_machine.pop();
      states[first_machine.finish_vertex].AddEpsilon(
          second_machine.start_vertex);
      stack_for_machine.emplace(first_machine.start_vertex,
                                second_machine.finish_vertex);
    }
    if (symbol == '*') {
      if (stack_for_machine.empty()) {
        Error();
      }
      PartMachine machine = stack_for_machine.top();
      stack_for_machine.pop();

      states[machine.finish_vertex].AddEpsilon(machine.start_vertex);

      stack_for_machine.emplace(machine.start_vertex, machine.start_vertex);
    }
  }

  if (stack_for_machine.size() != 1) {
    Error();
  }

  start_node = stack_for_machine.top().start_vertex;
  finish_node = stack_for_machine.top().finish_vertex;
}

unsigned int
FiniteStateMachine::dfs(unsigned int vertex, std::string &pattern,
                        unsigned int position,
                        std::vector<std::vector<int>> &previous_answer,
                        std::vector<std::vector<bool>> &used) {
  if (position == pattern.size()) {
    return position;
  }
  if (previous_answer[vertex][position] >= 0) {
    return previous_answer[vertex][position];
  }
  used[vertex][position] = true;

  unsigned int return_value = position;

  for (auto to : states[vertex].epsilon) {
    if (!used[to][position]) {
      return_value =
          std::max(return_value, dfs(to, pattern, position, previous_answer, used));
    }
  }

  std::vector<unsigned int> *child = nullptr;

  if (pattern[position] == 'a') {
    child = &states[vertex].a;
  } else if (pattern[position] == 'b') {
    child = &states[vertex].b;
  } else if (pattern[position] == 'c') {
    child = &states[vertex].c;
  } else {
    Error();
  }

  for (auto to : *child) {
    return_value =
        std::max(return_value, dfs(to, pattern, position + 1, previous_answer, used));
  }

  previous_answer[vertex][position] = return_value;
  used[vertex][position] = false;
  return return_value;
}

unsigned int FiniteStateMachine::FindAnswer(std::string &pattern) {
  std::vector<std::vector<int>> previous_answer(
      states.size(), std::vector<int>(pattern.size(), -1));
  std::vector<std::vector<bool>> used(
      states.size(), std::vector<bool>(pattern.size(),false));
  return dfs(start_node, pattern, 0, previous_answer, used);
}
void FiniteStateMachine::Invert() {
  std::vector<Node> old_states;
  old_states.swap(states);

  states.resize(old_states.size());

  for (unsigned long i = 0; i < old_states.size(); ++i) {
    for (unsigned long j = 0; j < old_states[i].epsilon.size(); ++j) {
      states[old_states[i].epsilon[j]].epsilon.push_back(i);
    }
    for (unsigned long j = 0; j < old_states[i].a.size(); ++j) {
      states[old_states[i].a[j]].a.push_back(i);
    }
    for (unsigned long j = 0; j < old_states[i].b.size(); ++j) {
      states[old_states[i].b[j]].b.push_back(i);
    }
    for (unsigned long j = 0; j < old_states[i].c.size(); ++j) {
      states[old_states[i].c[j]].c.push_back(i);
    }
  }

  std::swap(start_node, finish_node);
}
