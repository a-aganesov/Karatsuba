`timescale 1ns / 1ps

module karatsuba_multiplier_tb;

  parameter N = 16;
  reg [N-1:0] a, b;
  wire [2*N-1:0] result;
  reg [2*N-1:0] expected_result;
  integer i, j;

  // Instantiate the Karatsuba multiplier
  karatsuba_multiplier #(N) uut (
    .a(a),
    .b(b),
    .result(result)
  );

  initial begin
    for (i = 1; i <= 100; i = i + 5) begin
      for (j = 1; j <= 100; j = j + 5) begin
        a = i;
        b = j;
        expected_result = a * b;
        #10;
        $display("Test: a = %d, b = %d, expected_result = %d, result = %d", a, b, expected_result, result);
        if (result !== expected_result)
          $display("Error: result does not match expected_result for a = %d, b = %d", a, b);
      end
    end
    $finish;
  end

endmodule
