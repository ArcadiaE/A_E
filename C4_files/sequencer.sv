/////////////////////////////////////////////////////////////////////
// Design unit: sequencer
//            :
// File name  : sequencer.sv
//            :
// Description: Code for C4 Lab exercise
//            : Outline code for sequencer
//            :
// Limitations: None
//            : 
// System     : SystemVerilog IEEE 1800-2005
//            :
// Author     : @A_E 
//            : School of Electronics and Computer Science
//            : University of Southampton
//            : Southampton SO17 1BJ, UK
//            : yz50u222soton.ac.uk
//      	  :  
// Claim      : 适度编程益脑，过度编程伤身
//            ：合理安排时间，享受健康生活
//
// Revision   : Version 1.0 
/////////////////////////////////////////////////////////////////////


module sequencer (
		input logic n_rst,
		input logic clk,
		input logic A,
		output logic Q1,
		output logic Q2);
		
enum{AA, AB, AC, AD} state;

always_ff @(posedge n_rst, negedge clk)
begin
	//Reset logic
	if (n_rst)
		state <= AA;
	else
	//State machine implement
	begin
		unique case (state)
			AA: begin
				if (A)
					state <= AB;
				else 
					state <= AA;
			end
			
			AB: begin
				if (A)
					state <= AD;
				else
					state <= AC;
			end
			
			AC: begin
				state <= AA;
			end
			
			AD: begin
				if (A);
					state <= AD;
				else
					state <= AA;
			end
		endcase
	end
end

always_comb 
begin
	unique case (state)
		AA: begin
			Q1 = '0;
			Q2 = '0;
		end
		
		AB: begin
			Q1 = '0;
			Q2 = '1;
		end
		
		AC: begin
			Q1 = '1;
			Q2 = '1;
		end
		
		AD: begin
			Q1 = '1;
			Q2 = '0;
		end
	endcase
end
	
endmodule
	