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

  8.2.7.cpp -- Test code snipped from IEEE Std 1666-2023 LRM 

  Original Author: Andy Goodrich, Accellera Systems Initiative

 *****************************************************************************/

#include <systemc.h>

SC_MODULE(M)
{
    SC_CTOR(M) {
        SC_THREAD(T);
    }
    void T() {
        try {
	    // . . .
	    SC_REPORT_ERROR("msg_type", "msg");
#ifndef IEEE_1666_STRICT
	} catch(const sc_core::sc_report & c) {
#else
	} catch(sc_core::sc_report c) {
#endif // IEEE_1666_STRICT
	    std::cout << "Caught " << c.what() << std::endl;
	}
    }
};

int sc_main( int argc, char* argv[] ) { 

    M m("m");

    sc_start();

    std::cout << std::endl << "program completed" << std::endl;
    return 0;
}
