	.text
	.file	"test.ll"
	.globl	"_alolang_2te1(1a3int"          # -- Begin function _alolang_2te1(1a3int
	.p2align	4, 0x90
	.type	"_alolang_2te1(1a3int",@function
"_alolang_2te1(1a3int":                 # @"_alolang_2te1(1a3int"
	.cfi_startproc
# %bb.0:                                # %entry
	retq
.Lfunc_end0:
	.size	"_alolang_2te1(1a3int", .Lfunc_end0-"_alolang_2te1(1a3int"
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	_alolang_8testPuts@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
