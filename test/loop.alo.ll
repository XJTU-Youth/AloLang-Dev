; ModuleID = './../test/loop.alo.bc'
source_filename = "test.ll"

declare void @_alolang_12testPrintInt3int(i64)

define void @main() {
entry:
  %a = alloca i64, align 8
  store i64 0, i64* %a, align 4
  %0 = load i64, i64* %a, align 4
  br label %2

1:                                                ; preds = %2
  ret void

2:                                                ; preds = %2, %entry
  %3 = load i64, i64* %a, align 4
  call void @_alolang_12testPrintInt3int(i64 %3)
  %4 = load i64, i64* %a, align 4
  %5 = add i64 %4, 1
  store i64 %5, i64* %a, align 4
  %6 = load i64, i64* %a, align 4
  %7 = icmp slt i64 %6, 10
  br i1 %7, label %2, label %1
}
