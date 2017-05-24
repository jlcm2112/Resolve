//  /*----------------------------------------------------------------*\
//  |   Concrete Template : Partial_Map_Kernel_7
//  \*----------------------------------------------------------------*/

#ifndef CT_PARTIAL_MAP_KERNEL_7
#define CT_PARTIAL_MAP_KERNEL_7 1

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "AT/Partial_Map/Kernel.h"
/*!
    #include "AT/General/Is_Equal_To.h"
    #include "AT/General/Are_In_Order.h"
!*/
#include "CT/Binary_Tree/Kernel_1a.h"

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
            Binary_Tree_Kernel_1a <D_R_Pair>,
        concrete_instance class Rep =
            Representation <
		    Integer,
		    D_R_Pair,
		    Binary_Tree_Of_D_R_Pair
		>
    >
class Partial_Map_Kernel_7 :
    implements
        abstract_instance Partial_Map_Kernel <
                D_Item, 
                R_Item
            >,
    encapsulates
        concrete_instance Rep
{

private:

    rep_field_name (Rep, 0, Integer, number_of_pairs);
    rep_field_name (Rep, 1, D_R_Pair, cache);
    rep_field_name (Rep, 2, Binary_Tree_Of_D_R_Pair, tree_of_pairs);

    field_name (D_R_Pair, 0, D_Item, d_item);
    field_name (D_R_Pair, 1, R_Item, r_item);
    

    local_procedure_body Add_Pair_To_Tree (
            alters Binary_Tree_Of_D_R_Pair& t,
            consumes D_R_Pair& pair
        )
    /*!
	 requires
	     TREE_CONV (t)  and
	     pair.d_item is not in D_ELEMENTS (t)
	 ensures
	     TREE_CONV (t)  and
	     ELEMENTS (t) = ELEMENTS (#t) union {pair}
	 decreases
	     SIZE (t)
    !*/
    {
	if (t.Size () == 0)
	{
	    object catalyst Binary_Tree_Of_D_R_Pair empty_left, empty_right;

	    t.Compose (pair, empty_left, empty_right);
	}
	else
	{
	    object catalyst D_R_Pair root;
	    object catalyst Binary_Tree_Of_D_R_Pair left, right;

	    t.Decompose (root, left, right);

	    if (D_Item_Are_In_Order::Are_In_Order (root[d_item], pair[d_item]))
	    {
		Add_Pair_To_Tree (right, pair);
	    }
	    else
	    {
		Add_Pair_To_Tree (left, pair);
	    }

	    t.Compose (root, left, right);
	}    
    }

local_procedure_body Remove_Pair_From_Tree (
            alters Binary_Tree_Of_D_R_Pair& t,
            preserves D_Item& d,
            produces D_R_Pair& pair
        )
    /*!
	 requires
	     TREE_CONV (t)  and
	     d is in D_ELEMENTS (t)
	 ensures
	     TREE_CONV (t)  and
	     pair is in ELEMENTS (#t)  and
	     ELEMENTS (t) = ELEMENTS (#t) - {pair}  and
	     pair.d_item = d
	 decreases
	     SIZE (t)
    !*/
    {
      	pair.Clear();
	object catalyst D_R_Pair root;
	object catalyst Binary_Tree_Of_D_R_Pair left, right;

	 t.Decompose (root, left, right);
	    
	if (d.Is_Equal_To(root[d_item]))
	 {
	     root &= pair;
	     if (right.Size() > 0)
	       {
		 Remove_Smallest_Pair_From_Tree(right, root);	
		 t.Compose (root, left, right);
	       }
	     else 
	       {
		 t &= left;		 
	       }
	 }
	 else if (D_Item_Are_In_Order::Are_In_Order (root[d_item], d))
	 {
	   Remove_Pair_From_Tree (right, d, pair);
	   t.Compose (root, left, right);
	 }	    
        else 
	 {
	   Remove_Pair_From_Tree (left, d, pair);
	   t.Compose (root, left, right);
	 }
	

    }


    local_procedure_body Remove_Smallest_Pair_From_Tree (
            alters Binary_Tree_Of_D_R_Pair& t,
            produces D_R_Pair& small_pair
        )
    /*!
	 requires
	     TREE_CONV (t)  and
	     t /= empty_tree
	 ensures
	     TREE_CONV (t)  and
	     small_pair is in ELEMENTS (#t)  and
	     ELEMENTS (t) = ELEMENTS (#t) - {small_pair}  and
	     for all d: D_Item
	         where (d is in D_ELEMENTS (t))
		     (ARE_IN_ORDER (small_pair.d_item, d))
	 decreases
	     SIZE (t)
    !*/
    {
      	small_pair.Clear();
	object catalyst D_R_Pair root;
	object catalyst Binary_Tree_Of_D_R_Pair left, right;

        t.Decompose (root, left, right);
	if (left.Size () == 0) // then this is the smallest pair
	{
	  root &= small_pair;
	  if (right.Size () > 0) //smallest part of right tree should be new root, if it exists
	    {
	      Remove_Smallest_Pair_From_Tree(right, root);
	    }
	}
	else
	{
	  Remove_Smallest_Pair_From_Tree (left, small_pair); // if left size was not 0, we need to descend lower to get the smallest.
        }
	t.Compose (root, left, right);
    }

    local_function_body Boolean Is_In_Tree (
            preserves Binary_Tree_Of_D_R_Pair& t,
            preserves D_Item& d
        )
    /*!
	 requires
	     TREE_CONV (t)
	 ensures
	     Is_In_Tree = (d is in D_ELEMENTS (t))
	 decreases
	     SIZE (t)
    !*/
    {
	object catalyst D_R_Pair root;
	object catalyst Binary_Tree_Of_D_R_Pair left, right;
	object catalyst Boolean result;

	if (t.Size() == 0) //base case 1
	  {
	    result = false;
	  }
	else
	  {
	    t.Decompose (root, left, right);
	    
	    if (d.Is_Equal_To(root[d_item])) //base case 2
	      {
		result = true; 
	      }
	    else if (D_Item_Are_In_Order::Are_In_Order (root[d_item], d)) 
	      {
		result = Is_In_Tree (right, d); // descend into the right subtree
	      } 
	    else if (D_Item_Are_In_Order::Are_In_Order (d, root[d_item]))
	      {
		result = Is_In_Tree (left, d); //descend into the left subtree
	      }

	    t.Compose (root, left, right);
	  }

	    return result;
    }


public:

    standard_concrete_operations (Partial_Map_Kernel_7);
  procedure_body Define (

            consumes D_Item& d,
            consumes R_Item& r
        )
    {
	if (self[number_of_pairs] == 0)
	{
	    // Put (#d,#r) into cache, which is currently unoccupied

	    self[cache][d_item] &= d;
	    self[cache][r_item] &= r;

	    // Consume d and r

	    d.Clear ();
	    r.Clear ();
	}
	else
	{
	    // Put (#d,#r) into tree, since cache is currently occupied

	    object catalyst D_R_Pair pair;

	    pair[d_item] &= d;
	    pair[r_item] &= r;
	    Add_Pair_To_Tree(self[tree_of_pairs], pair);
	}

	// Update number of pairs
	
	self[number_of_pairs]++;
    }

    procedure_body Undefine (
            preserves D_Item& d,
            produces D_Item& d_copy,
            produces R_Item& r
        )
    {
      
      d_copy.Clear();
      r.Clear();
      // if d is not already in the cache
      if (not d.Is_Equal_To (self[cache][d_item]))
	{
	  //store cache pair in tree and put d's pair in cache
	  Add_Pair_To_Tree (self[tree_of_pairs], self[cache]);
          Remove_Pair_From_Tree(self[tree_of_pairs], d, self[cache]);
	}

      d_copy &= self[cache][d_item];
      r &= self[cache][r_item];

      self[number_of_pairs]--;
    }

    procedure_body Undefine_Any (
            produces D_Item& d,
            produces R_Item& r
        )
    { 
      d.Clear();
      r.Clear();
      //if tree is empty, there must be only one item, which is in the cache
     if (self[tree_of_pairs].Size() == 0)
      {
	d &= self[cache][d_item];
	r &= self[cache][r_item];
      }
     else
       { //tree is not empty, so we'll remove one.
	object catalyst D_R_Pair foo;
	Remove_Smallest_Pair_From_Tree(self[tree_of_pairs], foo);
        d &= foo[d_item];
	r &= foo[r_item];
       }
      
	self[number_of_pairs]--;
    }

    function_body Boolean Is_Defined (
            preserves D_Item& d
        )
    {
      // if d is in the tree, or in the cache, it is defined.
      return (Is_In_Tree (self[tree_of_pairs], d)) or d.Is_Equal_To(self[cache][d_item]);
    }

    function_body R_Item& operator [] (
            preserves D_Item& d

        )
    {
      // if it is not already in the cache
      if (not d.Is_Equal_To(self[cache][d_item])) 
	{
	  //store cache pair in tree and put d's pair in cache
	  Add_Pair_To_Tree (self[tree_of_pairs], self[cache]);
	  Remove_Pair_From_Tree (self[tree_of_pairs], d, self[cache]);
	}

	  return self[cache][r_item];
        
    }

    function_body Integer Size ()
    {
	return self[number_of_pairs];
    }

};

#endif // CT_PARTIAL_MAP_KERNEL_7
