/////////////////////////////////////////////////////////////////////
// Design unit: sequencer
//            :
// File name  : sequencer.sv
//            :
// Description: Code for M4 Lab exercise
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
//
// Revision   : Version 1.0 
/////////////////////////////////////////////////////////////////////


module sequencer(
    input logic start,   // Start signal (active high)
    input logic clock,   // Clock signal
    input logic Q0,      // Q0 input
    input logic n_rst,   // Asynchronous active low reset
    output logic add,    // Add control signal    
    output logic shift,  // Shift control signal
    output logic ready,  // Ready signal
    output logic reset   // Reset signal
);

    // Define states
    enum {
        IDLE,       // Idle state
        ADDING_SHIFTING, // Combined Adding and Shifting state
        STOPPED     // Stopped state
    } state;

    int count;

    // Define state transitions and outputs
    always_ff @(posedge clock, negedge n_rst)
    begin: SEQ
        if (!n_rst)
            state <= IDLE;
        else
        begin
            unique case(state)
                IDLE: begin
                    count <= 4;
                    if (start)
                        state <= ADDING_SHIFTING;
                    else
                        state <= IDLE;
                end
                
                ADDING_SHIFTING: begin
                    count <= count - 1;
                    if (count == 0)
                        state <= STOPPED;
                end
                
                STOPPED: begin
                    count <= 4;
                    if (start)
                        state <= IDLE;
                    else
                        state <= STOPPED;
                end
            endcase
        end
    end

    always_comb
    begin: COM
        add = '0;
        shift = '0;
        ready = '0;
        reset = '0;

        unique case (state)
            IDLE: begin
                reset = '1;
            end
            
            ADDING_SHIFTING: begin
                if (Q0)
                    add = '1;
                shift = '1;
            end
            
            STOPPED: begin
                ready = '1;
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