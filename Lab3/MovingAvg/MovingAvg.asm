// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL FILT
HERE: SJMP HERE
ORG 130H
// *****************
FILT:
MOV R0, #60H	//the source 

//setting initial values
DEC R0
MOV @R0, #00H
DEC R0
MOV @R0, #00H
DEC R0
MOV @R0, #00H


MOV R4, #08H	//the counter
MOV R0, #60H	//the source 
MOV R1, #70H    //the destination

loopit : MOV A, @R0
DEC R0
ADD A,@R0
DEC R0
ADD A,@R0
DEC R0
ADD A,@R0
INC R0
INC R0
INC R0

MOV B, #04
DIV AB
MOV @R1,A

INC R0
INC R1
DJNZ R4, loopit

RET
END
