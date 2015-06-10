//	p8.h		1996 sep 12	last modified 2000 may 17
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EOS '\0'			// end of string marker
#define HSIZE 211			// hash table size
#define MAXL 240			// max input line length
#define NEWL '\n'			// new line
#define OP0 aux[top]		// operand in code generator
#define OP1 aux[top+1]		// operand in code generator
#define OP2 aux[top+2]		// operand in code generator
#define OP3 aux[top+3]		// operand in code generator
#define SSIZE 1024			// stringspace size
#define SYMLIN 10			// max number of symbols per line

	typedef struct {
		char *ptss;
		int icod;
	} HASHREC;

	FILE *fpc,*fpe,*fps;
	HASHREC *hashp;
	long double rlit[50];
	long ilit[50];
	int alpha,aux[128],ibrk[16],*bstop,bug,c1i,c1j,
		c2[86]={424,354,100,  0,424,363,421,  0,404,403,
			  0,424,303,  0,420,  0,305,  0,304,  0,
			308,409,  0,405,  0,413,  0,414,  0,415,
			  0,363,404,  0,363,420,  0,302,  0,424,
			423,424,352,  0,424,352,309,  0,352,306,
			  0,424,352,  0,355,424,  0,356,424,  0,
			356,  0,357,425,  0,358,425,  0,405,401,
			350,  0,405,350,  0,401,  0,307,  0,306,
			  0,363,421,  0,303,0},
		eline,eos,err,isymb,label,line,lrw,lsymb,maxtop,modes,nerr,
		nilit,nivar,nrlit,nrvar,nsymb,row,
		same[38]={364,364,364,364,364,364,364,406,406,406,
			  406,406,406,100,100,100,100,100,353,353,
			  353,353,425,425,425,425,426,426,426,351,
			  351,402,402,422,422,424,424,  0},
		sd,sigma,sopt=0,symb,symbol[1024],top;
	char *bugm[6]={"mixed modes",
			"illegal syntax",
			"program, apart from comments, must start with '{'",
			"expression is too complicated - not enough registers",
			"expression in repeat clause must be type integer",
			"must be in \"while\" to \"break\""},
















        // c1 table is located on page 116
		c1[54][27]={			// 0:shift; 1:reduce; 1<:bug
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,1,1,1,1,1,1,1,1,1,1},    // <variable>
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,1,1,1,1,1,1,1,1},    // <constant>
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // float
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // int
		{0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // input
		{0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2},    // output
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},    // return
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},    // break
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2},    // while
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2},    // if               [09]
		{0,2,2,2,0,0,0,0,0,0,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // else
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2},    // repeat
		{0,2,0,0,0,0,0,0,0,0,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // {
		{1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // }
		{0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,0,2,2,2,2,2,2,2,2},    // (
		{1,2,2,2,1,1,1,1,1,1,2,1,1,2,2,1,2,1,1,1,1,1,1,1,1,1,1},    // )
		{0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2},    // =
		{0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2},    // +
		{0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2},    // -
		{0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2},    // *                [19]
		{0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2},    // /
		{1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,2},    // <
		{1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,2},    // <=
		{1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,2},    // ==
		{1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,2},    // !=
		{0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2},    // ,
		{1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // ;
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},    // <program>
		{0,2,0,0,0,0,0,2,0,0,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <dec. list>
		{1,2,1,1,1,1,1,2,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <declaration>    [29]
        {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <type>
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0},    // <variable list>
		{0,2,2,2,0,0,0,0,0,0,2,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <state. list>
		{1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <statement>
		{1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <comp. state.>
		{1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <cond. state.>
		{1,2,2,2,1,1,1,1,1,1,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <if statement>
		{1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <if/else state.>
		{1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <while state.>
		{1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <repeat state.>  [39]
		{0,2,2,2,0,0,0,0,0,0,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <if clause>
		{0,2,2,2,0,0,0,0,0,0,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <while clause>
		{0,2,2,2,0,0,0,0,0,0,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <repeat clause>
		{1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <assign state.>
		{1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <i/o state.>
		{1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <break state.>
		{1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <return state.>
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0},    // <get>
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2},    // <put>
		{1,2,2,2,1,1,1,1,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2},    // <condition>      [49]
		{0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2},    // <boolean rel.>
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,0,0,2,2,0,0,0,0,1,0},    // <expression>
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,0,0,1,1,1,1,1,1},    // <term>
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,1,1,1,1,1,1,1,1}},   // <primary>











		c2ptr[37]={ 0, 4, 8,11,14,16,18,20,23,25,
			   27,29, 3,31,34,37, 3, 3,39,44,
			   48,51,54,57,60, 3,62,65, 3,68,
			   72,75, 3,77,79,81,84},
		ch,
		code[54]={1,1,0,1,0,1,1,1,0,1, 1,1,0,0,1,1,0,0,1,1,
			  1,0,1,1,1,0,1,1,0,0, 0,0,0,1,1,1,1,0,0,0,
			  0,1,0,0,0,0,0,0,0,1, 1,1,1,0},
		comf[4]={ 7, 8, 9,13},
		comi[4]={10,11, 9,13},

		delim[131]={
                0,0,0,0,0,0,0,0,0,0,0, 0, 0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0, 0, 0,0,0,0,
			    0,0,0,0,0,0,0,0,2,3,7, 5,13,6,0,8,
			    0,0,0,0,0,0,0,0,0,0,0,14, 9,4,0,0,
			    0,0,0,0,0,0,0,0,0,0,0, 0, 0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0, 0, 0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0, 0, 0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0, 0, 0,1,0,0,10,11,12},

		*e0="line%5d - %d decimal points in numeric string [%s]\n",
		*e1="line%5d - illegal character [%c]\n",
		*e2="line%5d - illegal numeric string [%s]\n",
		*e3="line%5d - variable is doubly defined [%s]\n",
		*e4="line%5d - unrecognized id [%s]\n",
		first[54]={13,53,37,38, 0, 0, 0, 0, 0, 0,
			    0, 0, 0,29, 0,18, 0, 0, 0, 0,
			    0,49,50,51,52, 0, 0, 0, 0,31,
			    0, 0, 0, 7,39,40,47,48,41,42,
			    0, 0, 0,43,44,45,46, 0, 0,33,
			    0,35,22,26},
		*fcode="$$p8$$.asm",
		*fname,inf,ini,
		*inst[41]={"add" ,"call","cdq" ,"cmp" ,"cwd" ,"idiv",
			   "imul","ja"  ,"jae" ,"je"  ,"jl"  ,"jle" ,
			   "jmp" ,"jne" ,"mov" ,"neg" ,"pop" ,"push",
			   "sahf","sub" ,"xchg",
			   "fadd"  ,"faddp","fchs" ,"fcom"  ,"fcomp"    ,
			   "fcompp","fdiv" ,"fdivp","fdivr" ,"fdivrp"   ,
			   "fld"   ,"fmul" ,"fmulp","fstp"  ,"fstsw\tax",
			   "fsub"  ,"fsubp","fsubr","fsubrp","fxch"},

        // kind[] maps ASCII characters. Used only in 'nexts()' Note: Extended ASCII not supported in p8. kind[128 - 130] are for boolean comparitors
		kind[132]={
                0,5,5,5,5,5,5,5,5,4,0,5,5,5,5,5,        // 0 - 15
                5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,        // 16 - 31
                4,5,5,5,5,5,5,5,3,3,3,3,3,3,3,3,        // 32 - 47
                2,2,2,2,2,2,2,2,2,2,5,3,3,3,5,5,        // 48 - 63
                5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,        // 64 - 79
                1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,        // 80 - 95
                5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,        // 96 - 111
                1,1,1,1,1,1,1,1,1,1,1,3,5,3,5,5,3,3,3, 3}, // 112 - 130
		mode[128],
		newsigma[54]={16,17, 2,17,17,18,19,10, 5, 9,
			      11,12, 5, 4,20,20, 4,26,22,15,
			      14,26,24,24,24,24,25,25,25, 0,
			       7, 1, 1,13,14,21,21, 3, 3, 6,
			       6, 6, 6, 6, 6, 6, 6, 8, 8,23,
			      23,23,23,26},
		ouf,oui,rbu[6],
		*reg[6]={"eax","ebx","ecx","edx","esi","edi"},
		*ssp,*ssp1,
		subtop[37]={3,3,2,2,1,1,1,2,1,1,
			    1,1,0,2,2,1,0,0,4,3,
			    2,2,2,2,1,0,2,2,0,3,
			    2,1,0,1,1,2,1},
		*trw[10]={"float", "int", "input", "output", "return",
			  "break", "while", "if", "else", "repeat"},
		*var[100];
