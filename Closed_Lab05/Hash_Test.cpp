//  /*--------------------------------------------------------*\
//  |   Main Program: Hash Function Test Driver
//  |*--------------------------------------------------------*|
//  |   Date:         22 May 1997, revised 8 November 1999
//  |   Author:       Bruce W. Weide
//  |   Date:         19 November 2003
//  |   Modifier:     Wayne D. Heym
//  |   
//  |   Brief User's Manual:
//  |   Lets the user test the "Hash" procedure of "Text_Hash"
//  |   utility class, by reading text lines from a file (whose
//  |   name is supplied by the user), and then outputting the
//  |   distribution of lines into buckets.
//  |   
//  \*--------------------------------------------------------*/

///-------------------------------------------------------------
/// Global Context ---------------------------------------------
///-------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "AT/General/Hash.h"
#include "CT/Array/Kernel_1_C.h"
#include "CT/Set/Kernel_2_C.h"
#include "CI/Text/Hash_1.h"

///-------------------------------------------------------------
/// Interface --------------------------------------------------
///-------------------------------------------------------------

concrete_instance
utility_class Text_Hash :
    implements
        abstract_instance General_Hash <Text>
{
public:

    /*!
	math operation HASH_FUNCTION (
		t: string of character
	    ): integer satisfies
	    if t = empty_string
	    then HASH_FUNCTION (t) = 0
	    else there exists c: character, s: string of character
		     (t = <c> * s  and
		      HASH_FUNCTION (t) = TO_INTEGER (c) +
			  HASH_FUNCTION (s))
    !*/

    utility_function_body Integer Hash (
	    preserves Text& t
	)
    {
	//-------- for students to fill in --------

	// The specification of Text_Hash::Hash, which is in the
	// abstract template General_Hash, is that it ensures that
	// Hash = HASH_FUNCTION(t).

	// If you are very observant, you might note that t is a
	// preserves-mode parameter of type Text, so technically it seems
	// t should not have an ampersand "&" after the type name.  The
	// reason this is different is that General_Hash<Item>::Hash has a
	// parameter of type Item, and this means the parameter to Hash
	// MUST have an ampersand after it because Item might NOT be a
	// built-in type.  The latter rule takes precedence; but this is
	// an unusual situation, so don't worry about it.  The only way it
	// would make any difference is if you were calling
	// Text_Hash::Hash with a Text literal as the argument , e.g.,
	// Text_Hash::Hash ("something like this").

	// Note also that, although the above definition of HASH_FUNCTION
	// is recursive (inductive), this does NOT mean that you must
	// write a recursive body for Hash!  If you understand the
	// definition, then it should be just as easy to write an
	// iterative body as a recursive one for this operation.

    }
    
};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

concrete_instance
class Array_Of_Integer :
    instantiates Array_Kernel_1_C <Integer>
{};

//----------------------------------------------------------------------

concrete_instance
class Set_Of_Text :
    instantiates Set_Kernel_2_C <
            Text,
            Text_Hash_1, // "_1": not Text_Hash, which is under test
            1009
        >
{};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

program_body main ()
{
    object Character_IStream ins, text_file;
    object Character_OStream outs;
    object Integer hash_table_size, i, total_hits;
    object Text text_file_name;
    object Array_Of_Integer counts;
    object Set_Of_Text counted;

    // Open input and output streams
    
    ins.Open_External ("");
    outs.Open_External ("");

    // Get hash table size and file name

    outs << "Hash table size: ";
    ins >> hash_table_size;
    outs << "Text file name: ";
    ins >> text_file_name;

    // Set up counts

    counts.Set_Bounds (0, hash_table_size - 1);

    // Get some lines of input, hash them, and record counts

    text_file.Open_External (text_file_name);
    while (not text_file.At_EOS ())
    {
	object Text t;
	
	text_file >> t;
	if (not counted.Is_Member (t))
	{
	    counts[Text_Hash::Hash (t) mod hash_table_size]++;
	    total_hits++;
	    counted.Add (t);
	}
    }
    text_file.Close_External ();
    
    // Report results

    outs << "\n"
	 << "Bucket\tHits\tBar\n"
	 << "------\t----\t---\n";
    while (i <= counts.Upper_Bound ())
    {
	object Integer j;
	
	outs << i << "\t" << counts[i] << "\t";
	while (j < counts[i])
	{
	    outs << '*';
	    j++;
	}
	outs << '\n';
	i++;
    }

    outs << "\nTotal:\t" << total_hits << "\n";
        
    // Close input and output streams
    
    ins.Close_External ();
    outs.Close_External ();
}
