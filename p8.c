//	p8.org		1996 apr 21	last modified 1998 jun 01
//
//	Shows organization of dan's p8.c.
//

#include "p8.h"

int main( int argc,char **argv ) {
	void parse( void ),scan( void );

	if ( (argc < 2) || (3 < argc) ) {
		puts( "** use is >p8 [-y] sourcefilename **" );
		exit( 1 );
	}
	if ( argc == 3 ) {
		if ( strcmp( *++argv,"-y" ) == 0 ) {
			sopt = 1;
		} else {
			printf( "** illegal option: [%s] **\n",*argv );
			exit( 1 );
		}
	}
	if ( (fps = fopen( fname = *++argv,"rt" )) == (FILE *)NULL ) {
		printf( "** can't open %s **\n",fname );
		exit( 1 );
	}
	if ( (fpe = fopen( "$$err$$","wt" )) == (FILE *)NULL ) {
		puts( "** can't open \"$$err$$\" for writing errors **" );
		exit( 1 );
	}
	scan();
	if ( nerr == 0 ) {
		parse();
	}
	return( 0 );
}

long double atold( char *a ) {
	long double tento( int );

	long double y;
	int n,p,s;
}

void baddigitstr( char *t ) {
}

void closeout( void ) {
	void makename( char *,char *,char * );

	int i;
	char fasm[13];
}

int comp( int s,int *p ) {
}

//Completed by Chris Arnoult
void delimiter( void ) {
    lsymb = symbol[nsymb++] = 350+(int)delim[(int)ch & 0x00ff];
    if (ch == ';') {
        lrw = 0;
    }
}

void emit0( int n ) {
}

void emit1( int i ) {
}

void emit2( int i,int j ) {
	void emit0( int );
}

void emit3( int i,int j,int k ) {
	void emit0( int );
}

void extradot( int d,char *t ) {
}

//Completed by Chris Arnoult
void floatstr( char *t ) {
	long double atold( char * );
	double x;
	int i;
    
    if (!isdigit(*(t+strlen(t)-1))) {
        fprintf(fpe,e2,line,t);
        nerr++;
        lsymb = symbol[nsymb++] = 0;
        return;
    }
    x = atold(t);
    for (i = 0; i < nrlit; i++) {
        if (x == rlit[i]) {
            lsymb = symbol[nsymb++] = 200+i;
            return;
        }
    }
    if (50 <= nrlit) {
        puts("** too many real literals **");
        exit(1);
    }
    rlit[nrlit++] = x;
    lsymb = symbol[nsymb++] = 199+nrlit;
}

void gencode( void ) {
	int nextr( void );
	void emit1( int ),emit2( int,int ),emit3( int,int,int );

	int l,r;
}

void getsymbol( void ) {
}
//
//	If string s is new, return -(hash+1)
//	else if found, return hash.
//	Thus (in calling function):
//		if return value y < 0, then hash = -(y+1)
//				       else hash = y.
//
int hash( char *s ) {
	int h,q;
	char *p;
}

//Completed by Chris Arnoult
void illegalch( void ) {
    fprintf(fpe,e1,line,ch);
    nerr++;
    lsymb = symbol[nsymb++] = 0;
}

void initparse( void ) {
	int r;
}

void initscan( void ) {
	int hash( char * );

	int h,i;
}

//Completed by Chris Arnoult
void intstr( char *t ) {
	long atol( char * );
	long x;
	int i;
    
    x = atol(t);
    for (i = 0; i < nilit; i++) {
        if (x == ilit[i]) {
            lsymb = symbol[nsymb++] = 250+i;
            return;
        }
    }
    if (50 <= nilit) {
        puts("** too mamny int literals **");
        exit(1);
    }
    ilit[nilit++] = x;
    lsymb = symbol[nsymb++] = 249+nilit;
}

