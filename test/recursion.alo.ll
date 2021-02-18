; ModuleID = './../test/recursion.alo.bc'
source_filename = "test.ll"

define void @_alolang_3rec() {
entry:
  %a = alloca i64, align 8
  store i64 0, i64* %a, align 4
  %0 = load i64, i64* %a, align 4
  %1 = load i64, i64* %a, align 4
  %2 = add i64 %1, 1
  store i64 %2, i64* %a, align 4
  %3 = load i64, i64* %a, align 4
  %4 = icmp slt i64 %3, 50
  br i1 %4, label %6, label %5

5:                                                ; preds = %6, %entry
  ret void

6:                                                ; preds = %entry
  call void @_alolang_3rec()
  br label %5
}

define void @main() {
entry:
  call void @_alolang_3rec()
  ret void
}
