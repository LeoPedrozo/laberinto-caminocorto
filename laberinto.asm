        .data
MSG1:           .asciiz "sample 2D array access\n"
MSG2:           .asciiz "Enter the row number: "
MSG3:           .asciiz "Enter the column number: "
MSG4:           .asciiz "The value is: "
                .align  2
TWOD:           .word   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25
EOL:            .byte   '\n'
                .align  2
                .text
                .globl  main
main:
                li $v0,4        #syscall para imprimir cadena
                la $a0, MSG1    #cargar la direccion de la cadena
                syscall
#######################################################################
                li $v0,4        #syscall para imprimir cadena
                la $a0, MSG2    #cargar la direccion de la cadena
                syscall
                li $v0, 5       #leer el numero de la fila
                syscall
                move $t0, $v0   #guardar en un temporal la fila
                li $v0, 4
                la $a0, MSG3    #cargar el mensaje 3
                syscall
                li $v0, 5       #leer el numero de la columna
                syscall
                move $t1, $v0   #guardar en un temporal la columna
                move $a0, $t0   #fila como argumento
                move $a1, $t1   #columna como argumento
                li $a2, 20      #tamaño de la fila en $a2
                li $a3, 4       #tamaño de la columna en $a3
#######################################################################
                addiu $sp, $sp, -4      #obtener espacio del stack
                sw $ra, 0($sp)          #guardar el return address
                jal GETOFF              #llamar a get offset
                lw $ra, 0($sp)          #restore return address
                addi $sp, $sp, 4        #restore stack space

                la $t1, TWOD            #obtener la direccion del array
                add $t1,$v0, $t1        #agregar el offset al array
                li $v0, 4               #servicio de impresion de cadena
                la $0, MSG4             #cargar la direccion de la cadena
                syscall
                li $v0,1                #servicio de impresion de cadena
                lw $a0,0($t1)           #obtener el numero del array
                syscall                 #imprimir el numero
                jr $ra

#####################################################################
#GETOFF : recibe la fila que se desea en $a0, la columna en $a1,
#       tamanho de la fila en $a2, y tamanho de la columna en $a3
#       Obs: Los tamanhos son en bytes
#       El retorno se guardara en $v0
#####################################################################
GETOFF:
        move $s0, $a0           #guardar el numero de la fila
        move $s1 , $a1          #guardar el numero de la columna
        move $s2 , $a2          #guardar el tamanho de la fila (bytes)
        move $s3 , $a3          #guardar el tamanho de la columna (bytes)

        addiu $s0 ,$s0, -1      #restar uno a la fila
        addiu $s1 ,$s1, -1      #restar uno a la columna
        mul $s0, $s0, $s2       #calcular el offset de la fila
        mul $s1, $s1, $s3       #calcular el offset de la columna
        add $v0, $s0, $s1
        jr $ra
