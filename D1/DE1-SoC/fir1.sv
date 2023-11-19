/////////////////////////////////////////////////////////////////////
// Design unit: FIR
//            :
// File name  : FIR.sv
//            :
// Description: Code for D1 Lab exercise
//            : Outline code for FIR
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


// FIR 16 stages; 16 bit samples. Could be parameterised.

module fir1 #(parameter N = 24)
	(input logic signed [N-1:0] in,
       input logic input_ready, ck, rst ,
       output logic signed [N-1:0] out,
       output logic output_ready);

typedef logic signed [N-1:0] sample_array;
sample_array samples [0:N-1];


function int clog2(input int n);
begin
	clog2 = 0;
	n--;
	while (n>0)
	begin
		clog2++;
		n>>=1;
	end
end
endfunction


// generate coefficients from Octave/Matlab
// disp(sprintf('%d,',round(fir1(23,0.5)*32768)))

/*
const sample_array coefficients [0:N-1] =
     '{-81, -134,  318, 645,
     -1257, -2262, 4522, 14633,
     14633, 4522, -2262,-1257,
     645, 318, -134, -81};
*/


//这里可能需要用Matlab测另一组 

const sample_array coefficients [0:N-1] =
     '{-51, -68,  114, 197,
     -324, -508, 768, 1141,
     -1702, -2653, 4743,14727,
     14727, 4743, -2653, -1702,
	 1141, 768, -508,-324,
	 197, 114,-68,-51};
	 
logic unsigned [clog2(N)-1:0] address; //clog2 of 16 is 4

logic signed [2*N-1:0] sum;

typedef enum logic [1:0] {waiting, loading, processing, saving} state_type;
state_type state, next_state;
logic load, count, reset_accumulator;

// Shift samples and load the input sample
always_ff @(posedge ck)
	if (load)
	begin
		for (int i=N-1; i >= 1; i--)
			samples[i] <= samples[i-1];
		samples[0] <= in;
	end


// accumulator register
always_ff @(posedge ck)
	if (reset_accumulator)
		sum <= '0;
	else
		sum <= sum + samples[address] * coefficients[address];

// Output the result after shifting to the right    
always_ff @(posedge ck)
	if (output_ready)
		out <= sum[2*N-2:N-1];
    
// Address counter logic
always_ff @(posedge ck) 
	begin
		if (count) 
            address <= address + 4'b0001;
        else
            address <= '0;
    end	
/*		if (address == 15)
			address <= 0;
		else
			address <= address + 1;
*/
// implement a synchronous counter that counts up through all 16 values of address
// when a count signal is true

// State machine logic

always_ff @(posedge ck, posedge rst) 
begin
    if (rst) 
		// Reset the state machine and accumulator when rst is active
		state <= waiting;
//		reset_accumulator <= 1;
	
	else 
		state <= next_state;
//		reset_accumulator <= 0;
end

always_comb
	begin
	output_ready = '0;
    load = '0;
    count = '0;
    reset_accumulator = '0;
	next_state = state; 
	
    unique case (state)
		waiting: begin
			reset_accumulator = '1;
			if (input_ready)
				next_state = loading;
//			else
//				next_state = waiting;
		end
		
		loading: begin
            reset_accumulator = '1;
            load = '1;
//			if (!load)
				next_state = processing;
//			else
//				next_state = loading;
		end
      
		processing: begin
//          load = '1;
			count = '1;
			if (address == N-1)
				next_state = saving;
//			else
//				next_state = processing;
		end
			
		saving: begin
                output_ready = '1;
//			if (output_ready)
				next_state = waiting;
//			else
//				next_state = saving;
		end
		
    endcase
end



endmodule


      
/*                                                    
    .::-------------------------------:---------==-=-     
    ::-=+++++++++*+++++++++=++++=++++*+++++++++***#*##-    
   .:-==++++=+=+**++++++++++++++-+++++*+++++******####*.   
  .:-=+=++++++++*+++++++++++++++::++++*++++*+*****#####+   
  ::-=++++++++++*+++++++++++++++:.=+++*++++********#####-  
  :-=+++++++++++*+++++++++++++++:..++**************#####*  
 .:-=++++++++++++++++*****++++++...-+++*+**+*******######: 
 ::-+++++++++++++++++++++++++++=....++**+++++******######- 
 ::=+++++++++++++++++*+++++++++=....=+++=+++++*****######= 
 ::=+++++++++++++++++++++++++++-....:+++-++++=+*****#####+ 
 ::+++++++++++++++++*++++++++++:.....+++.++++-+*****#####+ 
 ::++++++++++++++++++++++*+++++......=+*.=***+******#####+ 
 ::=++++++++++++++++++++++*+++=......-*#*###**%#****#####- 
 .:=+++++++++++++*##########*+-......=+%%***=:+#%#**#####. 
 .:-++++++++++++##*+*++++**+*+:........=%%#*#. .--*#####:  
  :-+++++++++++##++==+##+#*++=........-*#%#:+. ..-######   
  ::++++++++++++*++=#+#%+-*............-:-::: ...=######   
  :-++*++++++++++-:.+:::.:: ............:........*######=  
 :-++*++*+++++++=.. .:..........................-########+ 
 -=++*++******++=...............................+######### 
 =+++*++*+*******:.............................-########## 
 ++++*++*+++++***:............................-+########## 
 ++++**+*+++++*++-...........................::-#########* 
 *+=+**+***+++*+++=...........................-*######%##- 
 *%==+**********+***:.......................:+###**##%@%@+ 
 -%%=-+*+**+*********+-...................:+###***#%@@@@@+ 
 +*%@#+=++++++**********=:..............:+###%%%@@@@@@@@@+ 
 *@@@@@%-=+++++#++=+**#*#**::.........-*#%%%@@@@@@@@@@@@@= 
 *@@@@@@--+++++*++=-=*%##***::::::..:---+%%%%@@@@@@@@@@@@=               
*/         