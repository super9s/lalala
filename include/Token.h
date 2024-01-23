#pragma once

#include <string>

enum TokenKind {
  TOK_Unknown,
  TOK_Int,
  TOK_Float,
  TOK_Char,
  TOK_String,
  TOK_Ident,
  TOK_Keyword,
  TOK_Punct,
  TOK_End
};

struct Token {
  TokenKind kind;
  Token *prev, *next;
  std::string_view str;
  size_t pos;

  union {
    int64_t value;     // if TOK_Int
    char16_t val_char; // if TOK_Char
    double val_double; // if TOK_Float

    // if TOK_String
    struct {
      char const *vstr_p;
      size_t vs_length;
    };
  };

  Token(TokenKind kind, Token *prev, std::string_view str, size_t pos)
    : kind(kind),
      prev(prev),
      next(nullptr),
      str(str),
      pos(pos),
      value(0)
  {
  }

  Token(TokenKind kind = TOK_Unknown)
    : Token(kind, nullptr, "", 0)
  {
    this->next = nullptr;
  }
};
