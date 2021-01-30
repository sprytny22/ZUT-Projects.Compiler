.data
x: .word 0
y: .word 0
v: .word 0
result1: .word 0
result2: .word 0
result3: .word 0
w: .word 0

.text
li $t0, 2
sw $t0, x

li $t0, 2
sw $t0, y

li $t0, 3
li $t1, 2
add $t0, $t0, $t1
sw $t0, result1
lw $t0, result1
li $t1, 1
add $t0, $t0, $t1
sw $t0, result2
lw $t0, result2
lw $t1, x
add $t0, $t0, $t1
sw $t0, result3
lw $t0, result3
sw $t0, w

li $t2, 0
li $t3, 0
beq $t2, $t3, LABEL1
li $v0, 1
lw $a0, w
syscall

LABEL1: 

li $v0, 5
syscall
sw $v0, v

li $v0, 1
lw $a0, v
syscall

