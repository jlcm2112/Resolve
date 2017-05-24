//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Queue_Of_Text_Sort_1
//  \*-------------------------------------------------------------------*/

#ifndef CT_QUEUE_OF_TEXT_SORT_1
#define CT_QUEUE_OF_TEXT_SORT_1 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AI/Queue_Of_Text/Sort.h"
/*!
    #include "AT/Queue/Kernel.h"
!*/
   
///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

concrete_template <
	concrete_instance class Queue_Of_Text_Base
	/*!
	    implements
		abstract_instance Queue_Kernel <Text>
	!*/
    >
class Queue_Of_Text_Sort_1 :
    implements
	abstract_instance Queue_Of_Text_Sort,
    extends
	concrete_instance Queue_Of_Text_Base
{
private:

    local_procedure_body Remove_Min (
	    alters Queue_Of_Text_Sort_1& q,
	    produces Text& min
	)
    /*!
	requires
	    q /= empty_string
	ensures
	    (q * <min>) is permutation of #q  and
	    for all t: string of character
		    where (t is in elements (q))
		(min <= t)
    !*/
    {
	assert (q.Length () > 0,
		"q /= empty_string");

	//-------- for students to fill in --------
    }

public:
    
    procedure_body Sort ()
    {
	//-------- for students to fill in --------
    }

};

#endif // CT_QUEUE_OF_TEXT_SORT_1
