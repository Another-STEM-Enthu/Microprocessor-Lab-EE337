// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL TAKE_INP
CALL QUANT_ENC
CALL LED_DISP

HERE: SJMP HERE
ORG 130H
// *****************

delay_10s:
push 00h
mov r0, #40
h5: acall delay_250ms
djnz r0, h5
pop 00h
ret

delay_5s:
push 00h
mov r0, #20
h4: acall delay_250ms
djnz r0, h4
pop 00h
ret

delay_250ms:
push 00h
mov r0, #250
h3: acall delay_1ms
djnz r0, h3
pop 00h
ret


delay_1ms:
push 00h
mov r0, #4
h2: acall delay_250us
djnz r0, h2
pop 00h
ret


delay_250us:
push 00h
mov r0, #244
h1: djnz r0, h1
pop 00h
ret



TAKE_INP:
MOV R0, #60H
MOV R5, #01		//pointer for LED output
MOV R6, #04		//counter

takein: 
MOV A, #00H
MOV B, #00H


MOV A, R5
SWAP A
MOV P1,A
SETB P1.0
SETB P1.1
SETB P1.2
SETB P1.3
CALL delay_10s
MOV A, P1
ANL A, #0FH
SWAP A
MOV B,A

INC R5

MOV A, R5
SWAP A
MOV P1,A
SETB P1.0
SETB P1.1
SETB P1.2
SETB P1.3
CALL delay_10s
MOV A, P1
ANL A, #0FH
ADD A, B


MOV @R0,A
INC R0
INC R5
DJNZ R6, takein




CLR P1.4
CLR P1.5
CLR P1.6
CLR P1.7
RET



QUANT_ENC:
MOV R4, #04H	//the counter
MOV R0, #60H	//the source 
MOV R1, #70H    //the destination

loop : MOV B, @R0 	//B holds a sample

MOV A, B
ANL A, #10000000B	//remember to check for case when zero occurs
JNZ elsee			//negative number

MOV A, B
CLR C
SUBB A, #10
JNC elseif1
MOV @R1, #5		// >=0 & <10
SJMP done			//end of if

elseif1 : MOV A, B
CLR C
SUBB A, #20
JNC elseif2
MOV @R1, #15		//>=10 & <20
SJMP done			//end of elseif1

elseif2 : MOV A,B
CLR C
SUBB A, #30
JNC elsee
MOV @R1, #25		//>=20 & <30
SJMP done 		//end of elseif2



elsee : MOV @R1,#35

done : INC R0
INC R1
DJNZ R4, loop
RET




LED_DISP:

infloop : CLR C

MOV R4, #04H	//the counter
MOV R0, #70H	//the samples 

displayloop : MOV A, @R0
CLR C
SUBB A,#05
JNZ check15
SETB P1.4
CLR P1.5
CLR P1.6
CLR P1.7
SJMP putthedelay

check15: MOV A, @R0
CLR C
SUBB A, #15
JNZ check25
CLR P1.4
SETB P1.5
CLR P1.6
CLR P1.7
SJMP putthedelay

check25: MOV A, @R0
CLR C
SUBB A, #25
JNZ elsee11
CLR P1.4
CLR P1.5
SETB P1.6
CLR P1.7
SJMP putthedelay

elsee11 : 
CLR P1.4
CLR P1.5
CLR P1.6
SETB P1.7

putthedelay: CALL delay_5s

INC R0
DJNZ R4, displayloop
SJMP infloop
RET
END