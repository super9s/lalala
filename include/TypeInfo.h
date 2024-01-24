#pragma once

#include <vector>

enum TypeKind {
  TYPE_None,
  TYPE_Int,
  TYPE_Float,
  TYPE_Char,
  TYPE_String,
  TYPE_Vector,
};

struct TypeInfo {
  TypeKind kind;
  std::vector<TypeInfo> params;

  bool is_mutable;

  TypeInfo(TypeKind kind = TYPE_None)
    : kind(kind),
      is_mutable(false)
  {
  }
};
