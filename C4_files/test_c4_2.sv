/////////////////////////////////////////////////////////////////////
// Design unit: test_c4
//            :
// File name  : test_c4.sv
//            :
// Description: Testbench for for C4 Lab exercise
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


module test_c4;

timeunit 1ns;
timeprecision 100ps;

logic s, t, n;//add n
logic n_clk, rst, a, c;//add c

c4 c4 (.*);

initial 
  begin
  n_clk = 0;
  #20;
  forever #10 n_clk = ~n_clk;
  end
  
initial

  begin
  c=0;//add c
  rst = 1;
  a = 0;
  #20 rst = 0;
  #20 rst = 1;
  #20 a = 0;c=1; //00->00
  #20 a = 1;c=1; //00->01
  #20 a = 0;c=1; //01->11
  #20 a = 0;c=1; //11->00
  #20 a = 1;c=1; //00->01
  #20 a = 0;c=1; //01->11
  #20 a = 1;c=1; //11->00
  #20 a = 1;c=1; //00->01
  #20 a = 1;c=1; //01->10
  #20 a = 1;c=1; //10->10
  #20 a = 0;c=1; //10->00
  
  
  
  #20 $finish;
  end

endmodule
