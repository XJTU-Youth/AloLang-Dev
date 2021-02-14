; ModuleID = './../test/demo.alo.bc'
source_filename = "test.ll"

declare void @_alolang_8testPuts()

declare void @_alolang_12testPrintInt3int(i64)

define void @_alolang_4demo() {
entry:
  call void @_alolang_8testPuts()
  call void @_alolang_12testPrintInt3int(i64 1)
  call void @_alolang_12testPrintInt3int(i64 11)
  call void @_alolang_12testPrintInt3int(i64 511)
  ret void
}

define void @main() {
entry:
  call void @_alolang_4demo()
  ret void
}
