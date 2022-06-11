.data 
	n: .word 8
	array: .word 45, 23, 11, 67, 48, 34, 98, 54


.text 
lw $a0, n 	
la $a1, array 
jal sortarray

printInts: 
	move $t0, $a0 		
	li $v0, 1 		
	loop: 
	ble $t0, $zero, exit 	
	lw $a0, ($a1)		
	syscall 		
	addi $a1, $a1, 4 	
	subi  $t0, $t0, 1 	
	j loop

sortarray:
	li $t7, 0 		 	

swappedLoop:   
		move $t6, $a0 	 	
		subi $t6, $t6, 1 	
		bgtz $t7, printInts 	
		li $t7, 1 		
	loopCount:
	beq $t6, $zero, swappedLoop	
	subi $t5, $t6, 1 		
	mul $t0, $t6, 4 		
	mul $t1, $t5, 4 		
	add $t2, $t0, $a1 		
	add $t3, $t1, $a1 		
	lw $t4, ($t2)			
	lw $t5, ($t3)			
	blt $t4, $t5, swapPositions 	
	
	subi $t6, $t6, 1 		
	j loopCount 			

swapPositions: 
	sw  $t5, ($t2) 			
	sw  $t4, ($t3)			
	subi $t6, $t6, 1 		
	li $t7, 0 			
	j loopCount			


exit: 
	li $v0, 10  			
	syscall 
	
