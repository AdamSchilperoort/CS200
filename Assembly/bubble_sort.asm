	.data
array: .word 20, 1, -10, 24, 49, 87, 23, 11, -12, 34

	.text
	.globl main
main:
	la $s0, array
	addi $s0, $s0, 40
	la $t0, array
	li $t5, 1

print_out:
	beq $t0, $s0, end_loop
	lw $a0, 0($t0)
	li $v0, 1
	syscall

	li $v0, 11
	li $a0, '\n'
	syscall

	addi $t0, $t0, 4
	b print_out

end_loop:
	li $v0, 11
	li $a0, '\n'
	syscall
	li $v0, 10
	beq $t5, 1, load_sort
	syscall

make_print:
	la $t0, array
	b print_out

load_sort:
	la $s1, array
	addi $s1, $s1, 36
	la $t2, array
	addi $t2, $t2, -4
	beq $t5, 0, make_print
	li $t5, 0

sort:
	addi $t2, $t2, 4
	bge $t2, $s1, load_sort
	lw $t3, 0($t2)
	lw $t4, 4($t2)
	bgt $t3, $t4, swap_nums
	b sort

swap_nums:
	sw $t3, 4($t2)
	sw $t4, 0($t2)
	addi $t2, $t2, 4
	li $t5, 1
	b sort
