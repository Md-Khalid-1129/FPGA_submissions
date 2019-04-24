module matrix_mult (input clock, input reset, output reg [9:0] rnd, output reg [1:0] value);

wire feedback;
wire [9:0] lfsr_next;

//An LFSR cannot have an all 0 state, thus reset to non-zero value
//reg [26:0] delay;
reg [9:0] reset_value = 13;
reg [9:0] lfsr;
reg [9:0] count;
reg [9:0] half = 511;
reg [9:0] one_fourth = 255;
reg [9:0] three_fourth = 767;


always @ (posedge clock or posedge reset)
begin
	//delay <= delay+1;
	//if(delay==27'b000000011110100001001000000)
	//begin
if (reset)
	begin
		lfsr <= reset_value; 
		count <= 1;
		rnd <= 13;
	end
	else
	begin
		lfsr <= lfsr_next;
		rnd <= lfsr_next;
		if(rnd <= one_fourth)
	   begin
	       value <= 0;
	   end
	   else if(rnd <= half)
	   begin
	       value <= 1;
	   end
	   else if (rnd <= three_fourth)
	   begin
	       value <= 2;
	   end
	   else
	   begin
	       value <= 3;
	   end
		count <= count + 1;
	end
end
		
assign feedback = lfsr[9] ^lfsr[6]; 
assign lfsr_next = {lfsr[8:0], feedback};

endmodule