//  /*----------------------------------------------------------------*\
//  |   Main Program: Simple tester for Stack
//  |*----------------------------------------------------------------*|
//  |   Date:     4 March 1998     
//  |   Author:   Bruce W. Weide 
//  |   
//  |   Modified: 2 July 2001     
//  |   Modifier: Wayne D. Heym
//  |   
//  |   Modification:
//  |   Reveal any storage leaks.
//  |   
//  |   Brief User's Manual:
//  |   Allows user to test a Stack implementation, interactively
//  |   or in batch mode.
//  |   
//  \*----------------------------------------------------------------*/

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "CT/Stack/Kernel_1a_C.h"
#include "CT/Stack/Put_To_1.h"
#include "CT/Array/Kernel_1_C.h"

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

// Concrete instances

concrete_instance
class Stack_Of_Text_Base :
    instantiates Stack_Kernel_1a_C <Text>
{};

//----------------------------------------------------------------------

concrete_instance
class Stack_Of_Text :
    instantiates Stack_Put_To_1 <
		Text,
		Stack_Of_Text_Base
	    >
{};

//----------------------------------------------------------------------

concrete_instance
class Array_Of_Stack_Of_Text :
    instantiates Array_Kernel_1_C <Stack_Of_Text>
{};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Program control objects

object Boolean interactive;
object Text command_line;
object Character command_code;
object Character_IStream input;
object Character_OStream output;

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operations (omitted for brevity)

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operation bodies

global_procedure_body Determine_Interactive_Mode ()
{
    output << "Run in interactive mode (y/n)? ";
    input >> command_line;
    command_code = command_line[0];
    interactive = (command_code == 'y');
}

//---------------------------------------------------------------------

global_procedure_body Get_Command ()
{
    if (interactive)
    {
	// Show menu of commands:
	// Concept-specific operations
	
	output << "\n\nCommand: s [Swap]\n"
	       << "         c [Clear]\n"
	       << "         p [Put_To]\n"
	       << "         a [Push]\n"
	       << "         r [Pop]\n"
	       << "         [ [Swap Using Accessor]\n"
	       << "         l [Length]\n"

	// Tester control operations
	
	       << "         q [Quit]: ";
    }

    // Get next command line and code
	     
    input >> command_line;
    command_code = command_line[0];
}

//---------------------------------------------------------------------

global_procedure_body Do_Swap (Array_Of_Stack_Of_Text& s)
{
    object Integer id1, id2;
    object Stack_Of_Text temp;  // to avoid repeated argument

    if (interactive)
    {
	output << "Swap which object? ";
    }
    input >> id1;
    if (interactive)
    {
	output << "  ... with which object? ";
    }
    input >> id2;
    output << "\n--------------------------------------------"
	   << "\n                    |";
    output << "\n--------------------------------------------"
	   << "\ns" << id1 << " &= s" << id2 << ";           |";
    temp &= s[id1];
    temp &= s[id2];
    temp &= s[id1];
    output << "\n--------------------------------------------"
	   << "\n                    |";
    output << "\n--------------------------------------------";
}

//---------------------------------------------------------------------

global_procedure_body Do_Clear (Array_Of_Stack_Of_Text& s)
{
    object Integer id;

    if (interactive)
    {
	output << "Clear which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\n                    |";
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Clear ();        |";
    s[id].Clear ();
    output << "\n--------------------------------------------"
	   << "\n                    |";
    output << "\n--------------------------------------------";
}

//---------------------------------------------------------------------

global_procedure_body Do_Put_To (Array_Of_Stack_Of_Text& s)
{
    object Integer id;

    if (interactive)
    {
	output << "Put which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\ns" << id << " = ";
    output << s[id];
    output << "\n--------------------------------------------";
}

//---------------------------------------------------------------------

global_procedure_body Do_Push (Array_Of_Stack_Of_Text& s)
{
    object Integer id;
    object Text x;

    if (interactive)
    {
	output << "Push onto which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... x value? ";
    }
    input >> x;
    output << "\n--------------------------------------------"
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Push (x);        |";
    s[id].Push (x);
    output << "\n--------------------------------------------"
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------";
}

//---------------------------------------------------------------------

global_procedure_body Do_Pop (Array_Of_Stack_Of_Text& s)
{
    object Integer id;
    object Text x;

    if (interactive)
    {
	output << "Pop from which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... x value? ";
    }
    input >> x;
    output << "\n--------------------------------------------"
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Pop (x);         |";
    s[id].Pop (x);
    output << "\n--------------------------------------------"
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------";
}

//---------------------------------------------------------------------

global_procedure_body Do_Swap_Using_Accessor (Array_Of_Stack_Of_Text& s)
{
    object Integer id;
    object Text x;

    if (interactive)
    {
	output << "Swap using accessor in which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... x value to swap with? ";
    }
    input >> x;
    output << "\n--------------------------------------------"
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------"
	   << "\nx &= s" << id << "[current];   |";
    x &= s[id][current];
    output << "\n--------------------------------------------"
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------";
}

//----------------------------------------------------------------------

global_procedure_body Do_Length (Array_Of_Stack_Of_Text& s)
{
    object Integer id;
    object Integer i;

    if (interactive)
    {
	output << "Get length of which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\n                    |  i = ?";
    output << "\n--------------------------------------------"
	   << "\ni = s" << id << ".Length ();   |";
    i = s[id].Length ();
    output << "\n--------------------------------------------"
	   << "\n                    |  i = " << i;
    output << "\n--------------------------------------------";
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

program_body main ()
{
    // Establish an inner scope to contain the array of test objects
    // and the main program that uses it.
    {
	// Test objects
	
	object Array_Of_Stack_Of_Text s;
	
	object Boolean finished;
	
	// Open input and output streams
	
	input.Open_External ("");
	output.Open_External ("");
	
	// Set number of test objects (= 10)
	
	s.Set_Bounds (0, 9);
	
	// Ask user about interactive mode
	
	Determine_Interactive_Mode ();
	
	// Execute interactive testing loop until finished
	
	while (not finished)
	{
	    // Ask user for next command
	    
	    Get_Command ();
	    
	    // Perform next command
	    
	    case_select (command_code)
		{
		    // Concept-specific operations
		    
		case 's':
		{
		    Do_Swap (s);
		}
		break;
		case 'c':
		{
		    Do_Clear (s);
		}
		break;
		case 'p':
		{
		    Do_Put_To (s);
		}
		break;
		case 'a':
		{
		    Do_Push (s);
		}
		break;
		case 'r':
		{
		    Do_Pop (s);
		}
		break;
		case '[':
		{
		    Do_Swap_Using_Accessor (s);
		}
		break;
		case 'l':
		{
		    Do_Length (s);
		}
		break;
		
		// Tester control operations
		
		case 'q':
		{
		    finished = true;
		}
		break;
		
		default:
		{
		    output << "\n" << command_line;
		}
		break;
		}
	}
	
	// Close input and output streams
	
	input.Close_External ();
	output.Close_External ();
    } // end of scope containing the array of test objects
    
    // test for storage leaks
    Report_Storage_Allocation ();
}
