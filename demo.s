	.file	"demo.c"
	.option pic
	.attribute arch, "rv32i2p1"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
#APP
	li sp, 0x100000
	jal main
	mv a1, x10
	li a7, 10
	ecall
	.globl	__mulsi3
#NO_APP
	.align	2
	.globl	getIntSquareRoot
	.type	getIntSquareRoot, @function
getIntSquareRoot:
	beq	a0,zero,.L12
	addi	sp,sp,-16
	sw	s0,8(sp)
	sw	s1,4(sp)
	sw	ra,12(sp)
	li	a5,1
	mv	s1,a0
	li	s0,1
	beq	a0,a5,.L13
.L4:
	addi	s0,s0,1
	mv	a1,s0
	mv	a0,s0
	call	__mulsi3@plt
	bgtu	s1,a0,.L4
	mv	a0,s0
.L1:
	lw	ra,12(sp)
	lw	s0,8(sp)
	lw	s1,4(sp)
	addi	sp,sp,16
	jr	ra
.L12:
	li	a0,0
	ret
.L13:
	li	a0,1
	j	.L1
	.size	getIntSquareRoot, .-getIntSquareRoot
	.align	2
	.globl	rem
	.type	rem, @function
rem:
	bgtu	a1,a0,.L19
.L16:
	sub	a0,a0,a1
	bleu	a1,a0,.L16
.L19:
	ret
	.size	rem, .-rem
	.section	.text.startup,"ax",@progbits
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-16
	sw	s1,4(sp)
	li	s1,4096
	sw	s0,8(sp)
	sw	ra,12(sp)
	li	s0,1
	addi	s1,s1,-1740
.L21:
	addi	s0,s0,1
	mv	a1,s0
	mv	a0,s0
	call	__mulsi3@plt
	ble	a0,s1,.L21
	li	a3,4096
	li	a5,3
	li	a4,3
	addi	a3,a3,-1739
	bleu	s0,a5,.L28
.L22:
	mv	a5,a3
	bgt	a4,a3,.L25
.L24:
	sub	a5,a5,a4
	bleu	a4,a5,.L24
	beq	a5,zero,.L27
.L25:
	addi	a4,a4,2
	bgtu	s0,a4,.L22
.L28:
	li	a0,1
.L20:
	lw	ra,12(sp)
	lw	s0,8(sp)
	lw	s1,4(sp)
	addi	sp,sp,16
	jr	ra
.L27:
	li	a0,0
	j	.L20
	.size	main, .-main
	.ident	"GCC: (GNU) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
