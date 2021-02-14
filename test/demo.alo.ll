; ModuleID = './../test/demo.alo.bc'
source_filename = "test.ll"

define void @_alolang_8testPuts() {
entry:
  ret void
}

define void @_alolang_12testPrintInt3int(i64 %i) {
entry:
  ret void
}

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
