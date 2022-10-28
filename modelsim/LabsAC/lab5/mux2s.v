module mux2s #(
  parameter w=32 
)(
  input [1:0]s,
  input [w-1:0] d0, d1, d2, d3,
  output reg [w-1:0] o
);
  always @(*)
  begin
      case (s)
        2'b00 : o = d0;
        2'b01 : o = d1;
        2'b10 : o = d2;
        default : o = d3; 
      endcase
  end
endmodule

module mux2s_tb;
  reg [1:0]s;
  reg [7:0] d0, d1, d2, d3;
  wire [7:0] o;
  
  
  mux2s #(.w(8)) inst0(
    .s(s), .d0(d0), .d1(d1), .d2(d2), .d3(d3), .o(o)
  );
  
  integer k;
  initial 
  begin 
    for(k = 0; k < 8; k = k + 1) 
    begin
      s = k;
      {d0, d1, d2, d3} = $urandom();
      #10;
       
    end
  end

endmodule

