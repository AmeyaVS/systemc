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
 
  main.cpp -- Main function for the dashboard controller for a
           car. This controller contains a speedometer, two odometers (total
           and partial distance), the driver of the car, clocks, and the
           pulse generator. The pulses are generated by the sensors placed
           around one of the wheel shafts. The rate of pulse generation is
           determined by the speed of the car. The driver can start the car,
           set its speed, reset the partial distance odometer, and stop the
           car (which means he will stop the simulation). One of the clocks
           is slow and the other is fast. The fast clock represents the real
           time. The slow clock is used to control the actions of the
           driver. The signals in this program are traced.

           purpose (in terms of changes to dash2's purpose) -- multiple
           modules inside single modules.
 
  Original Author: Ali Dasdan, Synopsys, Inc.
 
 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include "systemc.h"
#include "const.h"
#include "driver.h"
#include "pulse.h"
#include "speed.h"
#include "dist.h"

int
sc_main(int argc, char *argv[])
{
  // Pulses for the speedometer and odometers, generated by the pulse
  // generator.
  sc_signal<bool> speed_pulses("speed_pulses");
  sc_signal<bool> dist_pulses("dist_pulses");
  // Signals for the driver's actions.
  sc_signal<bool> reset("reset");
  sc_signal<int>  speed("speed");
  sc_signal<bool> start("start");

  // Signals observed by the driver.
  sc_signal<double> disp_speed("disp_speed");
  sc_signal<double> disp_angle("disp_angle");
  sc_signal<double> disp_total_dist("disp_total_dist");
  sc_signal<double> disp_partial_dist("disp_partial_dist");

  // Clocks.
  sc_clock clk0("slow_clk", SLOW_CLOCK_PERIOD0, 0.5, 0.0, true);
  sc_clock clk1("fast_clk", FAST_CLOCK_PERIOD1, 0.5, 0.0, false);

  driver_mod driver("driver");
  driver << clk0 << disp_speed << disp_angle 
         << disp_total_dist << disp_partial_dist 
         << reset << speed << start;

  gen_pulse_mod gen_pulse("gen_pulse");
  gen_pulse << clk1 << start << speed 
            << speed_pulses << dist_pulses;

  speed_mod speedometer("speedometer");
  speedometer << clk1 << start << speed_pulses 
              << disp_speed << disp_angle;

  dist_mod odometers("odometers");
  odometers << dist_pulses << reset << start 
            << disp_total_dist << disp_partial_dist;

  // Initialize signals:
  start = false;

  // Tracing:
  // Trace file creation.
  sc_trace_file *tf = sc_create_vcd_trace_file("dash");
  // External signals.
  sc_trace(tf, clk0.signal(), "slow_clk");
  sc_trace(tf, clk1.signal(), "fast_clk");
  sc_trace(tf, speed_pulses, "speed_pulses");
  sc_trace(tf, dist_pulses, "dist_pulses");
  sc_trace(tf, reset, "reset");
  sc_trace(tf, start, "start");
  sc_trace(tf, speed, "speed");
  sc_trace(tf, disp_speed, "disp_speed");
  sc_trace(tf, disp_angle, "disp_angle");
  sc_trace(tf, disp_total_dist, "disp_total_dist");
  sc_trace(tf, disp_partial_dist, "disp_partial_dist");
  // Internal signals.
  sc_trace(tf, speedometer.elapsed_time, "elapsed_time");
  sc_trace(tf, speedometer.read_mod->raw_speed, "raw_speed");
  sc_trace(tf, speedometer.filtered_speed, "filtered_speed");
  sc_trace(tf, odometers.ok_for_incr, "ok_for_incr");
  sc_trace(tf, odometers.total_dist, "total_dist");
  sc_trace(tf, odometers.partial_dist, "partial_dist");

  disp_speed = 0.0;
  disp_angle = 0.0;
  disp_total_dist = 0.0;
  disp_partial_dist = 0.0;

  sc_start(-1);

  return 0;
}

// End of file
