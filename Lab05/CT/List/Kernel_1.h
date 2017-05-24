//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : List_Kernel_1
//  \*-------------------------------------------------------------------*/

#ifndef CT_LIST_KERNEL_1
#define CT_LIST_KERNEL_1 1
 
///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/List/Kernel.h"

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
		    Pointer_C <Node>,
		    Pointer_C <Node>,
		    Integer,
		    Integer
		>    
    >
class List_Kernel_1 :
    implements
	abstract_instance List_Kernel <Item>,
    encapsulates
	concrete_instance Rep
{
private:

    rep_field_name (Rep, 0, Pointer_C <Node>, pre_start);
    rep_field_name (Rep, 1, Pointer_C <Node>, last_left);
    rep_field_name (Rep, 2, Pointer_C <Node>, finish);
    rep_field_name (Rep, 3, Integer, left_length);
    rep_field_name (Rep, 4, Integer, right_length);

    field_name (Node, 0, Item, data);
    field_name (Node, 1, Pointer_C <Node>, next);

    /*!
	convention
	    self.pre_start /= NULL  and
	    self.last_left /= NULL  and
	    self.finish /= NULL  and
	    self.left_length >= 0  and
	    self.right_length >= 0  and
	    [self.pre_start points to the first node of a singly
	     linked list containing (self.left_length +
	     self.right_length + 1) Node nodes]  and 
	    [self.last_left points to the (self.left_length + 1)-th
	     node in the singly-linked list of nodes]  and
	    [self.finish points to the last node in the
	     singly-linked list of nodes]
	     
	correspondence
	    (if self.left_length = 0
		 then self.left = empty_string
	     else if self.left_length = 1
		 then self.left = <self.last_left.data>
	     else if self.left_length = 2
		 then self.left =
		     <self.pre_start.next.data> *
		     <self.last_left.data>
	     else [self.left = 
		 <self.pre_start.next.data> *
		 <self.pre_start.next.next.data> *
		 ... *
		 <self.last_left.data>])  and
	    (if self.right_length = 0
		 then self.right = empty_string
	     else if self.right_length = 1
		 then self.right = <self.last_left.next.data>
	     else if self.right_length = 2
		 then self.right =
		     <self.last_left.next.data> *
		     <self.finish.data>
	     else [self.right = 
		 <self.last_left.next.data> *
		 <self.last_left.next.next.data> *
		 ... *
		 <self.finish.data>])
    !*/

    local_procedure_body Initialize ()
    {
	New (self[pre_start]);
	self[last_left] = self[pre_start];
	self[finish] = self[pre_start];
    }

    local_procedure_body Finalize ()
    {
	object Pointer_C <Node> temp;

	temp = self[pre_start];
	while (temp != self[finish])
	{
	    self[pre_start] = (*self[pre_start])[next];
	    Delete (temp);
	    temp = self[pre_start];
	}
	Delete (temp);
    }

public:

    standard_concrete_operations (List_Kernel_1);

    procedure_body Add_Right (
	    consumes Item& x
	)
    {
	object Pointer_C <Node> temp;

	New (temp);
	x &= (*temp)[data];
	(*temp)[next] = (*self[last_left])[next];
	(*self[last_left])[next] = temp;

	if (self[right_length] == 0)
	{
	    self[finish] = temp;
	}

	self[right_length]++;
    }

    procedure_body Remove_Right (
	    produces Item& x
	)
    {
	object Pointer_C <Node> temp;

	temp = (*self[last_left])[next];
	(*self[last_left])[next] = (*temp)[next];
	x &= (*temp)[data];
	Delete (temp);

	if (self[right_length] == 1)
	{
	    self[finish] = self[last_left];
	}

	self[right_length]--;
    }

    function_body Item& operator [] (
	    preserves Accessor_Position& current
	)
    {
	return (*(*self[last_left])[next])[data];
    }

    procedure_body Advance ()
    {
	self[last_left] = (*self[last_left])[next];

	self[left_length]++;
	self[right_length]--;
    }

    procedure_body Move_To_Start ()
    {
	self[last_left] = self[pre_start];

	self[right_length] += self[left_length];
	self[left_length] = 0;
    }
    
    procedure_body Move_To_Finish ()
    {
	self[last_left] = self[finish];

	self[left_length] += self[right_length];
	self[right_length] = 0;
    }
    
    function_body Integer Left_Length ()
    {
	return self[left_length];
    }
    
    function_body Integer Right_Length ()
    {
	return self[right_length];
    }

};

#endif // CT_LIST_KERNEL_1
