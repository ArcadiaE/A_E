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
        // 初始化
        clk = 0;
        n_rst = 0; a = 0;
        #10 n_rst = 1;  // 释放复位

        // AA 到 AB
        #10 a = 1;
        #10 a = 0;  // 复位输入 A

        // AB 到 AD
        #10 a = 1;
        #10 a = 0;  // 复位输入 A

        // AD 到 AA
        #10 a = 0;

        // AA 到 AB (再次)
        #10 a = 1;
        #10 a = 0;  // 复位输入 A

        // AB 到 AC
        #10 a = 0;

        // AC 到 AA
        #10 a = 1;  // a 的值在这里不重要
        #10 a = 0;  // 结束测试

        #10 $finish;
    end

endmodule