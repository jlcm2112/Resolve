//  /*-------------------------------------------------------------------*\
//  |   Abstract Instance : Queue_Of_Text_Sort
//  \*-------------------------------------------------------------------*/

#ifndef AI_QUEUE_OF_TEXT_SORT
#define AI_QUEUE_OF_TEXT_SORT 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Queue/Kernel.h"

///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

abstract_instance
class Queue_Of_Text_Sort :
    extends
	abstract_instance Queue_Kernel <Text>
{
public:
    
    /*!
        math operation IS_ORDERED (
		s: string of string of character
	    ): boolean is
	    for all u, v: string of character
		    where (<u> * <v> is substring of s)
		(u <= v)
    !*/

    procedure Sort () is_abstract;
    /*!
	ensures
	    self is permutation of #self  and
	    IS_ORDERED (self)
    !*/

};

#endif // AI_QUEUE_OF_TEXT_SORT
