#pragma once

#include <functional>
#include "Token.h"
#include "SourceLoc.h"

class Lexer {

public:
  Lexer(SourceLoc &source)
    : source(source),
      src(source.data),
      position(0),
      length(source.data.length())
  {
  }

  ~Lexer()
  {
  }

  bool check();
  char peek();
  void pass_space();
  bool eat(std::string_view str);
  bool match(std::string_view str);
  size_t pass_while(std::function<bool(char)> cond);

  Token *lex();

private:
  SourceLoc const &source;
  std::string const &src;
  size_t position;
  size_t const length;
};