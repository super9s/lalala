/*
 * (c) 2023 Aoki
 *
 * Implements of:
 *   SourceLoc.h
 *   Lexer.h
 */

#include <array>
#include <fstream>
#include "Lexer.h"
#include "Error.h"

static std::array<char const *, 5> const punctuaters = {
  "+", "-", "*", "/", "%",
};

// ---------------
//  SourceLoc.h
//    -> SourceLoc::from_text_file()
//
//   Construct a instance from a text file.
// ---------------
SourceLoc SourceLoc::from_text_file(std::string const &path)
{
  std::string data, line;
  std::ifstream ifs{ path };

  if (ifs.fail())
    throw std::invalid_argument("cannot open file");

  while (std::getline(ifs, line))
    data.append(line).append("\n");

  return { data, line };
}

// ---------------
//  Lexer.h
//    -> Lexer::check()
//
//  Check if current position is in range of source code.
// ---------------
bool Lexer::check()
{
  return this->position < this->length;
}

// ---------------
//  Lexer.h
//    -> Lexer::peek()
//
//  Get the character on current position.
// ---------------
char Lexer::peek()
{
  return this->src[this->position];
}

// ---------------
//  Lexer.h
//    -> Lexer::pass_space()
//
//  Skip spaces
// ---------------
void Lexer::pass_space()
{
  while (this->check() && std::isspace(this->peek()))
    this->position++;
}

// ---------------
//  Lexer.h
//    -> Lexer::eat()
//
//  add a count of length of str to Lexer::position if found that.
// ---------------
bool Lexer::eat(std::string_view str)
{
  if (this->match(str)) {
    this->position += str.length();
    return true;
  }

  return false;
}

// ---------------
//  Lexer.h
//    -> Lexer::match()
//
//  Check if found an any string on current pos.
// ---------------
bool Lexer::match(std::string_view str)
{
  return this->position + str.length() <= this->length &&
         this->src.substr(this->position, str.length()) == str;
}

// ---------------
//  Lexer.h
//    -> Lexer::pass_while()
//
//  skip characters which returned true by function @cond.
// ---------------
size_t Lexer::pass_while(std::function<bool(char)> cond)
{
  size_t pos = this->position;

  while (this->check() && cond(this->peek()))
    this->position++;

  return this->position - pos;
}

// ========================
//  Lexer.h
//    -> Lexer::peek()
//
//  LLLEEEEEXXXXXXXXXXXXXX!!!!!!!!!!!!!!!!!!!!!
// ========================
Token *Lexer::lex()
{
  Token top{ TOK_Unknown, this->source };
  Token *cur = &top;

  // skip first spaces
  this->pass_space();

  while (this->check()) {
    auto ch = this->peek();    // save character
    auto pos = this->position; // save position

    // hex
    if (this->eat("0x") || this->eat("0X")) {
      cur =
          new Token(TOK_Int, cur,
                    { this->src.data() + pos, this->pass_while(isxdigit) + 2 },
                    this->source, pos);

      cur->value = std::stoi(std::string(cur->str), nullptr, 16);
    }

    // bin
    else if (this->eat("0b") || this->eat("0B")) {
      cur = new Token(
          TOK_Int, cur,
          { this->src.data() + pos, this->pass_while([](char c) -> bool {
             return c == '0' || c == '1';
           }) + 2 },
          this->source, pos);

      cur->value = std::stoi(std::string(cur->str), nullptr, 2);
    }

    // digit (0 ~ 9)
    else if (std::isdigit(ch)) {
      cur = new Token(TOK_Int, cur,
                      { this->src.data() + pos, this->pass_while(isdigit) },
                      this->source, pos);

      // if found '.', is this a float ?
      if (this->peek() == '.') {
        this->position++;

        if (!this->check())
          break;

        // ended with '.f'
        if (this->peek() == 'f') {
          auto pos2 = ++this->position;

          cur->str = { this->src.data() + pos, pos2 - pos };
          cur->val_double = std::stod(std::string(cur->str));
        }

        // continueing of digits
        else if (isdigit(this->peek())) {
          cur->str = { this->src.data() + pos,
                       cur->str.length() + 1 + this->pass_while(isdigit) };

          cur->val_double = std::stod(std::string(cur->str));
        }

        // not a float literal
        else {
          this->position--; // return to '.'
        }
      }

      // decimal
      else {
        cur->value = std::stoi(std::string(cur->str), nullptr, 10);
      }
    }

    // identifier
    else if (std::isalpha(ch) || ch == '_') {
      cur = new Token(
          TOK_Ident, cur,
          { this->src.data() + pos, this->pass_while([](char c) -> bool {
             return isalnum(c) || c == '_';
           }) },
          this->source, pos);
    }

    // punctuaters or other
    else {
      for (std::string_view pu : punctuaters) {
        if (this->eat(pu)) {
          cur = new Token(TOK_Punct, cur, pu, this->source, pos);
          goto ate_punct;
        }
      }

    ate_punct:;
    }

    // skip spaces.
    this->pass_space();
  }

  cur = new Token(TOK_End, cur, "", this->source, this->position);

  return top.next;
}