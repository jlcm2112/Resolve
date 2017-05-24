//  /*--------------------------------------------------------------------*\
//  |   Main Program: Simple tester for List_Retreat
//  |*--------------------------------------------------------------------*|
//  |   Date:    16 November 1999     
//  |   Author:  Bruce W. Weide 
//  |   
//  |   Modified: 2 December 2003
//  |   Modifier: Dan Charnigo
//  |   
//  |   Modification:
//  |   Reveal any storage leaks.  Based on a modification of a
//  |   closed lab Stack_Test.cpp by Wayne D. Heym and a
//  |   modification by Dan Kelly of a previous lab's List_Test.cpp.
//  |   
//  |   Brief User's Manual:
//  |   Allows user to test a List_Retreat implementation,
//  |   interactively or in batch mode.
//  |   
//  \*--------------------------------------------------------------------*/

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "CT/List/Retreat_2a_C.h"
#include "CT/List/Put_To_1.h"
#include "CT/Array/Kernel_1_C.h"

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

// Concrete instances

concrete_instance
class List_Of_Text_Base :
    instantiates List_Retreat_2a_C <Text>
{};

//----------------------------------------------------------------------

concrete_instance
class List_Of_Text :
    instantiates  List_Put_To_1 <
	    Text,
	    List_Of_Text_Base
	>
{};

//----------------------------------------------------------------------

concrete_instance
class Array_Of_List_Of_Text :
    instantiates Array_Kernel_1_C <List_Of_Text>
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

procedure_body Determine_Interactive_Mode ()
{
    output << "Run in interactive mode (y/n)? ";
    input >> command_line;
    command_code = command_line[0];
    interactive = (command_code == 'y');
}

//------------------------------------------------------------------------

procedure_body Get_Command ()
{
    if (interactive)
    {
	// Show menu of commands:
	// Concept-specific operations
	
	output << "\n\nCommand: s [Swap]\n"
	       << "         c [Clear]\n"
	       << "         p [Put_To]\n"
	       << "         < [Move_To_Start]\n"
	       << "         > [Move_To_Finish]\n"
	       << "         n [Advance]\n"
	       << "         b [Retreat]\n"
	       << "         a [Add_Right]\n"
	       << "         r [Remove_Right]\n"
	       << "         [ [Swap Using Accessor]\n"
	       << "         L [Left_Length]\n"
	       << "         R [Right_Length]\n"

	// Tester control operations
	
	       << "         q [Quit]: ";
    }

    // Get next command line and code
	     
    input >> command_line;
    command_code = command_line[0];
}

//------------------------------------------------------------------------

procedure_body Do_Swap (Array_Of_List_Of_Text& s)
{
    object Integer id1, id2;
    object List_Of_Text temp;  // to avoid repeated argument

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
	   << "\n                        |";
    output << "\n--------------------------------------------"
	   << "\ns" << id1 << " &= s" << id2 << ";               |";
    temp &= s[id1];
    temp &= s[id2];
    temp &= s[id1];
    output << "\n--------------------------------------------"
	   << "\n                        |";
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Clear (Array_Of_List_Of_Text& s)
{
    object Integer id;

    if (interactive)
    {
	output << "Clear which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\n                        |";
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Clear ();            |";
    s[id].Clear ();
    output << "\n--------------------------------------------"
	   << "\n                        |";
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Put_To (Array_Of_List_Of_Text& s)
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

//------------------------------------------------------------------------

procedure_body Do_Move_To_Start (Array_Of_List_Of_Text& s)
{
    object Integer id;

    if (interactive)
    {
	output << "Move to start in which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\n                        |";
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Move_To_Start ();    |";
    s[id].Move_To_Start ();
    output << "\n--------------------------------------------"
	   << "\n                        |";
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Move_To_Finish (Array_Of_List_Of_Text& s)
{
    object Integer id;

    if (interactive)
    {
	output << "Move to finish in which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\n                        |";
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Move_To_Finish ();   |";
    s[id].Move_To_Finish ();
    output << "\n--------------------------------------------"
	   << "\n                        |";
    output << "\n--------------------------------------------";
}
//------------------------------------------------------------------------

procedure_body Do_Advance (Array_Of_List_Of_Text& s)
{
    object Integer id;

    if (interactive)
    {
	output << "Advance in which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\n                        |";
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Advance ();          |";
    s[id].Advance ();
    output << "\n--------------------------------------------"
	   << "\n                        |";
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Retreat (Array_Of_List_Of_Text& s)
{
    object Integer id;

    if (interactive)
    {
	output << "Retreat in which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\n                        |";
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Retreat ();          |";
    s[id].Retreat ();
    output << "\n--------------------------------------------"
	   << "\n                        |";
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Add_Right (Array_Of_List_Of_Text& s)
{
    object Integer id;
    object Text x;

    if (interactive)
    {
	output << "Add_Right to which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... x value? ";
    }
    input >> x;
    output << "\n--------------------------------------------"
	   << "\n                        |  x = " << x;
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Add_Right (x);       |";
    s[id].Add_Right (x);
    output << "\n--------------------------------------------"
	   << "\n                        |  x = " << x;
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Remove_Right (Array_Of_List_Of_Text& s)
{
    object Integer id;
    object Text x;

    if (interactive)
    {
	output << "Remove_Right from which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... x value? ";
    }
    input >> x;
    output << "\n--------------------------------------------"
	   << "\n                        |  x = " << x;
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Remove_Right (x);    |";
    s[id].Remove_Right (x);
    output << "\n--------------------------------------------"
	   << "\n                        |  x = " << x;
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Swap_Using_Accessor (Array_Of_List_Of_Text& s)
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
	   << "\n                        |  x = " << x;
    output << "\n--------------------------------------------"
	   << "\nx &= s" << id << "[current];       |";
    x &= s[id][current];
    output << "\n--------------------------------------------"
	   << "\n                        |  x = " << x;
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Left_Length (Array_Of_List_Of_Text& s)
{
    object Integer id;
    object Integer i;

    if (interactive)
    {
	output << "Get left length of which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\n                        |  i = ?";
    output << "\n--------------------------------------------"
	   << "\ni = s" << id << ".Left_Length ();  |";
    i = s[id].Left_Length ();
    output << "\n--------------------------------------------"
	   << "\n                        |  i = " << i;
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Right_Length (Array_Of_List_Of_Text& s)
{
    object Integer id;
    object Integer i;

    if (interactive)
    {
	output << "Get right length of which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\n                        |  i = ?";
    output << "\n--------------------------------------------"
	   << "\ni = s" << id << ".Right_Length (); |";
    i = s[id].Right_Length ();
    output << "\n--------------------------------------------"
	   << "\n                        |  i = " << i;
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

program_body main ()
{
    // Establish an inner scope to contain the array of test objects
    // and the main program that uses it.
    {
	// Test objects
	object Array_Of_List_Of_Text s;

	// Flag object
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
		case '<':
		{
		    Do_Move_To_Start (s);
		}
		break;
		case '>':
		{
		    Do_Move_To_Finish (s);
		}
		break;
		case 'n':
		{
		    Do_Advance (s);
		}
		break;
		case 'b':
		{
		    Do_Retreat (s);
		}
		break;
		case 'a':
		{
		    Do_Add_Right (s);
		}
		break;
		case 'r':
		{
		    Do_Remove_Right (s);
		}
		break;
		case '[':
		{
		    Do_Swap_Using_Accessor (s);
		}
		break;
		case 'L':
		{
		    Do_Left_Length (s);
		}
		break;
		case 'R':
		{
		    Do_Right_Length (s);
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
