using namespace std;

#include <iostream>

int main ()
{
    char one_name[30];

    // Read people's first names (assuming one word per line) from
    // stdin, until end of file, outputting both the original and an
    // uncapitalized version

    while (! cin.eof ())
    {
	one_name[0] = '\0';
	cin >> one_name;
	if (strlen (one_name) > 0)
	{
	    cout << one_name << '\n';
	    one_name[0] = tolower (one_name[0]);
	    cout << one_name << '\n';
	}
    }
}
