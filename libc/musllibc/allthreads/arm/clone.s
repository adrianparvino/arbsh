.text
.global __clone
.weak clone
.type   __clone,%function
.type   clone,%function
__clone:
clone:
	stmfd sp!,{r4,r5,r6,r7}
	mov r7,#120
	mov r6,r3
	mov r5,r0
	mov r0,r2
	and r1,r1,#-16
	ldr r2,[sp,#16]
	ldr r3,[sp,#20]
	ldr r4,[sp,#24]
	svc 0
	tst r0,r0
	beq 1f
	ldmfd sp!,{r4,r5,r6,r7}
	tst lr,#1
	moveq pc,lr
	bx lr

1:	mov r0,r6
	tst r5,#1
	bne 1f
	mov lr,pc
	mov pc,r5
2:	mov r1,r0
	mov r0,#1
	svc 0

1:	blx r5
	b 2b
