#include "RESOLVE_Foundation.h"

global_function Integer Foo (
    preserves Integer n, alters Character_OStream output
    );

function_body Integer Foo (
    preserves Integer n, alters Character_OStream output
    )
{
    if (n <= 1)
    {
	output << "n was <=1\n";
        return 1;
	
    }
    else if (n mod 2 == 0)
    {
	output << "n mod 2 == 0\n";
        return Foo (n/2) + 1;
    }
    else
    {
	output << "(3*n+1) +1\n";
        return Foo (3*n+1) + 1;
    }
}

program_body main ()
{
    object Character_OStream output;
    object Character_IStream input;
    object Integer max, i = 2;
    input.Open_External ("");
    output.Open_External ("");

    Foo (3, output);
    /*output << "Please enter the maximum number to check for Foo: ";
    input >> max;
    
    for (i=0; i<max; i++)
    {
	Foo(i);

	}*/
       output << "LOOK! The program has finished. I is " << i << ". I can has extra credit plz?";
       
       input.Close_External ();
       output.Close_External ();
}
