# 基本型

名前... 言語での名前 <br>
Kind... [`TypeInfo`](/include/TypeInfo.h) が持つ `kind` の種類 <br>
構造体... 処理系の実装

## 一覧表

| | | | |
|-|-|-|-|
| 名前      | Kind          | 構造体   | 内部データ型
| `object`  | `TYPE_Object` | `Object`          |
| `none`    | `TYPE_None`   | `ObjNone`         |
| `int`     | `TYPE_Int`    | `ObjNum<int64_t>` | `int64_t`
| `float`   | `TYPE_Float`  | `ObjNum<double>`  | `double`
| `bool`    | `TYPE_Bool`   | `ObjBool`         | `bool`
| `char`    | `TYPE_Char`   | `ObjChar`         | `char16_t`
| `string`  | `TYPE_String` | `ObjString`       | `std::u16string`
| `vector`  | `TYPE_Vector` | `ObjVector`       | `std::vector<Object*>`

## 基底クラス (`object`)
Metro では、全ての型は `object` の派生クラスという扱いになります。（C#, Java と同じ)

## 数値型

float は、内部表現は F64 (double) が使用されています。<br>
また、数値型は将来的には全て多倍長整数を導入する予定です。<br>

- `int` <br>

```cpp
struct ObjLong : Object {
  int64_t value;
  ...
};
```

## 文字・文字列
- `char`
- `string`
```cpp
struct ObjChar : Object {
  char16_t code;
  ...
};

struct ObjString : Object {
  std::vector<ObjChar*> characters;
  ...
};
```






# 内部表現 (オブジェクト)
先述の `ObjNum<T>`, `ObjBool` などは全て [`Object`](/include/Object.h) の派生クラスです。<br>
C# や Java と同じように、言語側からも `object` として使用可能です。<br>

