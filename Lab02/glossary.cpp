//-----------------------------------------------------------------------
//---global context------------------------------------------------------
//-----------------------------------------------------------------------

#include "RESOLVE_Foundation.h"
#include "CT/Sorting_Machine/Kernel_1_C.h"
#include "CI/Text/Are_In_Order_1.h" 
#include "CT/Partial_Map/Kernel_1_C.h"
#include "CT/Set/Kernel_1_C.h"

//-----------------------------------------------------------------------
//---concrete instances--------------------------------------------------
//-----------------------------------------------------------------------
concrete_instance 
class Sorting_Machine_Of_Text : 
    instantiates 
        Sorting_Machine_Kernel_1_C <Text, Text_Are_In_Order_1> 
{}; 

concrete_instance 
class Partial_Map_Instance : 
    instantiates 
        Partial_Map_Kernel_1_C <Text, Text> 
{}; 

concrete_instance
class Set_Of_Character : 
   instantiates 
       Set_Kernel_1_C <Character>
{};

concrete_instance
class Set_Of_Text : 
    instantiates 
        Set_Kernel_1_C <Text>
{};

//-----------------------------------------------------------------------
//---global operation headers--------------------------------------------
//-----------------------------------------------------------------------
global_procedure Create_Separators_Set (
	produces Set_Of_Character& separators
					     );
//--------------------------------
global_procedure Get_Terms_And_Defs (
   alters Character_IStream& input, 
   produces Sorting_Machine_Of_Text& s1, 
   produces Partial_Map_Instance& p1,
   preserves Set_Of_Character& separators,
   produces Set_Of_Text& terms
   
				     );
//-------------------------------
global_procedure_body Consume_Term (
	alters Character_IStream& input, 
	alters Sorting_Machine_Of_Text& s1, 
	alters Partial_Map_Instance& p1, 
	preserves Set_Of_Character& separators,
	alters Set_Of_Text& terms,
	produces Text& t
				    );

//--------------------------------
global_procedure_body Consume_Definition (
	  alters Character_IStream& input, 
	  alters Partial_Map_Instance& p1, 
	  preserves Set_Of_Character& separators,
	  consumes Text& t
					  );
//-------------------------------
global_procedure Remove_First_Word (
        alters Text& t,
	preserves Set_Of_Character& separators,   
	preserves Text& leading_separators,
        produces Text& word
					 );
//-------------------------------
global_procedure Put_With_HTML_Substitutions (
	alters Character_OStream& output,
	preserves Text t
				       	   );

//-------------------------------
global_procedure Create_Glossary (
	 consumes Sorting_Machine_Of_Text& s1,
	 preserves Partial_Map_Instance& p1,
	 /* I don't know if I really needed to keep the pmap in preserves mode... It seems inefficient to just redefine
	    the pmap item after taking it out... but I guess for code reusability it might be useful, and closed lab 3 
	    preserved the pmap for pizza orders, so I thought I should... please let me know what you think of this? Ty! */
	 preserves Set_Of_Text& terms,
	 produces Text& index,
	 produces Text& definitions,
	 preserves Set_Of_Character& separators

				       );
//-------------------------------
global_procedure Put_With_Links (
    alters Character_OStream& output,
    preserves Text t,
    preserves Set_Of_Text& set
				      );


//-----------------------------------------------------------------------
//---global operation bodies---------------------------------------------
//-----------------------------------------------------------------------

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

//-------------------------------
global_procedure_body Get_Terms_And_Defs (
   alters Character_IStream& input, 
   produces Sorting_Machine_Of_Text& s1, 
   produces Partial_Map_Instance& p1,
   preserves Set_Of_Character& separators,
   produces Set_Of_Text& terms
   
)
{
      assert (input.Is_Open (),
        "input.is_open = true");
      assert (not input.At_EOS (),
	"input.content begins with a Term & Definition;\n"
	"in particular,\n"
	      " 0 < |input.content|");

      object Text t, d, line, leading_separators;


  while (not input.At_EOS())
    {        

      Consume_Term (input, s1, p1, separators, terms, t);
      Consume_Definition (input, p1, separators, t);
	  
    }
}

