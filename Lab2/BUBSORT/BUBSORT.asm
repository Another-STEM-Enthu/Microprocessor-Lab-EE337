ORG 0H

LJMP MAIN
ORG 100H
MAIN:
CALL SORT
HERE: SJMP HERE
ORG 130H
// *****************
SORT:
// 60H <= 61H

MOV R0, #60H
MOV R1, #70H
MOV R2, #08H		//counter

loop: MOV A, @R0
MOV @R1,A
INC R0
INC R1
DJNZ R2, loop


MOV R6,#08H		//main counter

iterate : MOV R0,#70H
MOV R7,#07H //swap counter
MOV A,#01H		//to ensure that it zero flag isn't zero due to any other cause

start : MOV A,@R0
INC R0
MOV B,@R0
CLR C
SUBB A,B

//carry means A<B, don't do anything here.
//jump if carry, to NOT swap stuff

JC dontswap
//swap stuff here
//R0 points to the higher mem loc
MOV A,@R0	//content of higher mem loc
DEC R0
MOV B,@R0	//content of lower mem loc
MOV @R0,A	//content of higher mem loc to lower mem loc
INC R0
MOV @R0,B	//content of lower mem loc to higher mem loc





dontswap : MOV A,#01H //to ensure that it zero flag isn't zero due to any other cause
DEC R7
MOV A,R7
JNZ start

DEC R6
MOV A, R6
JZ store
LJMP iterate


store : RET
END