// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL DET
HERE: SJMP HERE
ORG 130H
// *****************

DET:
// r4 will have MSB of a*d and r3 the LSB of a*d
// r6 will have MSB of b*c and r5 the LSB of b*c

MOV A, 60H
MOV B, 63H
MUL AB
MOV R3,A
MOV R4,B

MOV A, 61H
MOV B, 62H
MUL AB
MOV R5,A
MOV R6,B

MOV A,R3
MOV B,R5
CLR C
SUBB A,B
MOV 71H,A

MOV A,R4
MOV B,R6
//CLR C		//Check if this should be there or not
SUBB A,B
MOV 70H,A

RET
END
