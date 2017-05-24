//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Stack_Kernel_1
//  \*-------------------------------------------------------------------*/

#ifndef CT_STACK_KERNEL_1
#define CT_STACK_KERNEL_1 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Stack/Kernel.h"

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

concrete_template <
	concrete_instance class Item,
	concrete_instance class Node,
	/*!
	    implements
		abstract_instance Record <
			Item,
			Pointer_C <Node>
		    >
	!*/
	concrete_instance class Rep =
            Representation <
		    Pointer_C <Node>,
		    Integer
		>
    >
class Stack_Kernel_1 :
    implements
	abstract_instance Stack_Kernel <Item>,
    encapsulates
	concrete_instance Rep
{
private:

    rep_field_name (Rep, 0, Pointer_C <Node>, top);
    rep_field_name (Rep, 1, Integer, length);

    field_name (Node, 0, Item, data);
    field_name (Node, 1, Pointer_C <Node>, next);
    
    /*!
	convention
	    self.length >= 0  and
	    if self.length = 0
		then (self.top = NULL)
		else ([self.top points to the first node of a
		      singly linked list containing self.length
		      Node nodes, and where the next field of
		      the last node is NULL])
		      
	correspondence
	    if self.length = 0
		then self = empty_string
		else self =
		   [data fields of the first self.length nodes
		    in the singly linked list pointed to by
		    self.top, concatenated together in the
		    order in which they are linked together]
    !*/

    local_procedure_body Initialize ()
    {
	self[top] = NULL;
    }

    local_procedure_body Finalize ()
    {
      while (self[length] > 0 )
	{
	   object Node temp;   
	   temp[next] = self[top];
	   self[top] = (*self[top])[next];
	   Delete(temp[next]);
	   self[length]--;
	}
    }

public:

    standard_concrete_operations (Stack_Kernel_1);

    procedure_body Push (
	    consumes Item& x
	)
    {
      object Pointer_C <Node> temp;
      New(temp);
      (*temp)[data] &= x;
      (*temp)[next] = self[top];
      self[top] = temp;
      self[length]++;

    }

    procedure_body Pop (
	    produces Item& x
	)
    {
      object Node temp;
      x &= (*self[top])[data];
      temp[next] = self[top];
      self[top] = (*self[top])[next];
      Delete(temp[next]);
      self[length]--;
      
    }

    function_body Item& operator [] (
	    preserves Accessor_Position& current
	)
    {
	return (*self[top])[data];
    }

    function_body Integer Length ()
    {
      return self[length];
    }

};

#endif // CT_STACK_KERNEL_1
