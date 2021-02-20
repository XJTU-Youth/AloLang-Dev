; ModuleID = './../test/demoa+b.alo.bc'
source_filename = "../test/demoa+b.alo"

declare void @_alolang_12testPrintInt3int(i64)

declare void @_alolang_10testGetInt()

define void @main() {
entry:
  %c = alloca i64, align 8
  %b = alloca i64, align 8
  %a = alloca i64, align 8
  store i64 2, i64* %a, align 4
  %0 = load i64, i64* %a, align 4
  %1 = load i64, i64* %b, align 4
  %2 = load i64, i64* %c, align 4
  store i64 9, i64* %b, align 4
  %3 = load i64, i64* %a, align 4
  %4 = load i64, i64* %b, align 4
  %5 = add i64 %3, %4
  store i64 %5, i64* %c, align 4
  %6 = load i64, i64* %c, align 4
  call void @_alolang_12testPrintInt3int(i64 %6)
  ret void
}
