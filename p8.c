/*  Authors:    Nicholas Rebhun
 *              Chris Arnoult
 *
 *  Course:     CS-4110 (Compiler Design)
 *  Project:    p1
 *
 *  Start Date: 19 May 2015
 *  Last Edit:  26 May 2015
 * ======================================================
 * Project Description:
 * ------------------------------------------------------
 ********************************************************/

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
    
    y = (long double) 0;
    n = p = s = 0;
    
    while (*a == ' ' || *a == '\t') {
        a++;
    }
    if (*a == '-') {
        a++;
        s++;
    }
    
    while (isdigit( *a )) {
        y = (long double) 10 * y + (long double)((*a++) - '0');
    }
    
    if (*a == '.') {
        a++;
        while (isdigit( *a )) {
            p++;
            y = (long double) 10 * y + (long double)((*a++) - '0');
        }
    }
    
    if ((*a == 'e') || (*a == 'E')) {
        n = atoi( ++a );
    }
    y = y * tento( n - p );
    
    return (s ? -y : y);
}

void baddigitstr( char *t ) {
    fprintf(fpe, e2, line, t);
    nerr++;
    lsymb = symbol[nsymb++] = 0;
}

void closeout( void ) {
	void makename( char *,char *,char * );

	int i;
	char fasm[13];
    
    fputs( "\tret\n_main\tendp\ntext\tends\n_data\tsegment\tword public 'data'\n", fpc );
    
    for (i = 0; i < nrlit; i++) {
        fprintf( fpc, "c%.2d\treal10\t%21.14e\n", i, (double)rlit[i] );
    }
    
    for (i = 0; i < nilit; i++) {
        fprintf( fpc, "c%.2d\tdd\t%ld\n", 50+i, ilit[i] );
    }
    
    for (i = 0; i < nrvar; i++) {
        fprintf( fpc, "v%.2d\treal10\t0.0\t;%-s\n", i, var[i] );
    }
    
    for (i = 0; i < nivar; i++) {
        fprintf( fpc, "v%.2d\tdd\t0\t;%-s\n", 50+i, var[50+i] );
    }
    
    fputs( "_data\tends\nstack\tsegment\tstack\n\tdw\t100h dup(?)\nstack\tends\n", fpc );
    
    if (inf) {
        fputs("\textern\t_inf:near\n", fpc);
    }
    
    if (ini) {
        fputs("\textern\t_ini:near\n", fpc);
    }
    
    if (ouf) {
        fputs("\textern\t_ouf:near\n", fpc);
    }
    
    if (oui) {
        fputs("\textern\t_oui:near\n", fpc);
    }
    
    fputs( "\tend\n", fpc );
    
    if (fclose( fpc )) {
        printf("** can't close %s **\n", fcode);
        exit(1);
    }
    
    makename( fname, "asm", fasm);

    if (fopen( fasm, "rt" ) != (FILE *)NULL) {
        unlink(fasm);
    }
    
    rename(fcode, fasm);
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
    if (n < 100) {
        fprintf( fpc, "%s", reg[n] );
    } else {
        if (n < 200) {
            fprintf( fpc, "v%.2d", n-100 );
        } else {
            fprintf( fpc, "c%.2d", n-200 );
        }
    }
}

void emit1( int i ) {
    fprintf( fpc, "\t%s\n", inst[i] );
}

void emit2( int i, int j ) {
	void emit0( int );
    fprintf( fpc, "\t%s\t", inst[i] );
    emit0(j);
    fputs( "\n", fpc );
}

void emit3( int i, int j, int k ) {
	void emit0( int );
    fprintf( fpc, "\t%s\t", inst[i] );
    emit0(j);
    fputs( ",", fpc );
    emit0(k);
    fputs( "\n", fpc );
}

