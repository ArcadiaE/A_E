/////////////////////////////////////////////////////////////////////
// Design unit: c4
//            :
// File name  : c4.sv
//            :
// Description: Top level code for C4 Lab exercise
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


module c4 (output logic  s, t, n, SDO, input logic n_clk, rst, a, c, mode, SDI); //add m, SDI, SDO

logic s_plus, t_plus, s_bar, t_bar, n_bar, clk;

assign clk = ~n_clk;

next_state n0 (.*);
scan_dff d0 (.q(s), .qbar(s_bar), .clk(clk), .rst(rst), .d(s_plus), .mode(m), .scan_in(t));
scan_dff d1 (.q(t), .qbar(t_bar), .clk(clk), .rst(rst), .d(t_plus), .mode(m), .scan_in(SDI));
output_reg o1 (.*);//calculate n

always_comb begin
    SDO = s;
  end
 //add the scan
endmodule


