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

  main.cpp -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

/* Main routine for tri-state simulation */

#include "driver.h"
#include "ts_buf.h"
#include "pullup.h"
#include "display.h"

int sc_main(int ac, char* av[] )
{
  sc_signal_resolved bus;
  sc_signal<bool> control;
  sc_signal<bool> out;

  sc_clock clock("CLK", 10.0, 0.5, 0.0);

  driver D("Driver", clock, bus, control, out);
  ts_buf B("Buffer", out, control, bus);
  pullup P("BusPullup", clock, bus);
  display DISP("BusDisplay", bus);

  sc_start(200);

  return 0;
}

