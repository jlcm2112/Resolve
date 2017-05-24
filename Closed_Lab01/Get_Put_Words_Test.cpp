//  /*----------------------------------------------------------------*\
//  |   Main Program: Test driver for "Get_Words", "Put_Words".
//  |*----------------------------------------------------------------*|
//  |   Date:         1 September 2004
//  |   Author:       Bruce W. Weide
//  |   
//  |   Brief User's Manual:
//  |   Lets the user test "Get_Words" and "Put_Words" by
//  |   using them to read input from test files, and outputting it.
//  |   
//  \*----------------------------------------------------------------*/

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "CT/Set/Kernel_1_C.h"

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

/*!
    math operation LINES (
	    s: string of character
	): string of string of character
	implicit definition
	    if s = empty_string
	    then LINES(s) = empty_string
	    else "\n" is not substring of s
	    then LINES(s) = <s>
	    else there exists a, b: string of character
		     (s = a * "\n" * b  and
		      "\n" is not substring of a  and
		      LINES(s) = <a> * LINES(b))
!*/

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Concrete instances

concrete_instance
class Set_Of_Text :
    instantiates Set_Kernel_1_C <Text>
{};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operations

global_procedure Get_Words (
	alters Character_IStream& input,
	produces Set_Of_Text& words
    );
/*!
    requires
	input.is_open = true
    ensures
	input.is_open = true  and
	input.ext_name = #input.ext_name  and
	input.content = empty_string  and
	words = elements (LINES (#input.content))
!*/

    
//----------------------------------------------------------------------

global_procedure Put_Words (
	alters Character_OStream& output,
	preserves Set_Of_Text& words
    );
/*!
    requires
	output.is_open = true
    ensures
	output.is_open = true  and
	output.ext_name = #output.ext_name  and
	output.content = #output.content *
			     [words in "words" set, appropriately
			      labelled and formatted in HTML]
!*/
    
//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operation bodies

global_procedure_body Get_Words (
	alters Character_IStream& input,
	produces Set_Of_Text& words
    )
{
    assert (input.Is_Open (),
	    "input.is_open = true");
    
     words.Clear();
     object Text t;
     while (not input.At_EOS())
     {
	 input >> t;
	 if (words.Is_Member(t) == false)
	     words.Add(t);
     }
}

//----------------------------------------------------------------------

global_procedure_body Put_Words (
	alters Character_OStream& output,
	preserves Set_Of_Text& words
    )
{
    assert (output.Is_Open (),
	    "output.is_open = true");

 object Set_Of_Text temp;
 object Text x;

 while (words.Size() >=1)
 {
     words.Remove_Any(x);
     output << x << " ";
     if (temp.Is_Member(x) == false)
     {
	 temp.Add(x);
     }
  }
    
      words  &= temp;

}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

program_body main ()
{
    object Character_IStream input;
    object Character_OStream output;
    object Set_Of_Text words_from_file;

    // Open output stream
    
    output.Open_External ("");

    // Output HTML prologue

    output << "<HTML>\n"
	   << "<BODY BGCOLOR=WHITE>\n";
    
    // Get words from first file and output them

    input.Open_External ("file1.txt");
    Get_Words (input, words_from_file);
    input.Close_External ();
    output << "<H1>Words from file1.txt</H1>\n";
    Put_Words (output, words_from_file);
    
    // Get classifier words from second file and output them

    input.Open_External ("file2.txt");
    Get_Words (input, words_from_file);
    input.Close_External ();
    output << "<H1>Words from file2.txt</H1>\n";
    Put_Words (output, words_from_file);

    // Output set of lines from second file again; except possibly for
    // the order of the words (note: sets are unordered) this output
    // should be the same as what was output just above, since
    // Put_Words is supposed to preserve its second
    // argument!  It's OK if the words come out in the same order,
    // and it's OK if they come out in a different order, so long as
    // you get the same set of words.

    output << "<H1>Words from file2.txt (again)</H1>\n";
    Put_Words (output, words_from_file);
    
    // Output HTML epilogue

    output << "</BODY>\n"
	   << "</HTML>\n";
    
    // Close output stream
    
    output.Close_External ();
}
