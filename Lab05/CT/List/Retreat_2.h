//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : List_Retreat_2
//  \*-------------------------------------------------------------------*/

#ifndef CT_LIST_RETREAT_2
#define CT_LIST_RETREAT_2 1
 
///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/List/Retreat.h"

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
			Pointer_C <Node>,0
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
class List_Retreat_2 :
    implements
	abstract_instance List_Retreat <Item>,
    encapsulates
	concrete_instance Rep
{
private:

    rep_field_name (Rep, 0, Pointer_C <Node>, pre_start);
    rep_field_name (Rep, 1, Pointer_C <Node>, last_left);
    rep_field_name (Rep, 2, Pointer_C <Node>, post_finish);
    rep_field_name (Rep, 3, Integer, left_length);
    rep_field_name (Rep, 4, Integer, right_length);

    field_name (Node, 0, Item, data);
    field_name (Node, 1, Pointer_C <Node>, next);
    field_name (Node, 2, Pointer_C <Node>, previous);

    /*!
	convention
	    self.pre_start /= NULL  and
	    self.last_left /= NULL  and
	    self.post_finish /= NULL  and
	    self.left_length >= 0  and
	    self.right_length >= 0  and
	    [self.pre_start points to the first node of a doubly-
	     linked list containing (self.left_length +
	     self.right_length + 2) Node nodes]  and 
	    [self.last_left points to the (self.left_length + 1)-th
	     node in the doubly-linked list of nodes]  and
	    [self.post_finish points to the last node in the
	     doubly-linked list of nodes]  and
	    [for every node n in the doubly-linked list of nodes,
	     except the one pointed to by self.pre_start,
	     n.previous.next = n]  and
	    [for every node n in the doubly-linked list of nodes,
	     except the one pointed to by self.post_finish,
	     n.next.previous = n]
	     
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
		     <self.post_finish.previous.data>
	     else [self.right = 
		 <self.last_left.next.data> *
		 <self.last_left.next.next.data> *
		 ... *
		 <self.post_finish.previous.data>])
    !*/

    local_procedure_body Initialize ()
    {
		New (self[pre_start]);  // create the pre_start node 
		New (self[post_finish]); // create the post_finish node
		(*self[post_finish])[previous] = self[pre_start]; // link post_finish's "previous" pointer to the pre_start node
		(*self[pre_start])[next] = self[post_finish]; // link pre_start's "next" pointer to the post_finish node
		self[last_left] = self[pre_start]; // last_left should also point to the pre_start node
		(*self[pre_start])[previous] = NULL; // set pre_start's "previous" pointer to NULL
	    (*self[post_finish])[next] = NULL; // set post_finish's "next" to NULL (this probably isn't necessary, but it makes me happy so it isn't wild)

    }


    local_procedure_body Finalize ()
    {
		object Pointer_C <Node> temp;

		temp = self[pre_start];
		while (temp != self[post_finish])
		{
		    self[pre_start] = (*self[pre_start])[next];
		    Delete (temp);
		    temp = self[pre_start];
		}
		Delete (temp);    
	}

public:

    standard_concrete_operations (List_Retreat_2);

    procedure_body Add_Right (
	    consumes Item& x
	)
	
    {
		object Pointer_C <Node> temp;

		New (temp); // temp is a new node to be inserted
		x &= (*temp)[data]; // swap x into temp's data field
		(*temp)[next] = (*self[last_left])[next]; // set the temp node's "next" pointer equal to the last_left node's "next" pointer.
		(*temp)[previous] = self[last_left];  // set the temp node's "previous" pointer equal to the last_left pointer.
		(*(*temp)[next])[previous]  = temp; // set the "previous" pointer on the node after temp towards temp node
		(*self[last_left])[next] = temp; // set the last_left node's "next" pointer towards temp node

		self[right_length]++;
		x.Clear(); // consumes parameter mode
    }    

    procedure_body Remove_Right (
	    produces Item& x
	)
    {
		object Pointer_C <Node> temp;
		x.Clear(); // produces parameter mode

		temp = (*self[last_left])[next]; // set the temp pointer to the node which will be removed
		(*self[last_left])[next] = (*temp)[next]; // set the "next" pointer on the previous node towards the node after temp
		(*(*temp)[next])[previous] = self[last_left]; //set the "previous" pointer on the next node to point to last_left
		x &= (*temp)[data]; // swap out temp's data with x
		Delete (temp);    // delete the node
		
		self[right_length]--;
	}

    function_body Item& operator [] (
	    preserves Accessor_Position& current
	) 
    {
		return (*(*self[last_left])[next])[data]; //the data field of the node on the right of the fence
    }

    procedure_body Advance () // moves the fence forward one node in the list in constant time
    {
		self[last_left] = (*self[last_left])[next];

		self[left_length]++;
		self[right_length]--; 
	}

    procedure_body Retreat () // moves the fence back one node in the list in constant time
    {
		   self[last_left] = (*self[last_left])[previous];		   
		   
		   self[left_length]--;
		   self[right_length]++;	
	}

    procedure_body Move_To_Start () // move the fence to the left of the first non-buffer node in the list
    {
		self[last_left] = self[pre_start];
	
		self[right_length] += self[left_length];
		self[left_length] = 0;    
	}
    
    procedure_body Move_To_Finish () //move the fence to the right of the last non-buffer node in the list
    {
		self[last_left] = (*self[post_finish])[previous];

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

#endif // CT_LIST_RETREAT_2
