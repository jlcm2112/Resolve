//  /*--------------------------------------------------------*\
//  |   Main Program: Sort test driver
//  |*--------------------------------------------------------*|
//  |   Date:         4 October 1999
//  |   Author:       Bruce W. Weide
//  |   
//  |   Brief User's Manual:
//  |   Lets the user test the "Sort" procedure extension to
//  |   Queue_Of_Text.
//  |   
//  \*--------------------------------------------------------*/

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "CT/Queue/Kernel_1a_C.h"
#include "CT/Queue_Of_Text/Sort_1.h"

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

/*!
    math operation LINES (
	    s: string of character
	): string of string of character satisfies
	if s = empty_string
	then LINES(s) = empty_string
	else if "\n" is not substring of s
	    then LINES(s) = <s>
	    else there exists a, b: string of character
		     (s = a * "\n" * b  and
		      "\n" is not substring of a  and
		      LINES(s) = <a> * LINES(b))

    math operation IS_ORDERED (
	    s: string of string of character
	): boolean is
	for all x, y: string of character
		where (<x> * <y> is substring of s)
	    (x <= y)
!*/

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Concrete instances

concrete_instance
class Queue_Of_Text_Base :
    instantiates Queue_Kernel_1a_C <Text>
{};

//----------------------------------------------------------------------

concrete_instance
class Queue_Of_Text:
    instantiates Queue_Of_Text_Sort_1 <
                Queue_Of_Text_Base
            >
{};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operations

global_procedure Get_Lines_From_Input (
	alters Character_IStream& input,
	produces Queue_Of_Text& q
    );
/*!
    requires
	input.is_open = true
    ensures
	input.is_open = true  and
	input.ext_name = #input.ext_name  and
	input.content = empty_string  and
	q = LINES (#input.content)
!*/
    
//----------------------------------------------------------------------

global_procedure Put_Lines_To_Output (
	alters Character_OStream& output,
	preserves Queue_Of_Text& q
    );
/*!
    requires
	output.is_open = true
    ensures
	output.is_open = true  and
	output.ext_name = #output.ext_name  and
	output.content = #output.content * [output of items of q]
!*/
    
//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operation bodies

global_procedure_body Get_Lines_From_Input (
	alters Character_IStream& input,
	produces Queue_Of_Text& q
    )
{
    assert (input.Is_Open (),
	    "input.is_open = true");
    
    q.Clear ();

    while (not input.At_EOS ())
    {
	object Text line;

	input >> line;
	q.Enqueue (line);
    }
}

//----------------------------------------------------------------------

global_procedure_body Put_Lines_To_Output (
	alters Character_OStream& output,
	preserves Queue_Of_Text& q
    )
{
    assert (output.Is_Open (),
	    "output.is_open = true");
    
    object catalyst Queue_Of_Text temp;

    output << "\n--- Start of Queue_Of_Text output ---\n";
    while (q.Length () > 0)
    {
	object Text t;
	
	q.Dequeue (t);
	output << t << "\n";
	temp.Enqueue (t);
    }
    output << "--- End of Queue_Of_Text output ---\n";

    q &= temp;
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

program_body main ()
{
    object Character_IStream input;
    object Character_OStream output;
    object Queue_Of_Text lines;

    // Open input and output streams
    
    input.Open_External ("");
    output.Open_External ("");

    // Get lines from input and output them, unsorted

    Get_Lines_From_Input (input, lines);
    Put_Lines_To_Output (output, lines);
    
    // Sort lines into non-decreasing alphabetical order

    lines.Sort ();
    
    // Output lines in sorted order

    Put_Lines_To_Output (output, lines);
    
    // Close input and output streams
    
    input.Close_External ();
    output.Close_External ();
}
