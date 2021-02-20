	.text
	.file	"test.ll"
	.globl	_alolang_4demo                  # -- Begin function _alolang_4demo
	.p2align	4, 0x90
	.type	_alolang_4demo,@function
_alolang_4demo:                         # @_alolang_4demo
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	_alolang_8testPuts@PLT
	movl	$1, %edi
	callq	_alolang_12testPrintInt3int@PLT
	movl	$11, %edi
	callq	_alolang_12testPrintInt3int@PLT
	movl	$511, %edi                      # imm = 0x1FF
	callq	_alolang_12testPrintInt3int@PLT
	movl	$2, %edi
	callq	_alolang_12testPrintInt3int@PLT
	movl	$65536, %edi                    # imm = 0x10000
	callq	_alolang_12testPrintInt3int@PLT
	movq	$-1, %rdi
	callq	_alolang_12testPrintInt3int@PLT
	movl	$8192, %edi                     # imm = 0x2000
	callq	_alolang_12testPrintInt3int@PLT
	movq	$-1, %rdi
	callq	_alolang_12testPrintInt3int@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	_alolang_4demo, .Lfunc_end0-_alolang_4demo
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
	callq	_alolang_4demo@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
