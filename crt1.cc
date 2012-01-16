// Filename:  		CRT1.CC
// Author:    		C. DAVYDUKE
// File Created:	03/09/25
// Last Modified:	03/10/21
// Description:  	This file is used to initialize bss, call global constructors, call main, call global desctructors,
//						and then go into an infinite loop upon termination.

extern int main();
extern char bss_beg;
extern char bss_end;

// Define a function pointer, read "pointer to a function, taking void, returning void."
typedef void ( *FPV )( );

extern FPV ctor_beg[ ];
extern FPV ctor_end[ ];

extern FPV dtor_beg[ ];
extern FPV dtor_end[ ];

void crt1( )
{
	char * bss_cp;
//	char * ctor_cp;
//	char * dtor_cp;
	int i;

// Initialize the bss, set all values to 0.  
	for ( bss_cp = &bss_beg; bss_cp < &bss_end; bss_cp++ )
		*bss_cp = 0;

// Call the global constructors.
//  for ( ctor_cp = &ctor_beg; ctor_cp < &ctor_end; ctor_cp++ )
	for ( i = 0; i < ( ctor_end - ctor_beg ); i++ )
	{
		( *ctor_beg[ i ] )( );
//    ctor_beg++;
	}
  
// Enable interrupts globally
	asm( "cli" );

// Call main
	main( );

// Disable interrupts globally
	asm( "sei" );
  
// Call the global destructors.
//  for ( dtor_cp = &dtor_beg; dtor_cp < &dtor_end; dtor_cp++ )
	for ( i = 0; i < ( dtor_end - dtor_beg ); i++ )
	{
		( *dtor_beg[ i ] )( );
//    dtor_beg++;
	}
  
// Sit and spin.
	while ( 1 )
	{
	}
}