//Completed by Chris Arnoult
void letterstr( char *t ) {
	int hash( char * );
	int h,i;
	char *p;
    
    h = hash(t);
    
    //old string
    if (0 <= h) {
        i = hashp[h].icod;
        if (i == 0) {
            fprintf(fpe, e4, line, t);
            nerr++;
        }
        if ((i < 200) && ((lrw == 300) || (lrw == 301))) {
            fprintf(fpe, e4, line, t);
            nerr++;
        }
        if (300 <= i) {
            lrw = i;
        }
        lsymb = symbol[nsymb++] = i;
    }
    
    //new string
    if (ssp1 <= ssp+strlen(t)) {
        puts("** out of string space **");
        unlink("$$err$$");
        fclose(fps);
        exit(1);
    }
    
    h = -(h+1);
    hashp[h].ptss = ssp;
    p = t;
    
    //copy to sspace
    while ((*ssp++ = *p++) != EOS) {}
    if (lrw == 300) {
        var[nrvar] = hashp[h].ptss;
        lsymb = symbol[nsymb++] = hashp[h].icod = 100+(nrvar++);
        return;
    }
    if (lrw == 301) {
        var[50+nivar] = hashp[h].ptss;
        lsymb = symbol[nsymb++] = hashp[h].icod = 150+(nivar++);
        return;
    }
    fprintf(fpe, e4, line, t);
    nerr++;
    lsymb = symbol[nsymb++] = hashp[h].icod = 0;
}

void makename( char *p,char *q,char *r ) {
}

void match( void ) {
	void gencode( void );
}

int nextr( void ) {
	int r;
}
//
//	st is as follows:
//	      -st : last symbol in string (here 0 < st)
//		0 : empty string (last, following a terminal delimiter)
//		1 : illegal char
//		2 : delimiter
//		3 : letterstring (possibly containing digits)
//		4 : letter in digitstring
//		5 : integer
//		6 : real
//	  7,8,... : too many dots (st-5 dots)
//

//Completed by Chris Arnoult (This could have errors)
int nexts( char *s,char *t ) {
	int ch2,e,st;
	static char *p;
    e = st = 0;
    
    if (ch == NEWL) {
        p = s;
    }
    //A
    while (1) {
        ch = *p;
        ch2 = (((int)ch)<<8)+((int)*(p+1));
        switch (ch2) {
            case 0x2f2f:
                ch = NEWL;
                break;
            case 0x3c3d:
                ch = (char)128;
                p++;
                break;
            case 0x3d3d:
                ch = (char)129;
                p++;
                break;
            case 0x213d:
                ch = (char)130;
                p++
                break;
            default:
                break;
        }
        switch ((int)kind[(int)ch & 0x00ff]) {
            case 0:
                *t = EOS;
                return(-st);
            case 1:
                if (st == 0) {
                    st = 3;
                }
                if (((ch == 'e') || (ch == "E")) && ((st == 5) || (st == 6)) && (e = 0)) {
                    st = 6;
                    e++;
                }
                if (4 < st) {
                    st = 4;
                }
            case 2:
                if (st == 0) {
                    st = 5;
                }
                p++;
                *t++ = ch;
                break;
            case 3:
                if (st == 0) {
                    *t++ = ch;
                    p++;
                }
                (ch == '.') && isdigit(*p) && ((lsymb = 303) || (lsymb = 352) || )
            
//            default:
//                break;
        }
        continue; //Goes back to A
    }
}

void ouch( int c ) {
	putchar( c );
}

void outscan( void ) {
	void makename( char *,char *,char * ),ouch( int );

	int c,i,j,k;
	char fsym[13];
}

void parse( void ) {
	void closeout( void ),getsymbol( void ),initparse( void ),
		reduce( void ),reportbug( void ),shift( void );
}

void reduce( void ) {
	int comp( int,int * );
	void match( void );
}

void reportbug( void ) {
	void ouch( int );

	int i,j,k;
}

void scan( void ) {
	int nexts( char *,char * );
	void baddigitstr( char * ),delimiter( void ),extradot( int,char * ),
		floatstr( char * ),illegalch( void ),initscan( void ),
		intstr( char * ),letterstr( char * ),outscan( void );

	int st;
	char s[MAXL+1],t[MAXL+1];
}

void shift( void ) {
}

long double tento( int n ) {
	long double y,z;
}
