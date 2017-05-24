//  /*----------------------------------------------------------------*\
//  |   Concrete Template : Partial_Map_Kernel_7_C
//  \*----------------------------------------------------------------*/

#ifndef CT_PARTIAL_MAP_KERNEL_7_C
#define CT_PARTIAL_MAP_KERNEL_7_C 1

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "CT/Partial_Map/Kernel_7.h"
#include "CT/Partial_Map/Kernel_C.h"
/*!
    #include "AT/General/Is_Equal_To.h"
    #include "AT/General/Are_In_Order.h"
!*/
#include "CT/Binary_Tree/Kernel_1a_C.h"

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

concrete_template <
        concrete_instance class D_Item,
        /*!
            implements
                abstract_instance General_Is_Equal_To <D_Item, D_Item>
        !*/
        concrete_instance class R_Item,
        concrete_instance utility_class D_Item_Are_In_Order,
        /*!
            implements
                abstract_instance General_Are_In_Order <D_Item>
        !*/
        concrete_instance class D_R_Pair =
	    Record <
		    D_Item, 
		    R_Item
                >,
        concrete_instance class Binary_Tree_Of_D_R_Pair =
            Binary_Tree_Kernel_1a_C <D_R_Pair>,
        concrete_instance class Rep =
            Representation <
		    Integer,
		    D_R_Pair,
		    Binary_Tree_Of_D_R_Pair
		>
    >
class Partial_Map_Kernel_7_C :
    specializes
	Partial_Map_Kernel_C <
		D_Item,
		R_Item,
		Partial_Map_Kernel_7 <
                        D_Item,
                        R_Item,
                        D_Item_Are_In_Order,
			D_R_Pair,
			Binary_Tree_Of_D_R_Pair,
			Rep
                    >
	    >
{};

//----------------------------------------------------------------------

#endif // CT_PARTIAL_MAP_KERNEL_7_C
