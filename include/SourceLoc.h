#pragma once

#include <string>

struct SourceLoc {
  std::string path;
  std::string data;

  SourceLoc(std::string path, std::string data)
    : path(std::move(path)),
      data(std::move(data))
  {
  }

  // => Lexer.cpp
  static SourceLoc from_text_file(std::string const &path);
};
