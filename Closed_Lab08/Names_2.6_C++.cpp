// WHAT THE MAINTAINER IS THINKING: OK, now I've got it!  Let's go
// back to char* ...

using namespace std;

#include <iostream>

#include "Stack.h"

class Stack_Of_Names :
    public Stack <char*>
{};

int main ()
{
    Stack_Of_Names all_names;

    // Read people's first names (assuming one word per line) from
    // stdin, until end of file, outputting both the original and an
    // uncapitalized version and putting them in a stack to be
    // reversed

    while (! cin.eof ())
    {
	char* one_name = new char[30];
	one_name[0] = '\0';
	cin >> one_name;
	if (strlen (one_name) > 0)
	{
	    char* one_name_lower = new char[30];
	    cout << one_name << '\n';
	    all_names.Push (one_name);
	    strcpy (one_name_lower, one_name);
	    one_name_lower[0] = tolower (one_name_lower[0]);
	    cout << one_name_lower << '\n';
	    all_names.Push (one_name_lower);
	}
    }

    // Output all the names again, from the stack, in reverse order

    cout << "Names in reverse order:\n";
    while (all_names.Length () > 0)
    {
	char* one_name;
	all_names.Pop (one_name);
	cout << one_name << '\n';
    }
}
