module ex4 (
	input [6:0] i,
	output is1
);
  assign is1=i[6]&i[5]&(i[4]|i[3]|i[2]);
endmodule

module ex4_tb;
	reg [6:0] i;
	wire is1;

	ex4 ex4_i (.i(i), .is1(is1));

	integer k;
	initial begin
		$display("Time\ti\ti_10\tis1");
		$monitor("%0t\t%b\t%0d\t%b", $time, i, i, is1);
		i = 0;
		for (k = 1; k < 128; k = k + 1)
			#10 i = k;
	end
endmodule