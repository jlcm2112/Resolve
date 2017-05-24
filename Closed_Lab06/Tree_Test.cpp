//  /*--------------------------------------------------------*\
//  |   Main Program: Test driver for "Get_Tree" and "Put_Tree"
//  |*--------------------------------------------------------*|
//  |   Date:    14 December 2007     
//  |   Author:  Bruce W. Weide    
//  |   
//  |   Brief User's Manual:
//  |   Allows user either to exercise Get_Tree and Put_Tree
//  |   in either an interactive menu-driven mode or in a batch
//  |   file mode (using input redirection).
//  |   
//  \*--------------------------------------------------------*/


///-------------------------------------------------------------
/// Global Context ---------------------------------------------
///-------------------------------------------------------------

#include "RESOLVE_Foundation.h"
#include "CT/Binary_Tree/Kernel_1a_C.h"
#include "CT/Array/Kernel_1_C.h"

///-------------------------------------------------------------
/// Interface --------------------------------------------------
///-------------------------------------------------------------

/*!
    math definition PREFIX_DISPLAY (
	    t: binary tree of character
	): string of character satisfies
	if t = empty_tree
	then
	    PREFIX_DISPLAY (t) = "()"
	else
	    there exists ch: character,
			 t0, t1: binary tree of character
		(t = compose (ch, t0, t1) and
		 PREFIX_DISPLAY (t) = <ch> * "(" *
				      PREFIX_DISPLAY (t0) *
				      PREFIX_DISPLAY (t1) * ")")
!*/

///-------------------------------------------------------------
/// Template instantiations  -----------------------------------
///-------------------------------------------------------------

concrete_instance
class Binary_Tree_Of_Character :
    instantiates
	Binary_Tree_Kernel_1a_C <Character>
{};

//--------------------------------------------------------------

concrete_instance
class Array_Of_Tree :
    instantiates
	Array_Kernel_1_C <Binary_Tree_Of_Character>
{};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Program control objects

object Boolean interactive;
object Text command_line;
object Character command_code;
object Character_IStream ins;
object Character_OStream outs;

// Test objects

object Array_Of_Tree tree;

//----------------------------------------------------------------------
// Global operation headers --------------------------------------------
//----------------------------------------------------------------------

global_procedure Put_Tree(
	preserves Binary_Tree_Of_Character& t,
	alters Character_OStream& outs
    );
/*!
    requires
	outs.is_open = true
    ensures
	outs.is_open = true and
	outs.ext_name = #outs.ext_name and
	outs.content = #outs.content * PREFIX_DISPLAY (t)
!*/

//--------------------------------------------------------------

global_procedure Get_Tree(
	alters Text& tree_as_text,
	produces Binary_Tree_Of_Character& t
    );
/*!
    requires
	there exists x, y: string of character,
		     t1: binary tree of character
	    (tree_as_text = x * y and
	     x = PREFIX_DISPLAY (t1))
    ensures
	#tree_as_text = PREFIX_DISPLAY (t) * tree_as_text
!*/

global_function Binary_Tree_Of_Character Build_Sub_Tree(
	consumes Text& text
	);

	
//----------------------------------------------------------------------
// Global operation bodies ---------------------------------------------
//----------------------------------------------------------------------

global_procedure_body Put_Tree(
	preserves Binary_Tree_Of_Character& t,
	alters Character_OStream& outs
    )
{
    //-------- for students to fill in --------
	object Binary_Tree_Of_Character left, right;
	object Character c;
	if(t.Size()>0)
	{
		t.Decompose(c, left, right);
	
	outs << c << "(";
	if(left.Size() > 0)
	{
		Put_Tree(left, outs);
	}
	else
	{
		outs << "()";
	}
	if(right.Size() > 0)
	{
		Put_Tree(right, outs);
	}
	else
	{
		outs << "()";
	}
	outs << ")";
	t.Compose(c, left, right);
	}
	else
	{
		outs << "()";
	}
}


//--------------------------------------------------------------

