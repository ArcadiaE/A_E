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

logic s, t;
logic n_clk, rst, a;

c4 c4 (.*);

initial 
  begin
  n_clk = 0;
  #20;
  forever #10 n_clk = ~n_clk;
  end
  
initial

/*
  begin
  rst = 1;
  a = 0;
  #10 rst = 0;
  #10 rst = 1;
  #40 a = 1;
  #60 a = 0;
  #20 a = 1;
  #20 a = 0;
  #40 a = 1;
  #20 a = 0;
  #20 a = 1;
  #20 $finish;
  end
*/

begin
        a = 0;
        rst = 1; 
        #10 rst = 0
		#10 rst = 1;  //reset to AA

        
        #10 a = 1;	// AA to AB
        #10 a = 0;  // test back to AA

        #10 a = 1;	// AA to AB again
        #10 a = 0;  // AB to AC

        // AC back to AA
        #10 a = 0; 	// a not important here

        
        #10 a = 1;	// AA to AB 3rd
        
        #10 a = 1;// AC to AD

        #10 a = 1;  // back to AD
        #10 a = 0;  // back to AA finish test

        #10 $finish;
    end
	
endmodule
  
