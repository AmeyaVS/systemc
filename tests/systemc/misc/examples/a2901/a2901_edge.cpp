/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2014 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.accellera.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  a2901_edge.cpp -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include "a2901_edge.h"


void
a2901_edge::entry()
{
    i86 = I.read().range(8,6);
    i87 = I.read().range(8,7);
    q31 = Q.read().range(3,1);
    q20 = Q.read().range(2,0);
    f31 = F.read().range(3,1);

    switch ((int)i87) {
    case 0:
	RAM[Badd.read()] = RAM[Badd.read()];
	break;
    case 1:
	RAM[Badd.read()] = F.read();
	break;
    case 2:
	RAM[Badd.read()] = (RAM3.read(),f31);
	break;
    case 3:
	RAM[Badd.read()] = (f20, RAM0.read());
	break;
    }
      
#if SUN_HAS_FIXED_THIS_BUG_IN_SC62
    Q.write( (i86 == 0x0) ? F.read() :
	     (i86 == 0x4) ? sc_uint<4>((Q3.read(),q31)) :
	     (i86 == 0x6) ? sc_uint<4>((q20,Q0.read())) :
	     Q.read());
#else
    if( i86 == 0x0 ) {
        Q.write( F.read() );
    } else if( i86 == 0x4 ) {
        Q.write( ( Q3.read(), q31 ) );
    } else if( i86 == 0x6 ) {
        Q.write( ( q20, Q0.read() ) );
    } else {
        Q.write( Q.read() );
    }
#endif
}
