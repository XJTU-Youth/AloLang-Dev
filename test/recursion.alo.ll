; ModuleID = './../test/recursion.alo.bc'
source_filename = "test.ll"

declare void @_alolang_12testPrintInt3int(i64)

define void @_alolang_3rec3int(i64 %a) {
entry:
  %a1 = alloca i64, align 8
  store i64 %a, i64* %a1, align 4
  %0 = load i64, i64* %a1, align 4
  %1 = icmp slt i64 %0, 10
  br i1 %1, label %3, label %2

2:                                                ; preds = %3, %entry
  ret void

3:                                                ; preds = %entry
  %4 = load i64, i64* %a1, align 4
  call void @_alolang_12testPrintInt3int(i64 %4)
  %5 = load i64, i64* %a1, align 4
  %6 = add i64 %5, 1
  store i64 %6, i64* %a1, align 4
  %7 = load i64, i64* %a1, align 4
  call void @_alolang_3rec3int(i64 %7)
  br label %2
}

define void @main() {
entry:
  call void @_alolang_3rec3int(i64 0)
  ret void
}
