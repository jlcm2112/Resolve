//  /*--------------------------------------------------------*\
//  |   Main Program: Pretty-printer using HTML
//  |*--------------------------------------------------------*|
//  |   Date:         
//  |   Author:       
//  |   
//  |   Brief User's Manual:
//  |   Reads Resolve/C++ source file from stdin, marks it up
//  |   with HTML tags so it looks pretty-printed when viewed
//  |   in a browser, and outputs the marked-up version to
//  |   stdout.  The only markup is that the entire thing is
//  |   preformatted text; comments are in italics and in two
//  |   colors (one for formal, one for informal); keywords
//  |   (unless in comments) are in boldface.  A list of
//  |   Resolve/C++ keywords is in the file:
//  |     /class/sce/now/222/labs/lab01/Lab01/keywords.txt
//  |   
//  \*--------------------------------------------------------*/


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
	    else if "\n" is not substring of s
	    then LINES(s) = <s>
	    else there exists a, b: string of character
		     (s = a * "\n" * b  and
		      "\n" is not substring of a  and
		      LINES(s) = <a> * LINES(b))

    math defintion SEPARATORS: set of character is
	{' ', '\t', '\n', '.', ',', ';', ':', '(', ')', '[', ']',
	 '{', '}', '<', '>'}
	    
    math definition IS_WORD (
	    s: string of character
	): boolean is
        s /= empty_string  and
        elements(s) intersect SEPARATORS = empty_set

    math definition CONTAINS_WORD (
	    s: string of character
	): boolean is
	there exists w: string of character
	    (w is substring of s  and
	     IS_WORD(w))

    math operation HTML_LT_SUBSTITUTED (
	    s: string of character
	): string of character
	implicit definition
	    if s = empty_string
	    then HTML_LT_SUBSTITUTED(s) = empty_string
	    else if "<" is not substring of s
	    then HTML_LT_SUBSTITUTED(s) = s
	    else there exists a, b: string of character
		     (s = a * "<" * b  and
		      "<" is not substring of a  and
		      HTML_LT_SUBSTITUTED(s) =
		          a * "&lt;" * HTML_LT_SUBSTITUTED(b))

    math operation HTML_GT_SUBSTITUTED (
	    s: string of character
	): string of character
	implicit definition
	    if s = empty_string
	    then HTML_GT_SUBSTITUTED(s) = empty_string
	    else if ">" is not substring of s
	    then HTML_GT_SUBSTITUTED(s) = s
	    else there exists a, b: string of character
		     (s = a * ">" * b  and
		      ">" is not substring of a  and
		      HTML_GT_SUBSTITUTED(s) =
		          a * "&gt;" * HTML_GT_SUBSTITUTED(b))
!*/

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Concrete instances

concrete_instance
class Set_Of_Character :
   instantiates Set_Kernel_1_C < Character >
{};

concrete_instance
class Set_Of_Text :
    instantiates Set_Kernel_1_C < Text >
{};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operations

global_procedure Create_Separators_Set (
	produces Set_Of_Character& separators
    );
/*!
    ensures
	separators = SEPARATORS
!*/
    
//----------------------------------------------------------------------

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

global_procedure Remove_First_Word (
        alters Text& t,
	preserves Set_Of_Character& separators,
        produces Text& leading_separators,
        produces Text& word
    );
/*!
    requires
    there exists c: character
	    (<c> is suffix of t  and
	     c is in SEPARATORS)
    ensures
	if CONTAINS_WORD(#t) then
	    (#t = leading_separators * word * t  and
	     elements(leading_separators) is subset of SEPARATORS  and
	     IS_WORD(word)  and
	     there exists c: character
		 (<c> is prefix of t  and
		  c is in SEPARATORS))
	else
	    (leading_separators = #t  and
	     word = empty_string  and
	     t = empty_string)
!*/
    
//----------------------------------------------------------------------

global_function Boolean Prefix_Is_Start_Of_One_Line_Comment (
	preserves Text t
    );
/*!
    ensures
	Prefix_Is_Start_Of_One_Line_Comment = "//" is prefix of t
!*/
    
//----------------------------------------------------------------------

global_function Boolean Prefix_Is_Start_Of_Formal_Comment (
	preserves Text t
    );
