	.text
	.file	"loop.alo"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	$0, (%rsp)
	.p2align	4, 0x90
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	movq	(%rsp), %rdi
	callq	_alolang_12testPrintInt3int@PLT
	movq	(%rsp), %rax
	incq	%rax
	movq	%rax, (%rsp)
	cmpq	$10, %rax
	jl	.LBB0_1
# %bb.2:
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
