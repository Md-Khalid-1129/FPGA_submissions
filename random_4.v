module rndm_gen (input clock, input reset, output reg [3:0] rnd);

wire feedback;
wire [3:0] lfsr_next;

//An LFSR cannot have an all 0 state, thus reset to non-zero value
reg [26:0] delay;
reg [3:0] reset_value = 13;
reg [3:0] lfsr;
reg [2:0] count;

always @ (posedge clock)
begin
	delay <= delay+1;
	if(delay==27'b000000011110100001001000000)
	begin
		if (reset)
		begin
			lfsr <= reset_value; 
			count <= 3'h7;
			rnd <= 0;
		end
		else
		begin
			lfsr <= lfsr_next;
			rnd <= lfsr;
			count <= count + 1;
			// a new random value is ready
			if (count == 3'd7)
			begin 
				count <= 0;
			//rnd <= lfsr; //assign the lfsr number to output after 10 shifts 
			end
		end
	end
end

// X4+x3
assign feedback = lfsr[3] ^ lfsr[2]; 
assign lfsr_next = {lfsr[2:0], feedback};

endmodule
