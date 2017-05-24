//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Sequence_Kernel_3
//  \*-------------------------------------------------------------------*/

#ifndef CT_SEQUENCE_KERNEL_3
#define CT_SEQUENCE_KERNEL_3 1

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "AT/Sequence/Kernel.h"
#include "CT/Stack/Kernel_1a_C.h"

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

concrete_template <
	concrete_instance class Item,
	concrete_instance class Stack_Of_Item =
            Stack_Kernel_1a_C <Item>,
	concrete_instance class Rep =
            Representation <
		    Stack_Of_Item,
		    Stack_Of_Item
		>
    >
class Sequence_Kernel_3 :
    implements
	abstract_instance Sequence_Kernel <Item>,
    encapsulates
	concrete_instance Rep
{
private:

    rep_field_name (Rep, 0, Stack_Of_Item, before);
    rep_field_name (Rep, 1, Stack_Of_Item, after);

    /*!
	correspondence
	    self = reverse (self.before) * self.after
    !*/

    local_procedure_body Set_Length_Of_Before (
	    alters Stack_Of_Item& before_stack,
	    alters Stack_Of_Item& after_stack,
	    preserves Integer pos
	)
    /*!
	requires
	    0 <= pos <= |before_stack| + |after_stack|
	ensures
	    reverse (before_stack) * after_stack =
		reverse (#before_stack) * #after_stack  and
	    |before_stack| = pos
    !*/
    {
	//-------- for students to fill in --------
    }

public:

    standard_concrete_operations (Sequence_Kernel_3);

    procedure_body Add (
	    preserves Integer pos,
	    consumes Item& x
	)
    {
	//-------- for students to fill in --------
    }  

    procedure_body Remove (
	    preserves Integer pos,
	    produces Item& x
	)
    {
	//-------- for students to fill in --------
    }

    function_body Item& operator [] (
	    preserves Integer pos
	)
    {
	Set_Length_Of_Before (self[before], self[after], pos);
	return self[after][current];
    }

    function_body Integer Length ()
    {
	//-------- for students to fill in --------
    }

};

#endif // CT_SEQUENCE_KERNEL_3
