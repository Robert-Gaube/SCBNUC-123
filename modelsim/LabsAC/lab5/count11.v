module count11 #(
  parameter w=32,
  parameter iv=0
)(
  input clk, rst_b, c_up,
  output reg [w-1:0] q
);
  always@(posedge clk, negedge rst_b)
  begin
    if(!rst_b) q<=iv;
    else if(c_up) q<=q+11;
  end
endmodule
// w=8, iv='hfb, Tclk=500, Prst_b=10
module count11_tb;
  reg clk, rst_b, c_up;
  wire [7:0] q;
  
  count11 #( .w(8), .iv('hfb)) inst0(
    .clk(clk), .rst_b(rst_b), .c_up(c_up), .q(q)
  );
  //generate clk signal of given period and number of cycles
  localparam CLK_PERIOD=500;
  localparam CLK_CYCLES=6;
  initial begin
    clk=0;
    repeat (2*CLK_CYCLES)
    #(CLK_PERIOD/2) clk = 1-clk;
  end
  //generate rst rst_b signal of given pulse duration
  localparam RST_PULSE=10;
  initial begin
    rst_b=0;
    #(RST_PULSE) rst_b=1;
    end
    initial begin
      c_up=1;
      #(1*CLK_PERIOD) c_up=0;
      #(1*CLK_PERIOD) c_up=1;
      end
endmodule

