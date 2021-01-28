.data
a: .word 0
b: .word 0
c: .word 0
x: .word 0
y: .word 0
z: .word 0

.text
li $t0, 10
sw $t0, a
li $t0, 11
sw $t0, b
li $t0, 0
sw $t0, c
lw $t2, b
lw $t3, a
ble $t2, $t3, LABEL1
li $t0, 0
sw $t0, x
LABEL1:
lw $t2, c
lw $t3, a
bge $t2, $t3, LABEL2
li $t0, 0
sw $t0, y
LABEL2:
lw $t2, b
lw $t3, a
beq $t2, $t3, LABEL3
li $t0, 0
sw $t0, z
LABEL3:
