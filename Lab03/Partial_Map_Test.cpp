//  /*----------------------------------------------------------------*\
//  |   Main Program: Simple tester for Partial_Map
//  |*----------------------------------------------------------------*|
//  |   Date:    17 November 1997, revised 7 February 2007,
//  |            revised 16 December 2009   
//  |   Author:  Bruce W. Weide 
//  |   
//  |   Brief User's Manual:
//  |   Allows user to test a Partial_Map implementation, interactively
//  |   or in batch mode.
//  |   
//  \*----------------------------------------------------------------*/

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "AT/General/Hash.h"
#include "CI/Natural/Number_1_C.h"
#include "CT/Partial_Map/Kernel_6_C.h"
#include "CT/Partial_Map/Put_To_1.h"
#include "CT/Array/Kernel_1_C.h"

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

// Concrete instances

concrete_instance
utility_class Natural_Hash_1 :
    implements abstract_instance General_Hash <Natural_Number_1_C>
{
public:
    
    /*!
	math definition HASH_FUNCTION (
		x: NATURAL_MODEL
	    ): integer is
	    x mod 1999
    !*/

    utility_function_body Integer Hash (
	    preserves Natural_Number_1_C& x
	)
    {
	object Natural_Number_1_C x_copy, divisor, remainder;
	object Integer hash_value;

	x.Copy_To (x_copy);
	divisor.Convert_From_Integer (1999);
	x_copy.Divide (divisor, remainder);
	while (remainder.Discrete_Log () > 0)
	{
	    object Integer digit;

	    remainder.Divide_By_Radix (digit);
	    hash_value = hash_value * remainder.Radix () + digit;
	}
	return hash_value; 
    }
};

//----------------------------------------------------------------------

concrete_instance
class Partial_Map_Of_Natural_To_Text_Base :
    instantiates Partial_Map_Kernel_6_C <
	    Natural_Number_1_C,
	    Text,
	    Natural_Hash_1,
	    10
	>
{};

//----------------------------------------------------------------------

concrete_instance
class Partial_Map_Of_Natural_To_Text :
    instantiates Partial_Map_Put_To_1 <
	    Natural_Number_1_C,
	    Text,
	    Partial_Map_Of_Natural_To_Text_Base
	>
{};

//----------------------------------------------------------------------

concrete_instance
class Array_Of_Partial_Map_Of_Natural_To_Text :
    instantiates Array_Kernel_1_C <Partial_Map_Of_Natural_To_Text>
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

object Array_Of_Partial_Map_Of_Natural_To_Text m;

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

//----------------------------------------------------------------------

global_procedure_body Get_Command ()
{
    if (interactive)
    {
	// Show menu of commands:
	// Concept-specific operations
	
	output << "\n\nCommand: s [Swap]\n"
	       << "         c [Clear]\n"
	       << "         p [Put_To]\n"
	       << "         d [Define]\n"
	       << "         u [Undefine]\n"
	       << "         a [Undefine_Any]\n"
	       << "         i [Is_Defined]\n"
	       << "         [ [Swap Using Accessor]\n"
	       << "         z [Size]\n"

	// Tester control operations
	
	       << "         q [Quit]: ";
    }

    // Get next command line and code
	     
    input >> command_line;
    command_code = command_line[0];
}

//----------------------------------------------------------------------

global_procedure_body Do_Swap ()
{
    object Integer id1, id2;
    object Partial_Map_Of_Natural_To_Text temp;  // to avoid repeated arg

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
	   << "\n                   |";
    output << "\n--------------------------------------------"
	   << "\nm" << id1 << " &= m" << id2 << ";          |";
    temp &= m[id1];
    temp &= m[id2];
    temp &= m[id1];
    output << "\n--------------------------------------------"
	   << "\n                   |";
    output << "\n--------------------------------------------";
}

//----------------------------------------------------------------------

global_procedure_body Do_Clear ()
{
    object Integer id;

    if (interactive)
    {
	output << "Clear which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\n                   |";
    output << "\n--------------------------------------------"
	   << "\nm" << id << ".Clear ();       |";
    m[id].Clear ();
    output << "\n--------------------------------------------"
	   << "\n                   |";
    output << "\n--------------------------------------------";
}

//----------------------------------------------------------------------

global_procedure_body Do_Put_To ()
{
    object Integer id;

    if (interactive)
    {
	output << "Put which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\nm" << id << " = ";
    output << m[id];
    output << "\n--------------------------------------------";
}

//----------------------------------------------------------------------

global_procedure_body Do_Define ()
{
    object Integer id;
    object Natural_Number_1_C d;
    object Text r;

    if (interactive)
    {
	output << "Define into which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... d value? ";
    }
    input >> d;
    if (interactive)
    {
	output << "  ... r value? ";
    }
    input >> r;
    output << "\n--------------------------------------------"
	   << "\n                   |  d = " << d
	   << "\n                   |  r = " << r;
    output << "\n--------------------------------------------"
	 << "\nm" << id << ".Define (d, r);  |";
    m[id].Define (d, r);
    output << "\n--------------------------------------------"
	   << "\n                   |  d = " << d
	   << "\n                   |  r = " << r;
    output << "\n--------------------------------------------";
}

//----------------------------------------------------------------------

global_procedure_body Do_Undefine ()
{
    object Integer id;
    object Natural_Number_1_C d, d_copy;
    object Text r;

    if (interactive)
    {
	output << "Undefine from which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... d value? ";
    }
    input >> d;
    if (interactive)
    {
	output << "  ... d_copy value? ";
    }
    input >> d_copy;
    if (interactive)
    {
	output << "  ... r value? ";
    }
    input >> r;
    output << "\n--------------------------------------------"
	   << "\n                   |  d = " << d
	   << "\n                   |  d_copy = " << d_copy
	   << "\n                   |  r = " << r;
    output << "\n--------------------------------------------"
	   << "\nm" << id << ".Undefine (d, d_copy, r);  |";
    m[id].Undefine (d, d_copy, r);
    output << "\n--------------------------------------------"
	   << "\n                   |  d = " << d
	   << "\n                   |  d_copy = " << d_copy
	   << "\n                   |  r = " << r;
    output << "\n--------------------------------------------";
}

//----------------------------------------------------------------------

global_procedure_body Do_Undefine_Any ()
{
    object Integer id;
    object Natural_Number_1_C d;
    object Text r;

    if (interactive)
    {
	output << "Undefine_Any from which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... d value? ";
    }
    input >> d;
    if (interactive)
    {
	output << "  ... r value? ";
    }
    input >> r;
    output << "\n--------------------------------------------"
	   << "\n                   |  d = " << d
	   << "\n                   |  r = " << r;
    output << "\n--------------------------------------------"
	   << "\nm" << id << ".Undefine_Any (d, r);  |";
    m[id].Undefine_Any (d, r);
    output << "\n--------------------------------------------"
	   << "\n                   |  d = " << d
	   << "\n                   |  r = " << r;
    output << "\n--------------------------------------------";
}

//----------------------------------------------------------------------

global_procedure_body Do_Is_Defined ()
{
    object Integer id;
    object Natural_Number_1_C d;
    object Boolean b;

    if (interactive)
    {
	output << "Is_Defined in which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... d value? ";
    }
    input >> d;
    output << "\n--------------------------------------------"
	   << "\n                   |  d = " << d
	   << "\n                   |  b = ?";
    output << "\n--------------------------------------------"
	   << "\nb = m" << id << ".Is_Defined (d);  |";
    b = m[id].Is_Defined (d);
    output << "\n--------------------------------------------"
	   << "\n                   |  d = " << d
	   << "\n                   |  b = " << b;
    output << "\n--------------------------------------------";
}

//----------------------------------------------------------------------

global_procedure_body Do_Swap_Using_Accessor ()
{
    object Integer id;
    object Natural_Number_1_C d;
    object Text r;

    if (interactive)
    {
	output << "Swap using accessor in which object? ";
    }
    input >> id;
    if (interactive)
    {
	output << "  ... d value? ";
    }
    input >> d;
    if (interactive)
    {
	output << "  ... r value to swap with? ";
    }
    input >> r;
    output << "\n--------------------------------------------"
	   << "\n                   |  d = " << d
	   << "\n                   |  r = " << r;
    output << "\n--------------------------------------------"
	   << "\nr &= m" << id << "[d];        |";
    r &= m[id][d];
    output << "\n--------------------------------------------"
	   << "\n                   |  d = " << d
	   << "\n                   |  r = " << r;
    output << "\n--------------------------------------------";
}

//----------------------------------------------------------------------

global_procedure_body Do_Size ()
{
    object Integer id;
    object Integer i;

    if (interactive)
    {
	output << "Get size of which object? ";
    }
    input >> id;
    output << "\n--------------------------------------------"
	   << "\n                   |  i = ?";
    output << "\n--------------------------------------------"
	   << "\ni = m" << id << ".Size ();    |";
    i = m[id].Size ();
    output << "\n--------------------------------------------"
	   << "\n                   |  i = " << i;
    output << "\n--------------------------------------------";
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

program_body main ()
{
    object Boolean finished;
    
    // Open input and output streams
    
    input.Open_External ("");
    output.Open_External ("");

    // Set number of test objects (= 8; this number is absolutely NOT
    // related to the number of buckets in the hash table, when the
    // Partial_Map_Kernel implementation uses hashing)

    m.Set_Bounds (0, 7);

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
		    Do_Swap ();
		}
		break;
	        case 'c':
		{
		    Do_Clear ();
		}
		break;
	        case 'p':
		{
		    Do_Put_To ();
		}
		break;
	        case 'd':
		{
		    Do_Define ();
		}
		break;
	        case 'u':
		{
		    Do_Undefine ();
		}
		break;
	        case 'a':
		{
		    Do_Undefine_Any ();
		}
		break;
	        case 'i':
		{
		    Do_Is_Defined ();
		}
		break;
	        case '[':
		{
		    Do_Swap_Using_Accessor ();
		}
		break;
	        case 'z':
		{
		    Do_Size ();
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
}
