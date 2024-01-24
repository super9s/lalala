# 基本型

| | | | |
|-|-|-|-|
| 名前      | Kind          | オブジェクト型   | 内部データ型
| `object`  | `TYPE_Object` | `Object`          |
| `none`    | `TYPE_None`   | `ObjNone`         |
| `int`     | `TYPE_Int`    | `ObjNum<int64_t>` | `int64_t`
| `float`   | `TYPE_Float`  | `ObjNum<double>`  | `double`
| `bool`    | `TYPE_Bool`   | `ObjBool`         | `bool`
| `char`    | `TYPE_Char`   | `ObjChar`         | `char16_t`
| `string`  | `TYPE_String` | `ObjString`       | `std::u16string`
| `vector`  | `TYPE_Vector` | `ObjVector`       | `std::vector<Object*>`

float は、内部表現は F64 (double) が使用されています。<br>
また、数値型は将来的には全て多倍長整数を導入する予定です。<br>

# 内部表現 (オブジェクト)
先述の `ObjNum<T>`, `ObjBool` などは全て [`Object`](/include/Object.h) の派生クラスです。<br>
C# や Java と同じように、言語側からも `object` として使用可能です。<br>

