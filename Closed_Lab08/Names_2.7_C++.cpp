// WHAT THE MAINTAINER IS THINKING: Hey, Names_2.6_C++.cpp actually
// works!  I can't believe I'm finished.  Oh, shoot, the boss told me
// to make sure I follow all company guidelines, and this program is
// now too long to be in a single operation.  I'll just split it into
// two: one that does the original work, and also puts the names into
// the stack; and the other that does the new work.  [Try it!  If
// you're lucky it will crash; if not, it will appear to "work" just
// like Names_2.6_C++.cpp appeared to "work"!  Do you know why?  You
// might want to use checked pointers in the Stack component to get
// more information.  And this is just the tip of the iceberg...]

using namespace std;

#include <iostream>

#include "Stack.h"

class Stack_Of_Names :
    public Stack <char*>
{};

void Do_Original_Stuff (Stack_Of_Names& all_names)
{
    // Read people's first names (assuming one word per line) from
    // stdin, until end of file, outputting both the original and an
    // uncapitalized version and putting them in a stack

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
}

void Do_New_Stuff (Stack_Of_Names all_names)
{
    // Output all the names again, from the stack, in reverse order

    cout << "Names in reverse order:\n";
    while (all_names.Length () > 0)
    {
	char* one_name;
	all_names.Pop (one_name);
	cout << one_name << '\n';
    }
}

int main ()
{
    Stack_Of_Names s;
    Do_Original_Stuff (s);
    Do_New_Stuff (s);
}