/*!
    ensures
	Prefix_Is_Start_Of_Formal_Comment = "/*!" is prefix of t
!*/
    
//----------------------------------------------------------------------

global_function Boolean Prefix_Is_Start_Of_Informal_Comment (
	preserves Text t
    );
/*!
    ensures
	Prefix_Is_Start_Of_Informal_Comment = "/*" is prefix of t
!*/
    
//----------------------------------------------------------------------

global_function Boolean Suffix_Is_End_Of_Comment (
	preserves Text t
    );
/*!
    ensures
        Suffix_Is_End_Of_Comment = <'*'> * <'/'> is suffix of t
!*/
    
//----------------------------------------------------------------------

global_procedure Put_With_HTML_Substitutions (
	alters Character_OStream& output,
	preserves Text t
    );
/*!
    requires
	output.is_open = true
    ensures
	output.is_open = true  and
	output.ext_name = #output.ext_name  and
	output.content = #output.content *
	                 HTML_GT_SUBSTITUTED (HTML_LT_SUBSTITUTED (t))
!*/
    
//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operation bodies

global_procedure_body Create_Separators_Set (
	produces Set_Of_Character& separators
    )
{
    object catalyst Character c;

    separators.Clear ();

    c = ' ';
    separators.Add (c);
    c = '\t';
    separators.Add (c);
    c = '\n';
    separators.Add (c);
    c = '.';
    separators.Add (c);
    c = ',';
    separators.Add (c);
    c = ';';
    separators.Add (c);
    c = ':';
    separators.Add (c);
    c = '(';
    separators.Add (c);
    c = ')';
    separators.Add (c);
    c = '[';
    separators.Add (c);
    c = ']';
    separators.Add (c);
    c = '{';
    separators.Add (c);
    c = '}';
    separators.Add (c);
    c = '<';
    separators.Add (c);
    c = '>';
    separators.Add (c);
}

//----------------------------------------------------------------------

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

global_procedure_body Remove_First_Word (
        alters Text& t,
	preserves Set_Of_Character& separators,
        produces Text& leading_separators,
        produces Text& word
    )
{
    assert (t.Length () > 0,
	    "there exists c: character\n"
	    "    (<c> is suffix of t)");
    assert (separators.Is_Member (t[t.Length () - 1]),
	    "there exists c: character\n"
	    "    (<c> is suffix of t  and\n"
	    "     c is in SEPARATORS)");
   	
    object Character sentinel = 'X';
	
    leading_separators.Clear ();
    word.Clear ();

    // Add a sentinel non-separators character to the end of t
    
    t.Add (t.Length (), sentinel);

    // Remove leading separators characters from t; loop can't run
    // off the end of t because of the sentinel
    
    while (separators.Is_Member (t[0]))
    {
        object Character ch;
	t.Remove (0, ch);
	leading_separators.Add (leading_separators.Length (), ch);
    }

    // Remove the word now at the start of t, if any
    
    if (t.Length () > 1)
    {
	// There was a word in #t, so remove the longest prefix of t
	// that is a word, AND the sentinel

	while (not separators.Is_Member (t[0]))
	{
	    object Character ch;
	    t.Remove (0, ch);
	    word.Add (word.Length (), ch);
	}

	t.Remove (t.Length () - 1, sentinel);
    }
    else
    {
	// There were no words in #t, so remove the sentinel (the only
	// character left in t) and return, since leading_separators
	// and word have correct values now

	t.Remove (0, sentinel);
    }    
}    

//----------------------------------------------------------------------

global_function_body Boolean Prefix_Is_Start_Of_One_Line_Comment (
	preserves Text t
    )
{
    if (t.Length () < 2)
    {
	return false;
    }
    else
    {
	return (t[0] == '/' and t[1] == '/');
    }
}

//----------------------------------------------------------------------

global_function_body Boolean Prefix_Is_Start_Of_Formal_Comment (
	preserves Text t
    )
{
    if (t.Length () < 3)
    {
	return false;
    }
    else
    {
	return (t[0] == '/' and t[1] == '*' and t[2] == '!');
    }
}
    
//----------------------------------------------------------------------

