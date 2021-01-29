.data
x: .word 0
z: .float 0
result1: .word 0
w: .word 0

.text
li $t0, 2
sw $t0, x

li $t0, 2.100000
sw $t0, z

li $t0, 2
lw $t1, z
add $t0, $t0, $t1
sw $t0, result1
lw $t0, result1
sw $t0, w

li $v0, 1
lw $a0, w
syscall

