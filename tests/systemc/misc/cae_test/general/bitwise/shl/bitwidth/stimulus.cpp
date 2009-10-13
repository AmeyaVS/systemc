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

  stimulus.cpp -- 

  Original Author: Rocco Jonack, Synopsys, Inc., 1999-07-30

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/


#include "stimulus.h"

void stimulus::entry() {
  sc_signed       send_value1(4);
  sc_unsigned     send_value2(4);
  sc_signed       send_value3(6);
  sc_unsigned     send_value4(6);
  sc_signed       send_value5(8);
  sc_unsigned     send_value6(8);


  // sending some reset values
  reset.write(true);
  out_valid.write(false);
  send_value1 = 1;
  send_value2 = 1;
  send_value3 = 1;
  send_value4 = 1;
  send_value5 = 1;
  send_value6 = 1;
  out_stimulus1.write(1);
  out_stimulus2.write(1);
  out_stimulus3.write(1);
  out_stimulus4.write(1);
  out_stimulus5.write(1);
  out_stimulus6.write(1);
  wait(3);
  reset.write(false);
  // sending normal mode values
  while(true){
    wait(20);
    out_stimulus1.write( send_value1 );
    out_stimulus2.write( send_value2 );
    out_stimulus3.write( send_value3 );
    out_stimulus4.write( send_value4 );
    out_stimulus5.write( send_value5 );
    out_stimulus6.write( send_value6 );
    out_valid.write( true );
    cout << "Stimuli : " << send_value1 << " "
	 << send_value2 << " "
	 << send_value3 << " "
	 << send_value4 << " "
	 << send_value5 << " " 
	 << send_value6 << " " << " at "
         << sc_simulation_time() << endl;
    send_value1 = send_value1+2;
    send_value2 = send_value2+2;
    send_value3 = send_value3+2;
    send_value4 = send_value4+2;
    send_value5 = send_value5+2;
    send_value6 = send_value6+2;
    wait();
    out_valid.write( false );
  }
}

// EOF
