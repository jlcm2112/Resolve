//  /*----------------------------------------------------------------*\
//  |   Concrete Template : Partial_Map_Kernel_6_C
//  \*----------------------------------------------------------------*/

#ifndef CT_PARTIAL_MAP_KERNEL_6_C
#define CT_PARTIAL_MAP_KERNEL_6_C 1

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "CT/Partial_Map/Kernel_6.h"
#include "CT/Partial_Map/Kernel_C.h"
#include "CT/Partial_Map/Kernel_1_C.h"
#include "CT/Array/Kernel_1_C.h"    
/*!
    #include "AT/General/Is_Equal_To.h"
    #include "AT/General/Hash.h"
!*/

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
	concrete_instance utility_class D_Item_Hash,
	/*!
	    implements
		abstract_instance General_Hash <D_Item>
	!*/	    
	Integer_constant hash_table_size,
	/*!
	    satisfies restriction
	        hash_table_size > 0
	!*/
        concrete_instance class D_R_Partial_Map =
            Partial_Map_Kernel_1_C <
                    D_Item,
                    R_Item
                >,
        concrete_instance class Array_Of_Partial_Map =
            Array_Kernel_1_C <
		    D_R_Partial_Map
		>,
	concrete_instance class Rep =
            Representation <
		    Array_Of_Partial_Map,
		    Integer
		>
    >
class Partial_Map_Kernel_6_C :
    specializes
	Partial_Map_Kernel_C <
		D_Item,
		R_Item,
		Partial_Map_Kernel_6 <
                        D_Item,
                        R_Item,
			D_Item_Hash,
			hash_table_size,
			D_R_Partial_Map,
			Array_Of_Partial_Map,
			Rep
                    >
	    >
{};

//----------------------------------------------------------------------

#endif // CT_PARTIAL_MAP_KERNEL_6_C
