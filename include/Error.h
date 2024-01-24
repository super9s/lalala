#pragma once

enum ErrorKind {
  ERR_InvalidToken,
  ERR_InvalidSyntax,

  ERR_TypeMismatch,
};

class Error {
public:
    Error();
};
