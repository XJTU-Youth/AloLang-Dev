; ModuleID = './module'
source_filename = "test.ll"

@0 = private unnamed_addr constant [17 x i8] c"just for debug!\0A\00", align 1

define void @testPuts() {
entry:
  %0 = call i32 @puts(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @0, i32 0, i32 0))
  ret void
}

declare i32 @puts(i8*)

define void @demo() {
entry:
  call void @testPuts()
  ret void
}

define void @main() {
entry:
  call void @demo()
  ret void
}
