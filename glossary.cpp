#include "RESOLVE_Foundation.h"
#include "CT/Sorting_Machine/Kernel_1_C.h"
#include "CI/Text/Are_In_Order_1.h" 
#include "CT/Partial_Map/Kernel_1_C.h"

concrete_instance 
class Sorting_Machine_Of_Text : 
    instantiates 
        Sorting_Machine_Kernel_1_C <Text, Text_Are_In_Order_1> 
{}; 

concrete_instance 
class Partial_Map_Instance : 
    instantiates 
        Partial_Map_Kernel_1_C <Text, Text> 
{}; 

//------------------------








program_body main ()
{
    object Character_IStream input;
    object Character_OStream output;
Output_Header ();


read in terms and definitons
copy term
Put term into sorting machine

Put copy into a partial map
Put definition into partial map

sort the machines / change to extraction phase


Output_Terms (terms, output);
Output_Definitions (definitions, output);