void extradot( int d,char *t ) {
    printf(fpe, e0, line, d, t );
    nerr++;
    lsymb= symbol[nsymb++] = 0;
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
    
    for (p = s, q = 0; *p; q = q+(int)*p, p++);
    
    h = (q % HSIZE) - 1;
    
    for (q = 0; ;) {
        
        if (HSIZE <= ++h) {
            h = 0;
        }
        
        if (hashp[h].ptss == (char *)NULL) {
            return ( -(h+1));
        }
        
        if (strcmp( s, hashp[p].ptss) == 0) {
            return h;
        }
        
        if (HSIZE <= ++q) {
            puts("** hash table overflow **");
            exit(1);
        }
    }
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
    
    ch = NEWL;
    line = nerr = nilit = nilit = nivar = nrlit = nrvar = nsymb = 0;
    hashp = (HASHREC *)malloc( HSIZE * sizeof(HASHREC));
    
    if (hashp == (HASHREC*)NULL) {
        puts("** can't allocate hash table **");
        exit( 1 );
    }
    
    ssp = (char *)malloc( SSIZE );
    
    if (ssp == (char *)NULL) {
        puts("** can't allocate string space **");
        exit( 1 );
    }
    
    ssp1 = ssp + SSIZE;
    
    for (i = 0; i < HSIZE; i++) {
        hashp[i].ptss = (char *)NULL;
    }
    
    for (i = 0; i < sizeof(trw) / sizeof( char *); i++) {
        h = -hash(trw[i] + 1);
        hashp[h].ptss = trw[i];
        hashp[h].icod = 300 + i;
    }
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
    lsymb = symbol[nsymb++] = 249 + nilit;
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
    
    for (; *p && *p++;) {
        *r++ = *p++;
    }
    
    *r++ = '.';
    
    for (; *q;) {
        *r++ = *q++;
    }
    
    *r = EOS;    
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
int nexts( char *s,char *t ) {
	int ch2,e,st;
	static char *p;
}

void ouch( int c ) {
	putchar( c );
}

void outscan( void ) {
	void makename( char *,char *,char * ),ouch( int );

	int c,i,j,k;
	char fsym[13];
    
    fclose( fpe );
    free( (void *)hashp);
    
    if ( nerr ) {
        printf("\n\n%d error%sdetected in scan\n\n", nerr, (nerr < 2 ? " " : "s "));
        fpe = fopen("$$err$$", "rt");
        
        while ((c = getc( fpe )) != EOF) {
            ouch( c );
        }
        
        fclose( fpe );
        puts( "\n" );
    }
    
    if ( sopt ) {
        makename( fname, "sym", fsym);
        if (fps = fopen( fsym, "wt")) == (FILE *)NULL) {
            printf( "** can't open %s**", fsym );
            exit( 1 );
        }
        
        fprintf( fps, "\t\t\t\tSymbol tables: %s\n", fname );
        
        if (nrvar) {
            fputs( "\n\nreal variables\n\n", fps );
            
            for (i = 0; i < nrvar; i++) {
                fprintf( fps, "%6d    %s\n", 100+i, var[i] );
            }
        }
        
        if (nivar) {
            fputs( "\n\ninteger variables\n\n", fps );
            for (i = 0; i < nivar; i++) {
                fprintf( fps, "%6d    %s\n", 150+i, var[50+i] );
            }
        }
        
        if (nrlit) {
            fputs( "\n\nreal literals\n\n", fps );
            for (i = 0; i < nrlit; i++) {
                fprintf( fps, "%6d    %s\n", 200+i, (double)rlit[i] );
            }
        }
        
        if (nilit) {
            fputs( "\n\ninteger literals\n\n", fps );
            for (i = 0; i < nilit; i++) {
                fprintf( fps, "%6d%15ld\n", 250+i, ilit[i] );
            }
        }
        
        if (nerr) {
            fprintf( fps, "\n\n%d error%sdetected in scan\n\n", nerr, (nerr < 2 ? " " : "s ") );
            while (c = getc( fpe )) != EOF ) {
                fputc( c, fps );
            }
            fclose( fpe );
            fputs( "\n", fps);
        }
        
        fprintf( fps, "\t\tinternal form: %d symbols\n\n", nsymb );
        
        for (i = 0; i < nsymb; i++) {
            k = symbol[i];
            if (400 < k) {
                fprintf( fps, "\n%6d", k )
                j = 0;
            } else {
                if (SYMLIN < ++j) {
                    fprintf( fps, "\n    " );
                    j = 1;
                }
                fprintf( fps, "%5d", k );
            }
        }
        
        fputc( (int) NEWL, fps );
        fclose( fps );
    }
    
    if( unlink( "$$err$$" ) != 0 ) {
        puts( "** cannot delete \"$$err$$\" **" );
    }
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
    
    if (n < 0) {
        return (long double) 1 / tento(-n);
    } else {
        z = (long double)10;
        y = (n & 1 ? z : (long double)1);
        
        for (; a >>= 1;) {
            z = z*z;
            if (n & 1) {
                y = y * z;
            }
        }
        
        return y;
    }
}
