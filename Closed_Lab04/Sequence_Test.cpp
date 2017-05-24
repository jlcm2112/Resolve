//  /*--------------------------------------------------------------------*\
//  |   Main Program: Simple tester for Sequence
//  |*--------------------------------------------------------------------*|
//  |   Date:    12 November 1997     
//  |   Author:  Bruce W. Weide 
//  |   
//  |   Brief User's Manual:
//  |   Allows user to test a Sequence implementation, interactively
//  |   or in batch mode.
//  |   
//  \*--------------------------------------------------------------------*/

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "CT/Sequence/Kernel_3_C.h"
#include "CT/Sequence/Put_To_1.h"
#include "CT/Array/Kernel_1_C.h"

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

// Concrete instances

concrete_instance
class Sequence_Of_Text_Base :
    instantiates Sequence_Kernel_3_C <Text>
{};

//----------------------------------------------------------------------

concrete_instance
class Sequence_Of_Text :
    instantiates Sequence_Put_To_1 <
		Text,
		Sequence_Of_Text_Base
	    >
{};

//----------------------------------------------------------------------

concrete_instance
class Array_Of_Sequence_Of_Text :
    instantiates Array_Kernel_1_C <Sequence_Of_Text>
{};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Program control objects

object Boolean interactive;
object Text command_line;
object Character command_code;
object Character_IStream input;
object Character_OStream output;

// Test objects

object Array_Of_Sequence_Of_Text s;

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

//------------------------------------------------------------------------

global_procedure_body Get_Command ()
{
    if (interactive)
    {
	// Show menu of commands:
	// Concept-specific operations
	
	output << "\n\nCommand: s [Swap]\n"
	       << "         c [Clear]\n"
	       << "         p [Put_To]\n"
	       << "         a [Add]\n"
	       << "         r [Remove]\n"
	       << "         [ [Swap Using Accessor]\n"
	       << "         l [Length]\n"
	    
	// Tester control operations
	
	       << "         q [Quit]: ";
    }

    // Get next command line and code
	     
    input >> command_line;
    command_code = command_line[0];
}

//------------------------------------------------------------------------

global_procedure_body Do_Swap ()
{
    object Integer id1, id2;
    object Sequence_Of_Text temp;  // to avoid repeated argument

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

//------------------------------------------------------------------------

global_procedure_body Do_Clear ()
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

//------------------------------------------------------------------------

global_procedure_body Do_Put_To ()
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

global_procedure_body Do_Add ()
{
    object Integer id, pos;
    object Text x;

    if (interactive)
    {
	output << "Add to which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... pos value? ";
    }
    input >> pos;
    if (interactive)
    {
	output << "  ... x value? ";
    }
    input >> x;
    output << "\n--------------------------------------------"
	   << "\n                    |  pos = " << pos
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Add (pos, x);    |";
    s[id].Add (pos, x);
    output << "\n--------------------------------------------"
	   << "\n                    |  pos = " << pos
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

global_procedure_body Do_Remove ()
{
    object Integer id, pos;
    object Text x;

    if (interactive)
    {
	output << "Remove from which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... pos value? ";
    }
    input >> pos;
    if (interactive)
    {
	output << "  ... x value? ";
    }
    input >> x;
    output << "\n--------------------------------------------"
	   << "\n                    |  pos = " << pos
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------"
	   << "\ns" << id << ".Remove (pos, x); |";
    s[id].Remove (pos, x);
    output << "\n--------------------------------------------"
	   << "\n                    |  pos = " << pos
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

global_procedure_body Do_Swap_Using_Accessor ()
{
    object Integer id, pos;
    object Text x;

    if (interactive)
    {
	output << "Swap using accessor in which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... pos value? ";
    }
    input >> pos;
    if (interactive)
    {
	output << "  ... x value to swap with? ";
    }
    input >> x;
    output << "\n--------------------------------------------"
	   << "\n                    |  pos = " << pos
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------"
	   << "\nx &= s" << id << "[pos];       |";
    x &= s[id][pos];
    output << "\n--------------------------------------------"
	   << "\n                    |  pos = " << pos
	   << "\n                    |  x = " << x;
    output << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

global_procedure_body Do_Length ()
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

//------------------------------------------------------------------------
//------------------------------------------------------------------------

program_body main ()
{
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
		Do_Swap ();
		break;
	    case 'c':
		Do_Clear ();
		break;
	    case 'p':
		Do_Put_To ();
		break;
	    case 'a':
		Do_Add ();
		break;
	    case 'r':
		Do_Remove ();
		break;
	    case '[':
		Do_Swap_Using_Accessor ();
		break;
	    case 'l':
		Do_Length ();
		break;

	    // Tester control operations
		
	    case 'q':
		finished = true;
		break;

	    default:
		output << "\n" << command_line;
		break;
        }
    }

    // Close input and output streams
    
    input.Close_External ();
    output.Close_External ();
}
