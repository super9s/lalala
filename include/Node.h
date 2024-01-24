#pragma once

#include <vector>
#include "Token.h"
#include "Object.h"

enum NodeKind {
  ND_Value,
  ND_Variable,

  ND_Add,
};

struct Node {
  NodeKind kind;
  Token *token;
  Node *lhs, *rhs;
  std::vector<Node> list;
};
