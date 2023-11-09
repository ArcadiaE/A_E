/////////////////////////////////////////////////////////////////////
// Design unit: next_state
//            :
// File name  : next_state.sv
//            :
// Description: Next state logic code for C4 Lab exercise
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
//            : Version 2.0 04/11/20 Use `define and `ifdef
//
/////////////////////////////////////////////////////////////////////


// To insert a fault, change ONE of the following lines to `define`

`undef FSA0
`undef FSA1

module next_state (output logic s_plus, t_plus, input logic s, s_bar, t, t_bar, a);

logic a_bar, e, f, g, h;

nand g0 (s_plus, e, f);
nand g1 (e, s_bar, t);

`ifdef FSA0
assign f = 1'b0;
`elsif FSA1
assign f = 1'b1;
`else
nand g2 (f, s, a, t_bar);
`endif

nand g3 (t_plus, g, h);
nand g4 (g, a, s_bar, t_bar);
nand g5 (h, a_bar, s_bar, t);
not g6 (a_bar, a);

endmodule