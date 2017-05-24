// WHAT THE MAINTAINER IS THINKING: The boss wants me to do this
// trivial maintenance activity on Names_1.cpp: Modify the program so
// that it also prints out the names in reverse order.  This should be
// easy.  Let's make life even simpler and use an off-the-shelf Stack
// component.  After outputting each name, let's push it onto a stack.
// Then we can output the values as they are popped from it.  [Try
// it!]

#include "RESOLVE_Foundation.h"

#include "CT/Stack/Kernel_1a_C.h"

concrete_instance
class Stack_Of_Names :
    instantiates Stack_Kernel_1a_C <Text>
{};

program_body main ()
{
    object Character_IStream input;
    object Character_OStream output;
    object Stack_Of_Names all_names;

    input.Open_External ("");
    output.Open_External ("");

    // Read people's first names (assuming one name per line) from
    // stdin, until end of file, outputting both the original and an
    // uncapitalized version and putting them in a stack

    while (not input.At_EOS ())
    {
	object Text one_name, all_lower_name;

	input >> one_name;
	all_lower_name = one_name;
	all_lower_name[0] = To_Lower (one_name[0]);
	output << one_name << '\n';
	all_names.Push (one_name);
	output << all_lower_name << '\n';
	all_names.Push (all_lower_name);
    }

    // Output all the names again, from the stack, in reverse order

    output << "Names in reverse order:\n";
    while (all_names.Length () > 0)
    {
	object Text one_name;

	all_names.Pop (one_name);
	output << one_name << '\n';
    }

    input.Close_External ();
    output.Close_External ();
}