global_function_body Boolean Prefix_Is_Start_Of_Informal_Comment (
	preserves Text t
    )
{
    if (t.Length () < 2)
    {
	return false;
    }
    else
    {
	return (t[0] == '/' and t[1] == '*');
    }
}    
//----------------------------------------------------------------------

global_function_body Boolean Suffix_Is_End_Of_Comment (
	preserves Text t
    )
{
    if (t.Length () <2)
    {
	return false;
    }
    else
    {
	return (t[t.Length()-2] == '*' and t[t.Length()-1] == '/');
    }
}
    
//----------------------------------------------------------------------

global_procedure_body Put_With_HTML_Substitutions (
	alters Character_OStream& output,
	preserves Text t
    )
{
    assert (output.Is_Open (),
	    "output.is_open = true");

    object Text temp, x;
    
    while (t.Length() > 0)
    {
	 object Character c;
	 t.Remove(0, c);
	 temp.Add(temp.Length(), c);
	 if (c == '<')
	 {
	     x.Add(x.Length(), '&');
	     x.Add(x.Length(), 'l');
	     x.Add(x.Length(), 't');
	     x.Add(x.Length(), ';');
	 }
	 else if (c == '>')
	 {
	     x.Add(x.Length(), '&');
	     x.Add(x.Length(), 'g');
	     x.Add(x.Length(), 't');
	     x.Add(x.Length(), ';');
	 }
	 else
	     x.Add(x.Length(), c);
    }

    t &= temp;
    output << x;
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

program_body main ()
{
    object Character_IStream input;
    object Character_OStream output;
    object Set_Of_Character separators;
    object Set_Of_Text keywords;
    object Boolean in_comment;
    object Text temp;

    // Initialize separators set

    Create_Separators_Set (separators);
    
    // Get keywords

    input.Open_External ("keywords.txt");
    Get_Words (input, keywords);
    input.Close_External ();
    
    // Open input and output streams
    
    input.Open_External ("");
    output.Open_External ("");

    // Output prologue

    output << "<HTML>\n<BODY>\n<PRE>\n";

    // Process input one line of program at a time, marking up as needed

    while (not input.At_EOS ())
    {
	object Text line;
	
	input >> line;

	// Add newline back onto end of line; not added by >> operator
	
	line.Add (line.Length (), '\n');

	while (line.Length () > 0)
	{
	   
           object Text leading_separators, word;	    
	   Remove_First_Word(line, separators, leading_separators, word);

	   //check for one line comments, unless in a comment  
	if (not in_comment and Prefix_Is_Start_Of_One_Line_Comment(word) == true)
	{      	
	    output << leading_separators << "<FONT COLOR=\"ForestGreen\"><I>" <<  word;
	    //when one-line comment occurs, output until the end of the line
		    while (line.Length()>0)
		    {
       	        	   Remove_First_Word(line, separators, leading_separators, word);
			   Put_With_HTML_Substitutions(output, leading_separators);
			   output << word;
		    }
		    	    
		       output << "</I></FONT>" ;
		       in_comment = false;
		       break; //go to new line
		    
	}
        //check for multi-line comments
          else  if (not in_comment)
	    {
	      
	        if (Prefix_Is_Start_Of_Formal_Comment(word) == true)
		{
		    output << "<FONT COLOR=\"SaddleBrown\"><I>";
		    in_comment = true;
		}
		
	        else if (Prefix_Is_Start_Of_Informal_Comment(word) == true)
	      	{
		    Put_With_HTML_Substitutions(output, leading_separators);
		    output << "<FONT COLOR=\"ForestGreen\"><i>";
		    in_comment = true;
	        }
	    }
	//check for end of comment
	    else if (in_comment and Suffix_Is_End_Of_Comment(word) == true)
	        {
		    Put_With_HTML_Substitutions(output, leading_separators);
		    output << word << "</I></FONT>" ;
		in_comment = false;
		continue; //restart the loop to avoid printing the
			  //word twice
	        }
	    
	
		 
            //check for keywords, then output words
            if (not in_comment and keywords.Is_Member(word))
		    output << "<B>" << word << "</B>";
	        else
		     output << word;
	    
	}	

    } 

    // Output epilogue

    output << "</PRE>\n</BODY>\n</HTML>\n";

    // Close input and output streams
    
    input.Close_External ();
    output.Close_External ();
}
