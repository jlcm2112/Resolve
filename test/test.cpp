#include "RESOLVE_Foundation.h"

program_body main ()
{
   
    object Character_OStream output;
    object Text t, t_copy;

    output.Open_External ("");

    t = "dicks";
    t_copy = t;
    output <<"\nt is: " << t << ", and t_copy is: " << t_copy << "\n";

    output.Close_External ();
}
