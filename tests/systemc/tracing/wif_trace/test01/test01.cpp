/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
  more contributor license agreements.  See the NOTICE file distributed
  with this work for additional information regarding copyright ownership.
  Accellera licenses this file to you under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with the
  License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
  implied.  See the License for the specific language governing
  permissions and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  test01.cpp --

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#define SC_INCLUDE_FX
#include "systemc.h"

SC_MODULE( proc1 )
{

  sc_in<bool> clk;

  bool obj1;
  sc_logic obj2;
  sc_bv<4> obj3;
  sc_lv<4> obj4;
  sc_fixed<16, 8>  obj5;
  sc_ufixed<16, 8> obj6;

  proc1( sc_module_name NAME,
	 sc_signal<bool>& CLK)
  {
    clk(CLK);
    SC_THREAD( entry );
    sensitive << clk;
    obj1 = 0;
    obj2 = 0;
    obj3 = "0000";
    obj4 = "0000";
    obj5 = 0.0;
    obj6 = 0.0;
  }

  void entry();
};

void proc1::entry()
{
  sc_bv<4> bv;
  sc_lv<4> sv;
  int i = 5;
  wait();
  while(true) {
    bv = i;
    sv = i++;
    obj1 = 0;
    obj2 = 1;
    obj3 = "0000";
    obj4 = "1111";
    obj5 = 254.5;
    obj6 = 254.5;
    wait();
    obj1 = 1;
    obj2 = 0;
    obj3 = "1010";
    obj4 = "1011";
    obj5 = 3.303;
    wait();
    obj3 = bv;
    obj4 = sv;
    obj6 = 4.404;
    wait();
  }
}


int sc_main(int ac, char *av[])
{
  sc_trace_file *tf;
  sc_signal<bool> clock;

  proc1 P1("P1", clock);

  tf = sc_create_wif_trace_file("test01");
  tf->set_time_unit( 1, SC_PS );
  // @@@@ ((wif_trace_file *) tf)->sc_set_wif_time_unit(-12);
  sc_trace(tf, P1.obj1, "Bool");
  sc_trace(tf, P1.obj2, "SC_Logic");
  sc_trace(tf, P1.obj3, "SC_BV");
  sc_trace(tf, P1.obj4, "SC_LV");
  sc_trace(tf, P1.obj5, "SC_Fixed");
  sc_trace(tf, P1.obj6, "SC_Ufixed");
  sc_trace(tf, clock, "Clock");

  clock.write(0);
  sc_start(0, SC_NS);
  for (int i = 0; i< 10; i++) {
    clock.write(1);
    sc_start(10, SC_NS);
    clock.write(0);
    sc_start(10, SC_NS);
  }
  sc_close_wif_trace_file( tf );
  return 0;
}
