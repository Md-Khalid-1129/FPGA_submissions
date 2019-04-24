module rndm_gen (input wire clk, input [7:0] reset_value, input wire reset, output reg [9:0] rnd, output reg [1:0] sig);

wire feedback;
wire [7:0] lfsr_next;

reg [26:0] time_value = 0;
reg [7:0] lfsr = 13;
reg [9:0] count;
reg [9:0] half = 511;
reg [9:0] one_fourth = 255;
reg [9:0] three_fourth = 767;

always @ (posedge clk)
begin
	time_value = time_value+1;
	if (time_value==27'b101111101011110000100000000)
	begin
		time_value = 27'b0;
		if (reset)
		begin
			lfsr = reset_value; 
			count = 0;
			rnd = reset_value;
		end
		else
		begin
			lfsr = lfsr_next;
			rnd = lfsr_next;
			
			if(rnd <= one_fourth)
		    begin
			    sig = 0;
		    end
		    else if(rnd <= half)
		    begin
			    sig = 1;
		    end
		    else if (rnd <= three_fourth)
		    begin
			    sig = 2;
		    end
		    else
		    begin
			    sig = 3;
		    end
			
			count = count + 1;
			if (count == 4'd15)
			begin 
				count = 0;
			end
		end
	end
end

assign feedback = lfsr[9] ^lfsr[6]; 
assign lfsr_next = {lfsr[8:0], feedback};

endmodule
