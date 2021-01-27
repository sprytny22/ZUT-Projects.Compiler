.data
x: .word 0
result1: .word 0
result2: .word 0
z: .word 0

.text
li $t0, 3
sw $t0, x
li $t0, 2
lw $t1, x
mul $t0, $t0, $t1
sw $t0, result1
lw $t0, result1
li $t1, 5
add $t0, $t0, $t1
sw $t0, result2
lw $t0, result2
sw $t0, z
