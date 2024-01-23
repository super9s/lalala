#pragma once

#include <exception>
#include "Error.h"

class Metro {
public:
  Metro();
  ~Metro();

  static Error &add_error();

private:
};