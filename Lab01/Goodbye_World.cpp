//  /*--------------------------------------------------------*\
//  |   Main Program: Traditional "Hello World" program
//  |*--------------------------------------------------------*|
//  |   Date:         13 August 1996
//  |   Author:       Bruce W. Weide
//  |   
//  |   Brief User's Manual:
//  |   Outputs to the screen "Hello world" on a line by
//  |   itself, and then quits.
//  |   
//  \*--------------------------------------------------------*/


///-------------------------------------------------------------
/// Global Context ---------------------------------------------
///-------------------------------------------------------------

#include "RESOLVE_Foundation.h"


///-------------------------------------------------------------
/// Interface --------------------------------------------------
///-------------------------------------------------------------

program_body main ()
/*!
    ensures
	stdout = #stdout * "Hello world\n"
!*/
{
    object Character_OStream outs;
    
    outs.Open_External ("");
    outs << "Hello world\n";
    outs.Close_External ();
}// comment
