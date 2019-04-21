module rndm_gen (input wire clk, input reset, output reg [7:0] rnd);

wire feedback;
wire [7:0] lfsr_next;

//An LFSR cannot have an all 0 state, thus reset to non-zero value
reg [26:0] delay = 0;
reg [7:0] reset_value = 13;
reg [7:0] lfsr = 13;
reg [3:0] count;

always @ (posedge clk)
begin
	delay = delay+1;
	if(delay==27'b101111101011110000100000000)
	begin
		delay = 27'b0;
		if (reset)
		begin
			lfsr = reset_value; 
			count = 0;
			rnd = 13;
		end
		else
		begin
			lfsr = lfsr_next;
			rnd = lfsr_next;
			count = count + 1;
			if (count == 4'd15)
			begin 
				count = 0;
			end
		end
	end
end

// X4+x3
assign feedback = lfsr[7] ^lfsr[5] ^lfsr[4] ^ lfsr[3]; 
assign lfsr_next = {lfsr[6:0], feedback};

endmodule
