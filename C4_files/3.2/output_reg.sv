/////////////////////////////////////////////////////////////////////
// Design unit: output_reg
//            :
// File name  : output_reg.sv
//            :
// Description: Output Register code for C4 Lab exercise
//            :
// Limitations: None
//            : 
// System     : SystemVerilog IEEE 1800-2005
//            :
// Author     : Mark Zwolinski
//            : School of Electronics and Computer Science
//            : University of Southampton
//            : Southampton SO17 1BJ, UK
//            : mz@ecs.soton.ac.uk
//
// Revision   : Version 1.0 28/08/17
//            : Version 2.0 04/11/20 
//
/////////////////////////////////////////////////////////////////////

module output_reg (output logic n, input logic clk, s, t, c);

always_ff @(posedge clk)
  if (s)
    n <= t & c;
    
endmodule