//-------------------------------
global_procedure_body Consume_Term (
	alters Character_IStream& input, 
	alters Sorting_Machine_Of_Text& s1, 
	alters Partial_Map_Instance& p1, 
	preserves Set_Of_Character& separators,
	alters Set_Of_Text& terms,
	produces Text& t
)
{
  object catalyst Text line, leading_separators;
  input >> line;
  line.Add(line.Length(), '\n');

  Remove_First_Word (line, separators, leading_separators, t); //strips whitespace from term t
    
  //if the term is NOT in the set, add term to the set, to the D_item of the partial map, and to the sorting machine.
  if (not terms.Is_Member(t))
      {
        object catalyst Text t_copy, t_copy2, t_copy3, blank;
        t_copy = t;
        t_copy2 = t;
        t_copy3 = t;
        terms.Add(t_copy); 
        p1.Define (t_copy2, blank);	      
        s1.Insert (t_copy3);
	     
       }
	
}
//-------------------------------
global_procedure_body Consume_Definition (
	  alters Character_IStream& input, 
	  alters Partial_Map_Instance& p1, 
	  preserves Set_Of_Character& separators,
	  consumes Text& t
)
{
  object catalyst Character_OStream mystream;
  object catalyst Text line, t_copy, d;

  if (not input.At_EOS())
    {
      input >> line;
      line.Add(line.Length(), '\n');
    }
  
  
  if (line.Length() > 1)
    {
      mystream.Open_Internal ();
      p1.Undefine (t, t_copy, d); // take it out
      mystream << d;

      while (line.Length() > 1)
	{
	  object catalyst Text word, leading_separators;
	  Remove_First_Word (line, separators, leading_separators, word);

	  Put_With_HTML_Substitutions (mystream, leading_separators);
	  mystream << word;
	}
      mystream << '\n';
     
      mystream.Close_Internal(d); 
  
      p1.Define (t, d);  // put it back

      Consume_Definition (input, p1, separators, t_copy); //recursive call
    }
  else
    {
      /* It puts the lotion on its skin, or else it gets the hose again*/
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
//----------------------------------

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
//-------------------------------
global_procedure_body Create_Glossary (
	 consumes Sorting_Machine_Of_Text& s1,
	 preserves Partial_Map_Instance& p1,
	 preserves Set_Of_Text& terms,
	 produces Text& index,
	 produces Text& definitions,
	 preserves Set_Of_Character& separators
      )
{
  object catalyst Character_OStream t_stream, d_stream; 

  index.Clear();
  definitions.Clear();

  //t_stream and d_stream are used to hold both sections of the glossary until they are ready for external output
  t_stream.Open_Internal ();
  d_stream.Open_Internal ();
  
  t_stream << "<H3>Index</H3>\n\n<UL>\n";
  d_stream << "<H3>Terms and Definitions</H3>\n\n";

  while (s1.Size() > 0)
    {
      object catalyst Text t, t_copy, def;

      t.Clear();
      t_copy.Clear();
      def.Clear();
      s1.Remove_First(t);
      p1.Undefine(t, t_copy, def);

      t_stream << "<LI><A HREF=\"#" << t << "\">" << t << "</A></LI>\n";
      d_stream << "<P><A NAME=\"" << t << "\"></A><FONT COLOR=RED><B><I>" << t << "</I></B></FONT></P>\n\n";
      d_stream << "<UL>\n<P>";
      def.Add(def.Length(), '\n');

      while (def.Length() > 1)
	{
	  object catalyst Text leading_separators;
	  Remove_First_Word (def, separators, leading_separators, t);
	  Put_With_HTML_Substitutions (d_stream, leading_separators);
	    Put_With_Links (d_stream, t, terms);	    
	}
      d_stream << "\n</P>\n</UL>\n\n";
      if (not p1.Is_Defined(def))
	{
	  p1.Define(t, def);
	}
    }

    t_stream << "</UL>" ;
    
      t_stream.Close_Internal (index); 
      d_stream.Close_Internal (definitions); // streams are now in text objects

}
//-------------------------------

global_procedure_body Put_With_Links (
    alters Character_OStream& output,
    preserves Text word,
    preserves Set_Of_Text& terms
)
{
   assert (output.Is_Open (),
	    "output.is_open = true");

   if (terms.Is_Member(word))
     {
       output << "<A HREF=\"#" << word << "\">" << word << "</A>";
     }
   else
     {
       output << word;
     }
   
}

//-------------------------------
//----------main-----------------
//-------------------------------

program_body main ()
{
    object Character_IStream input;
    object Character_OStream output;
    object Set_Of_Character separators;
    object Set_Of_Text terms;
    object Text index, definitions;
    object Sorting_Machine_Of_Text s1;
    object Partial_Map_Instance p1;

    // Initialize separators set
    Create_Separators_Set (separators);

    // Open Input and Output Streams
    input.Open_External ("");
    output.Open_External ("");

    // input file, create the set and sorting machine of terms, as well as the partial map of terms & definitions.
    Get_Terms_And_Defs (input, s1, p1, separators, terms);

    // Output prologue
    output << "<HTML>\n<HEAD>\n<TITLE>Glossary</TITLE>\n</HEAD>\n<BODY BGCOLOR=WHITE>\n<FONT SIZE=+2>\n\n";

    // Sort the terms in sorting machine 
    s1.Change_To_Extraction_Phase ();

    // Prepare both sections of the glossary for output
    Create_Glossary (s1, p1, terms, index, definitions, separators);

    // Output glossary
    output << index << "\n\n<HR>\n\n" << definitions;    

    // Output epilogue
    output << "\n<HR>\n\n</FONT>\n</BODY>\n</HTML>\n";

    // Close External input and output streams    
    input.Close_External ();
    output.Close_External ();
}

