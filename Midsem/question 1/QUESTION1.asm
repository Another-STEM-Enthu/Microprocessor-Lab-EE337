ORG 0H
LJMP main

ORG 130H
main : 
MOV 70H, #216
MOV 71H, #91


MOV R4, #01H   //this is i
MOV R3, #0FFH	//number of times we'll run the loop, i.e. i<= 255
MOV R7, 70H		//faster to load to A than memory
LJMP multiply
showitt : MOV A, 70H
MOV B, 72H
MUL AB
INC A 
MOV R0, A
MOV R1, B

MOV R5, #00H
divsub : 
MOV R2, 71H
MOV A, R0
MOV B, R2
CLR C
SUBB A, B
MOV R0, A
MOV A, R1
MOV B, #0H
SUBB A,B
MOV R1, A
INC R5
JNZ divsub
INC R5
MOV 72H, R5



//MOV 72H, #05H
LCALL display

multiply: MOV A, R7
MOV B, R4
MUL AB
INC A 			// we now have 216*i + 1, LSB in A
MOV R0, A		//lsb
MOV R1, B		//msb
LCALL checkmod


//now A has the modulus
JZ foundit
MOV B, 71H
CLR C
SUBB A, B
JZ foundit

INC R4
DJNZ R3, multiply
foundit : MOV 72H, R4
LJMP showitt







//check mod takes input such that R0 has LSB and R1 has MSB
checkmod: 	//stores modulus in A
MOV R6, #00H	//k
subtract : INC R6
MOV A, #01H
MOV B, 71H
MUL AB		//A has lsb
MOV R2, B	//MSB OF 173 * k
MOV R5, A	//LSB OF 173 * k
MOV A, R0
MOV B, R5
CLR C
SUBB A, B
MOV R0, A
MOV A, R1
MOV B, R2
SUBB A,B
JC gotit
MOV R1, A	//only if no carry
JZ cont
gotit : JNC subtract

cont : MOV A, R5
ADD A, R0
MOV R0, A
//now we have a smaller number, do that - 173...

//checking if the number is not smaller than 173 here:
MOV A, R1
JNZ sub2
MOV A, R0
MOV B, 71H
CLR C
SUBB A, B
JC jmpp

sub2 : MOV A, R0
MOV B, 71H
CLR C
SUBB A, B
MOV R0, A
MOV A, R1
MOV B, #0H
SUBB A, B
MOV R1, A
JNZ sub2

jmpp : MOV A, R0
MOV 72H, A

RET


delay_1s:
push 00h
mov r0, #4
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




display : MOV 72H, R4

MOV A, 72H
ANL A, #0F0H
MOV P1, A
LCALL delay_5s

MOV P1, #00H
LCALL delay_1s

MOV A, 72H
ANL A, #0FH
SWAP A
MOV P1, A
LCALL delay_5s

MOV P1, #00H
LCALL delay_1s

END

