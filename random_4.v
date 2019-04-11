module rndm_gen (input clock, input reset, output reg [7:0] rnd);

wire feedback;
wire [7:0] lfsr_next;

//An LFSR cannot have an all 0 state, thus reset to non-zero value
reg [26:0] delay;
reg [7:0] reset_value = 13;
reg [7:0] lfsr;
reg [3:0] count;

always @ (posedge clock)
begin
	delay <= delay+1;
	if(delay==27'b000000011110100001001000000)
	begin
		if (reset)
		begin
			lfsr <= reset_value; 
			count <= 4'hF;
			rnd <= 13;
		end
		else
		begin
			lfsr <= lfsr_next;
			rnd <= lfsr;
			count <= count + 1;
			if (count == 4'd15)
			begin 
				count <= 0;
			end
		end
	end
end

// X4+x3
assign feedback = lfsr[7] ^lfsr[5] ^lfsr[4] ^ lfsr[3]; 
assign lfsr_next = {lfsr[6:0], feedback};

endmodule
