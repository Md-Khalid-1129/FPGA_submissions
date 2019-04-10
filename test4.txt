module rndm_tb;
wire clock;
wire reset;
wire [3:0] rnd;

reg clk;
reg rst;

rndm_gen rando(
.clock (clock),
.reset (reset),
.rnd (rnd)
);

assign clock = clk; 
assign reset = rst; 

// generate the clock
initial begin
clk <= 0;
forever begin
#10 ;
clk <= ~clk;
end
end

initial begin
rst <= 1;
#10;
rst <= 0;
end
initial begin
 $display("clock rnd");
     $monitor("%d,%d", clock, rnd);
 end 

endmodule

