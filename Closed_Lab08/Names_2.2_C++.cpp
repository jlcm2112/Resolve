// WHAT THE MAINTAINER IS THINKING: Names_2.1_C++.cpp didn't even
// compile.  Well, come to think of it, it probably wouldn't have
// worked anyway, because a C++ char[] [an array of characters, used
// in most code of this kind in a typical C++ textbook] is allocated
// on the run-time stack.  This would mean that Stack_Of_Names
// all_names would end up holding pointers to the run-time stack,
// which is a definite no-no!  Let's see what happens if we
// dynamically allocate one_name from the heap; this should fix both
// problems.  [Try it!]

using namespace std;

#include <iostream>

#include "Stack.h"

class Stack_Of_Names :
    public Stack <char*>
{};

int main ()
{
    char* one_name = new char[30];
    Stack_Of_Names all_names;

    // Read people's first names (assuming one word per line)
    // from stdin, until end of file, outputting both the original and
    // an uncapitalized version and putting them in a stack to be
    // reversed

    while (! cin.eof ())
    {
	one_name[0] = '\0';
	cin >> one_name;
	if (strlen (one_name) > 0)
	{
	    cout << one_name << '\n';
	    all_names.Push (one_name);
	    one_name[0] = tolower (one_name[0]);
	    cout << one_name << '\n';
	    all_names.Push (one_name);
	}
    }

    // Output all the names again, from the stack, in reverse order

    cout << "Names in reverse order:\n";
    while (all_names.Length () > 0)
    {
	all_names.Pop (one_name);
	cout << one_name << '\n';
    }
}
