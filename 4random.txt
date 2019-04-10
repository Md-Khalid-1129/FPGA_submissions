module rndm_gen (
input clock,
input reset,
output reg [3:0] rnd 
);

wire feedback;
wire [3:0] lfsr_next;

//An LFSR cannot have an all 0 state, thus reset to non-zero value
reg [3:0] reset_value = 13;
reg [3:0] lfsr;
reg [2:0] count;

// pragma translate_off 
//integer f;
//initial begin
//f = $fopen("output.txt","w");
//end
// pragma translate_on

always @ (posedge clock or posedge reset)
begin
if (reset) begin
lfsr <= reset_value; 
count <= 3'h7;
rnd <= 0;
end
else begin
lfsr <= lfsr_next;
count <= count + 1;
// a new random value is ready
if (count == 3'd2) begin 
count <= 0;
rnd <= lfsr; //assign the lfsr number to output after 10 shifts
// pragma translate_off 
//$fwrite(f,"%0d\n",rnd);
// pragma translate_on 
end
end
end

// X4+x3
assign feedback = lfsr[3] ^ lfsr[2]; 
assign lfsr_next = {lfsr[2:0], feedback};

// pragma translate_off
//always @ (*) begin 
//if (rnd == reset_value) begin
//$fclose(f); 
//$finish();
//end
//end
// pragma translate_on
endmodule
