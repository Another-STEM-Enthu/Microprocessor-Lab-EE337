// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL QUANT
HERE: SJMP HERE
ORG 130H
// *****************
QUANT:
MOV R4, #08H	//the counter
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
END