.data
x: .word 0
4: .word 0
x: .word 0
z: .word 0
.text
li $t0 , 3
sw $t0 , x
li $t0 , 4
sw $t0 , 4
li $t0 , x
sw $t0 , x
li $t0 , 1
sw $t0 , z
