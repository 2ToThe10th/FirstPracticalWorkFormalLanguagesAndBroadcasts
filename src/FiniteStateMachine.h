#include <string>
#include <vector>
//
// Created by 2ToThe10th
//

#ifndef FINITESTATEMACHINE_H_
#define FINITESTATEMACHINE_H_

class FiniteStateMachine {
private:
  void Error();

  unsigned int dfs(unsigned int vertex, std::string &pattern,
                   unsigned int position,
                   std::vector< std::vector<int> > &previous_answer);

  struct Node {
    std::vector<unsigned int> epsilon;
    std::vector<unsigned int> a;
    std::vector<unsigned int> b;
    std::vector<unsigned int> c;

    void AddA(unsigned int where) { a.push_back(where); }
    void AddB(unsigned int where) { b.push_back(where); }
    void AddC(unsigned int where) { c.push_back(where); }
    void AddEpsilon(unsigned int where) { epsilon.push_back(where); }
  };

  unsigned int start_node;
  unsigned int finish_node;

  std::vector<Node> states;

public:
  explicit FiniteStateMachine(std::string &language);

  void Invert();

  unsigned int FindAnswer(std::string &pattern);
};

#endif // FINITESTATEMACHINE_H_
