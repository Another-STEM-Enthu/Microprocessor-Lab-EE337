ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL play_notes


HERE: SJMP HERE
ORG 130H

delay_Ma:
push 00h
mov r0, #192
h6: acall delay_8us
djnz r0, h5
pop 00h
ret

delay_Ga:
push 00h
mov r0, #204
h5: acall delay_8us
djnz r0, h5
pop 00h
ret

delay_Re:
push 00h
mov r0, #228
h4: acall delay_8us
djnz r0, h4
pop 00h
ret

delay_Sa:
push 00h
push 04h
mov r0, #255
mov r4, #25
addmoreSa : djnz r4, addmoreSa
h3: acall delay_8us
djnz r0, h3
pop 04h
pop 00h
ret


//24 + x*12 + 24 + 24 + 24 = 96 + x*12
delay_8us:
push 00h
mov r0, #2
h1: djnz r0, h1
pop 00h
ret


play_notes : CLR C
loop : 

MOV A, P1
MOV B, A
ANL A, #0FH
CLR C
SUBB A, #00001111B
JNZ notMa
CPL P0.7
CALL delay_Ma
SJMP loop

notMa : MOV A,B
ANL A, #0FH
CLR C
SUBB A, #00000111B
JNZ notGa
CPL P0.7
CALL delay_Ga
SJMP loop

notGa : MOV A,B
ANL A, #0FH
CLR C
SUBB A, #00000011B
JNZ notRe
CPL P0.7
CALL delay_Re
SJMP loop

notRe : MOV A,B
ANL A, #0FH
CLR C
SUBB A, #00000001B
JNZ notRe
CPL P0.7
CALL delay_Sa
SJMP loop



END