// WHAT THE MAINTAINER IS THINKING: That wasn't it, but at least we
// got something printed out that time.  Now this is REALLY becoming a
// pain in the ...  [Can you fix it, starting with the copy of
// Names_2.3_C++.cpp repeated below?  Feel free to consult a C++
// textbook or a C++ guru if you wish.]

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
