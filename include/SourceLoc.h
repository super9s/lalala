#pragma once

#include <string>

// impl: Lexer.cpp

struct SourceLoc {
  std::string path;
  std::string data;

  SourceLoc(std::string path, std::string data)
    : path(std::move(path)),
      data(std::move(data))
  {
  }

  static SourceLoc from_text_file(std::string const &path);
};
