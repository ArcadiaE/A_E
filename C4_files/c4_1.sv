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


module c4 (
    input logic n_clk, rst, a,
    output logic s, t
);

    logic s_plus, t_plus, s_bar, t_bar, clk;

    // 反相时钟
    assign clk = ~n_clk;

    // 状态机模块
    sequencer seq (
        .n_rst(!rst),
        .clk(clk),
        .A(a),
        .Q1(s_plus),
        .Q2(t_plus)
    );

    // D型触发器模块
    d_ff d0 (
        .q(s),
        .qbar(s_bar),
        .clk(clk),
        .rst(n_rst),
        .d(s_plus)
    );

    d_ff d1 (
        .q(t),
        .qbar(t_bar),
        .clk(clk),
        .rst(n_rst),
        .d(t_plus)
    );

endmodule
 