global_procedure_body Get_Tree(
	alters Text& tree_as_text,
	produces Binary_Tree_Of_Character& t
    )
{
    //-------- for students to fill in --------
	Binary_Tree_Of_Character tree, left_tree, right_tree;
	object Character root, c;
	object Integer i;
	object Text temp, left, right;
	
	
	if(tree_as_text.Length()>=7)
	{
		tree_as_text.Remove(0, root);
		tree_as_text.Remove(0, c);
		tree_as_text.Remove(tree_as_text.Length()-1, c);
		tree_as_text.Remove(0, c);
		if(c=='(')
		{
			i++;
		}
		temp.Add(temp.Length(), c);
		tree_as_text.Remove(0, c);
		if(c=='(')
		{
			i++;
		}
		else if(c==')')
		{
			i--;
		}
		temp.Add(temp.Length(), c);
		while(not (i==0))
		{
			tree_as_text.Remove(0, c);
			if(c=='(')
			{
				i++;
			}
			else if(c==')')
			{
				i--;
			}
			temp.Add(temp.Length(), c);
		}
		temp &= left;
		tree_as_text &= right;
		Get_Tree(left, left_tree);
		Get_Tree(right, right_tree);
		tree.Compose(root, left_tree, right_tree);
	}
}

//--------------------------------------------------------------

global_procedure_body Determine_Interactive_Mode ()
{
    object Text user_response;
    
    outs << "Run in interactive mode (y/n)? ";
    ins >> user_response;
    outs << "\n";
    interactive =  (user_response[0] == 'y');

}

//--------------------------------------------------------------

global_procedure_body Get_Command ()
{
    if (interactive)
    {
	// Show menu of commands:
	// Concept-specific operations
	
	outs << "\n\nCommand: p [Put_Tree]\n"
	     << "         g [Get_Tree]\n"
		    
	// Tester control operations
	
	     << "         q [Quit]: ";
    }

    // Get next command line and code
	     
    ins >> command_line;
    command_code = command_line[0];  
}

//--------------------------------------------------------------

global_procedure_body Do_Put_Tree ()
{
    object Integer tree_number;

    if (interactive)
    {
	outs << "Apply Put_Tree to which tree? ";
    }
    
    // get the tree number and report results of put tree

    ins >> tree_number;

    outs << "-------------------------------------------------\n"
         << "tree[" << tree_number << "] = ";
    Put_Tree (tree[tree_number], outs);
    outs << "\n";
    outs << "-------------------------------------------------\n";

}

//--------------------------------------------------------------

global_procedure_body Do_Get_Tree ()
{
    object Integer tree_number;
    object Text prefix_rep;

    if (interactive)
    {
	outs << "Apply Get_Tree to which tree? ";
    }
    
    // get the tree number 

    ins >> tree_number;

    if (interactive)
    {
	outs << "  ... Enter the prefix representation of a tree: ";
    }

    //  get the prefix representation

    ins >> prefix_rep;
    
        // Report results of this test case

    outs << "-------------------------------------------------\n"
	 << "                      |  prefix_rep  = " 
         << prefix_rep << '\n'
	 << "-------------------------------------------------\n";
    Get_Tree (prefix_rep,tree[tree_number]);
    outs << "Get_Tree (prefix_rep, tree[" << tree_number << "]);|\n"
	 << "-------------------------------------------------\n"
	 << "                      |  prefix_rep  = " 
         << prefix_rep << '\n'
	 << "-------------------------------------------------\n";
}

//--------------------------------------------------------------
//--------------------------------------------------------------

program_body main ()
{
    object Boolean finished;

    //  set array of tree bounds

    tree.Set_Bounds (0, 9);

    // Open input and output streams

    ins.Open_External ("");
    outs.Open_External ("");

    // Ask user about interactive mode

    Determine_Interactive_Mode ( );

    // Execute interactive testing loop until finished

    while (not finished)
    {
        // Ask user for next command

        Get_Command ();

        // Perform next command

        case_select (command_code)
        {
            // Concept-specific operations

            case 'g':
	    {
                Do_Get_Tree ();
	    }
	    break;

	    case 'p':
	    {
                Do_Put_Tree ();
	    }
	    break;

            // Tester control operations

            case 'q':
	    {
                outs << "\n*** Quitting test program";
                finished = true;
	    }
	    break;
		
	    default:
	    {
		outs << "\n" << command_line;
	    }
	    break;
        }
     }
    

    // Close input and output streams

    ins.Close_External ();
    outs.Close_External ();
}
