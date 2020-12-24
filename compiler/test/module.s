	.text
	.file	"test.ll"
	.globl	testPuts                        # -- Begin function testPuts
	.p2align	4, 0x90
	.type	testPuts,@function
testPuts:                               # @testPuts
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	leaq	.L__unnamed_1(%rip), %rdi
	callq	puts@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	testPuts, .Lfunc_end0-testPuts
	.cfi_endproc
                                        # -- End function
	.globl	demo                            # -- Begin function demo
	.p2align	4, 0x90
	.type	demo,@function
demo:                                   # @demo
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	testPuts@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	demo, .Lfunc_end1-demo
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
	callq	demo@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_1,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"just for debug!\n"
	.size	.L__unnamed_1, 17

	.section	".note.GNU-stack","",@progbits
