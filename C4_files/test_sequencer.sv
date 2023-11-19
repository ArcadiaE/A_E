module test_sequencer;

    logic clk, n_rst, a;
    logic q1, q2;

    // 实例化 sequencer 模块
    sequencer s1 (
        .n_rst(n_rst),
        .clk(clk),
        .A(a),
        .Q1(q1),
        .Q2(q2)
    );

    // 时钟生成
    always #5 clk = ~clk;

    // 测试序列
    initial begin
        clk = 0;
        n_rst = 0; a = 0;
        #10 n_rst = 1;  //reset to AA

        
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
