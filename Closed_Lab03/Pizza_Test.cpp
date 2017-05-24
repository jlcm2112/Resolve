//  /*----------------------------------------------------------------*\
//  |   Main Program: Pizza program test driver
//  |*----------------------------------------------------------------*|
//  |   Date:         16 October 1999
//  |   Author:       Bruce W. Weide
//  |   Modified:     5 December 2005
//  |   Modifier:     Wayne D. Heym
//  |   
//  |   Brief User's Manual:
//  |   Lets the user test implementations of some Partial_Map client
//  |   operations.
//  |   
//  \*----------------------------------------------------------------*/

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "CT/Partial_Map/Kernel_1_C.h"

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

// Concrete instances

concrete_instance
class Price_Map :
//-- for students to complete by instantiating Partial_Map_Kernel_1_C --
    
//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operations

global_procedure Get_Price_Map (
	preserves Text file_name,
	produces Price_Map& p_map
    );
/*!
    requires
	[file named file_name exists and is readable, and has the
	 format of one "word" and one price (in cents) per line,
	 with word and price separated by '\t'; the "word" may
	 contain whitespace other than '\t'; each "word" appears
	 at most once in the file]
    ensures
	[p_map contains word -> price mapping from file file_name]
!*/

//----------------------------------------------------------------------

global_procedure Get_One_Order (
        alters Character_IStream& input,
	preserves Price_Map& sp_map,
	preserves Price_Map& tp_map,
	produces Integer& price
    );
/*!
    requires
	input.is_open = true  and
	[input.content begins with a pizza order consisting of a
	 size (something defined in sp_map) on the first line,
	 followed by zero or more toppings (something defined in
	 tp_map) each on a separate line, followed by an empty line]
    ensures
	input.is_open = true  and
	input.ext_name = #input.ext_name  and
	#input.content = [one pizza order (as described
		in the requires clause)] * input.content  and
	price = [total price (in cents) of that pizza order]
!*/

//----------------------------------------------------------------------

global_procedure Put_Price (
	alters Character_OStream& output,
	preserves Integer price
    );
/*!
    requires
	output.is_open = true  and
	0 <= price
    ensures
	output.is_open = true  and
	output.ext_name = #output.ext_name  and
	output.content = #output.content *
	    [display of price, where price is in cents but
	     display is formatted in dollars and cents]
!*/

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operation bodies

global_procedure_body Get_Price_Map (
	preserves Text file_name,
	produces Price_Map& p_map
    )
{
    assert (File_Exists (file_name),
	    "file named file_name exists");
    assert (File_Is_Readable (file_name),
	    "file named file_name is readable");
    
    //-------- for students to fill in --------
}

//----------------------------------------------------------------------

global_procedure_body Get_One_Order (
        alters Character_IStream& input,
	preserves Price_Map& sp_map,
	preserves Price_Map& tp_map,
	produces Integer& price
    )
{
    assert (input.Is_Open (),
	    "input.is_open = true");
    assert (not input.At_EOS (),
	    "input.content begins with a pizza order;\n"
	    "in particular,\n"
	    "    0 < |input.content|");
    
    //-------- for students to fill in --------
}

//----------------------------------------------------------------------

global_procedure_body Put_Price (
	alters Character_OStream& output,
	preserves Integer price
    )
{
    //-------- for students to fill in, including "assert(s)" --------
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

program_body main ()
{
    object Character_IStream input;
    object Character_OStream output;
    object Price_Map size_menu, topping_menu;
    object Integer order_number = 1;

    // Get menus of sizes and toppings and their prices

    Get_Price_Map ("sizes.txt", size_menu);
    Get_Price_Map ("toppings.txt", topping_menu);
    
    // Open input and output streams
    
    input.Open_External ("");
    output.Open_External ("");

    // Display heading
    output << '\n';
    output << "Order\n";
    output << "Number Price\n";
    output << "------ ------\n";

    while (not input.At_EOS ())
    {
	object Integer price;
	
	Get_One_Order (input, size_menu, topping_menu, price);
	output << order_number << "      ";
	Put_Price (output, price);
	output << '\n';
	order_number++;
    }

    // Display end of list
    output << '\n';

    // Close input and output streams
    
    input.Close_External ();
    output.Close_External ();
}
