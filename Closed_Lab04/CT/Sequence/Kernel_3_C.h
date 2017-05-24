//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Sequence_Kernel_3_C
//  \*-------------------------------------------------------------------*/

#ifndef CT_SEQUENCE_KERNEL_3_C
#define CT_SEQUENCE_KERNEL_3_C 1

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "CT/Sequence/Kernel_3.h"
#include "CT/Sequence/Kernel_C.h"

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
class Sequence_Kernel_3_C :
    specializes
	Sequence_Kernel_C <
		Item,
		Sequence_Kernel_3 <
			Item,
			Stack_Of_Item,
			Rep
		    >
	    >
{};

//----------------------------------------------------------------------

#endif // CT_SEQUENCE_KERNEL_3_C
