//	errs.p8		1997 may 26	last modified 1998 may 21
//
//	Example "p8" program with errors detected by scanner.
//	Notice that the parser and code generator are not called.
//

{
	float cat,dog,house;
	int i,dog,horse;

	input i,cat,camel;
	while [ cat < house ] {
		i = i+1.0;
		house = 3.14.15.93*house;
		dog = 1.23x567/cat;
		cat = 1.23e06e04;
		if ( dog > cat )
			goto label;
		outputs i,house$
	}
	label: return( 0 );
}
