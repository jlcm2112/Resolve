// WHAT THE MAINTAINER IS THINKING: That wasn't it.  This is becoming
// a pain in the ...  I know!  I remember some old professor saying at
// one point that it's better to declare local objects in the
// innermost scope in which they are used.  Let's move the declaration
// of one_name inside the loop bodies so it gets allocated each time
// through.  Perhaps the Stack component would like this better.
// [Although, how would you know without exploring the code for that
// component?]  Anyway, let's see what happens if we dynamically
// allocate one_name from the heap each time we enter each loop body.
// [Try it!]

using namespace std;

#include <iostream>

#include "Stack.h"

class Stack_Of_Names :
    public Stack <char*>
{};

int main ()
{
    Stack_Of_Names all_names;

    // Read people's first names (assuming one word per line)
    // from stdin, until end of file, outputting both the original and
    // an uncapitalized version and putting them in a stack to be
    // reversed

    while (! cin.eof ())
    {
	char* one_name = new char[30];
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
        char* one_name = new char[30];
	all_names.Pop (one_name);
	cout << one_name << '\n';
    }
}
