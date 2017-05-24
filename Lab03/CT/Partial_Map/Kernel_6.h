//  /*----------------------------------------------------------------*\
//  |   Concrete Template : Partial_Map_Kernel_6
//  \*----------------------------------------------------------------*/

#ifndef CT_PARTIAL_MAP_KERNEL_6
#define CT_PARTIAL_MAP_KERNEL_6 1

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "AT/Partial_Map/Kernel.h"
/*!
    #include "AT/General/Is_Equal_To.h"
    #include "AT/General/Hash.h"
!*/
#include "CT/Partial_Map/Kernel_1.h"
#include "CT/Array/Kernel_1.h"    

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
            Partial_Map_Kernel_1 <
                    D_Item,
                    R_Item
                >,
        concrete_instance class Array_Of_Partial_Map =
            Array_Kernel_1 <
		    D_R_Partial_Map
		>,
	concrete_instance class Rep =
            Representation <
		    Array_Of_Partial_Map,
		    Integer
		>
    >
class Partial_Map_Kernel_6 :
    implements
	abstract_instance Partial_Map_Kernel <D_Item, R_Item>,
    encapsulates
	concrete_instance Rep
{
private:
    
    rep_field_name (Rep, 0, Array_Of_Partial_Map, hash_table);
    rep_field_name (Rep, 1, Integer, total_pairs);

    /*!
	convention
	    self.hash_table.lb = 0  and
	    self.hash_table.ub = hash_table_size - 1  and
	    for all i: integer, d: D_Item, p: PARTIAL_FUNCTION,
	            where ((i,p) is in self.hash_table.table  and
		            IS_DEFINED_IN (p, d))
		(HASH_FUNCTION (d) mod hash_table_size = i)  and
	    self.total_pairs =
		sum i: integer, p: PARTIAL_FUNCTION
			where ((i,p) is in self.hash_table.table)
		    (|p|)
		    
	correspondence
	    self =
		union i: integer, p: PARTIAL_FUNCTION
			where ((i,p) is in self.hash_table.table)
		    (p)
    !*/

    local_procedure_body Initialize ()
    {
      //given code, do not edit
       self[hash_table].Set_Bounds (0, hash_table_size-1);
    }

public:

    standard_concrete_operations (Partial_Map_Kernel_6);

    procedure_body Define (
	    consumes D_Item& d,
            consumes R_Item& r
	)
    {
      object catalyst Integer j = D_Item_Hash::Hash(d) mod hash_table_size;
      self[hash_table][j].Define (d, r);
      self[total_pairs]++;

    }

    procedure_body Undefine (
            preserves D_Item& d,
	    produces D_Item& d_copy,
            produces R_Item& r
	)
    {
      object catalyst Integer j = D_Item_Hash::Hash(d) mod hash_table_size;
      self[hash_table][j].Undefine (d, d_copy, r);
      self[total_pairs]--;
      
    }

    procedure_body Undefine_Any (
	    produces D_Item& d,
	    produces R_Item& r
	)
    {
      object catalyst Integer i;
      while (self[hash_table][i].Size () == 0)
	{
	  i++;
	}
      self[hash_table][i].Undefine_Any (d, r);
      self[total_pairs]--;
    }

    function_body Boolean Is_Defined (
	    preserves D_Item& d
	)
    {
      object catalyst Integer j = D_Item_Hash::Hash(d) mod hash_table_size;
      return self[hash_table][j].Is_Defined (d);
    }

    function_body R_Item& operator [] (
	    preserves D_Item& d
	)
    {
      object catalyst Integer j = D_Item_Hash::Hash(d) mod hash_table_size;
      return self[hash_table][j][d];

    }
    function_body Integer Size ()
    { 
      return self[total_pairs]; 
    }

};

//----------------------------------------------------------------------

#endif // CT_PARTIAL_MAP_KERNEL_6ls

