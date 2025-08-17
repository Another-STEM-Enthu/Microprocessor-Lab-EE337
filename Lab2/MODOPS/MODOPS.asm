// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
MOV R1, #61H
CALL MODADD
CALL MODSUB
HERE: SJMP HERE
ORG 130H
// *****************


MODADD:
MOV B, 71H
MOV A, 70H
ADD A,B
JNC nocarry

loopit : MOV A, 70H
MOV B, R1
DIV AB
MOV R6, B
MOV A, 71H
MOV B, R1
DIV AB
MOV R7, B
MOV A, R6
MOV B, R7
ADD A, B
MOV B, R1
DIV AB
MOV A, B
MOV 72H, A
JMP done

nocarry : MOV B,R1
DIV AB
MOV A,B //moving the remiander from B to A
MOV 72H,A
done : RET

MODSUB:
MOV B, 71H
MOV A, 70H
CLR C
SUBB A,B
//if carry is not set, use JNC and go for division by 61H; else, apply corrective measures
//the subtraction gives a negative result
//to tackle this : let the result be -x (x>=0)
// first get x; do x mod 61H; and now do 61H - x to get final result
JNC POS
MOV B,A 
MOV A, #0FFH
CLR C
SUBB A,B //Subtracting content of A from 255
INC A //adding 1 to A
//A now has x(>=0)

MOV B,R1
DIV AB
//we now have x mod 61H in B
MOV A, R1
CLR C
SUBB A,B
JNC NEG
//61H - (x mod 61H)

//the subtraction gives a positive result
POS : MOV B,R1
DIV AB
MOV A,B //moving the remiander from B to A

NEG : MOV 73H,A
RET


END