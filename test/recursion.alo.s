	.text
	.file	"test.ll"
	.globl	_alolang_3rec                   # -- Begin function _alolang_3rec
	.p2align	4, 0x90
	.type	_alolang_3rec,@function
_alolang_3rec:                          # @_alolang_3rec
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	$1, (%rsp)
	movb	$1, %al
	testb	%al, %al
	je	.LBB0_2
# %bb.1:
	callq	_alolang_3rec@PLT
.LBB0_2:
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	_alolang_3rec, .Lfunc_end0-_alolang_3rec
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
	callq	_alolang_3rec@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
