
	.data
array:	.word 30, 2, -9, 20, 19, 86, 21, 8, -15, 32

	.text
	.globl main

main:
	jal print
	jal sort
	jal print
	li $v0, 10 # code for ’exit’
	syscall


print_loop:
	beq $t0, $s0, end_loop
	lw $a0, 0($t0)
	li $v0, 1
	syscall

	li $v0, 11
	li $a0, '\n'
	syscall

  # goes 4 bytes forward for the next word
	addi $t0, $t0, 4
	b print_loop

end_loop:

	li $v0, 11
	li $a0, '\n'
	syscall
	jr $ra

print:
	la $s0, array
	addi $s0, $s0, 40
	la $t0, array
	li $t5, 1
	b print_loop

ret:
	jr $ra

sort:
	la $s1, array
	addi $s1, $s1, 36
	la $t2, array
	addi $t2, $t2, -4
	beq $t5, 0, ret
	li $t5, 0

sort_items:
	addi $t2, $t2, 4
	bge  $t2, $s1, sort
	lw $t3, 0($t2)
	lw $t4, 4($t2)
	bgt $t3, $t4, swap_items
	b sort_items

swap_items:
	sw $t3, 4($t2)
	sw $t4, 0($t2)
	addi $t2, $t2, 4
	li $t5, 1
	b sort_items
