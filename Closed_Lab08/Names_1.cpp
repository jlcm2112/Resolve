#include "RESOLVE_Foundation.h"

program_body main ()
{
    object Character_IStream input;
    object Character_OStream output;

    input.Open_External ("");
    output.Open_External ("");

    // Read people's first names (assuming one name per line) from
    // stdin, until end of file, outputting both the original and an
    // uncapitalized version

    while (not input.At_EOS ())
    {
	object Text one_name;

	input >> one_name;
	output << one_name << '\n';
	one_name[0] = To_Lower (one_name[0]);
	output << one_name << '\n';
    }

    input.Close_External ();
    output.Close_External ();
}
