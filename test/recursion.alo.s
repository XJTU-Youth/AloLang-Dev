	.text
	.file	"test.ll"
	.globl	_alolang_3rec3int               # -- Begin function _alolang_3rec3int
	.p2align	4, 0x90
	.type	_alolang_3rec3int,@function
_alolang_3rec3int:                      # @_alolang_3rec3int
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	%rdi, (%rsp)
	cmpq	$10, %rdi
	jge	.LBB0_2
# %bb.1:
	movq	(%rsp), %rdi
	callq	_alolang_12testPrintInt3int@PLT
	movq	(%rsp), %rdi
	incq	%rdi
	movq	%rdi, (%rsp)
	callq	_alolang_3rec3int@PLT
.LBB0_2:
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	_alolang_3rec3int, .Lfunc_end0-_alolang_3rec3int
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
	xorl	%edi, %edi
	callq	_alolang_3rec3int@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
