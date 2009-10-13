/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2002 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.3 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  switch6.cpp -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include "systemc.h"
unsigned short
select( unsigned a, unsigned b, unsigned c )
{
    sc_unsigned x(7);
    sc_unsigned y(9);

    switch ((c >> 2) & 3) {
    case 0:
        x = a + b;
        if (a > 23349212) {
            x = x + 1;
            break;
        } else {
            x = x - 1;
        }
        return x.to_uint();
    case 1:
        x = a - b;
        break;
    case 2:
        x = (a >> 16) + (b << 16);
        return x.to_uint();
    case 3:
        x = (a << 16) - (b >> 16);
        if (b < 234328112) {
            x = x - 1;
            break;
        } else {
            x = x + 1;
            return x.to_uint();
        }
        break;
    }

    y = 2 * x;
    return y.to_uint();
}

int
sc_main( int, char** argv )   
{
    return 0;
}
