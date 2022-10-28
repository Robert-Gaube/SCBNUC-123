module cnt1s (
  input [5:0] i,
  output reg [5:0] o
);
  reg [5:0]var;
  always@(*)
  begin
    var = i;
    o = 3'b000;
    while(var != 0)
    begin
      var = (var & (var - 1));
      o = o + 1;
    end
  end
endmodule

module cnt1s_tb;
  reg [5:0] i;
  wire [5:0] o;

  cnt1s cnt1s_i (.i(i), .o(o));

  integer k;
  initial begin
    $display("Time\ti\t\to");
    $monitor("%0t\t%b(%2d)\t%b(%0d)", $time, i, i, o, o);
    i = 0;
    for (k = 1; k < 64; k = k + 1)
      #10 i = k;
  end
endmodule