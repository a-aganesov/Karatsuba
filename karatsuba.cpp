#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

void generate_verilog(int N, const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    file << "module karatsuba_multiplier #(parameter N = " << N << ") (input [N-1:0] a, input [N-1:0] b, output [2*N-1:0] result);\n";
    file << "  wire [N/2-1:0] a1, a0, b1, b0;\n";
    file << "  wire [N-1:0] z2, z0;\n";
    file << "  wire [N:0] z1;\n";
    file << "\n";
    file << "  assign a1 = a[N-1:N/2];\n";
    file << "  assign a0 = a[N/2-1:0];\n";
    file << "  assign b1 = b[N-1:N/2];\n";
    file << "  assign b0 = b[N/2-1:0];\n";
    file << "\n";
    file << "  assign z2 = a1 * b1;\n";
    file << "  assign z0 = a0 * b0;\n";
    file << "  assign z1 = (a1 + a0) * (b1 + b0) - z2 - z0;\n";
    file << "\n";
    file << "  assign result = (z2 << N) + (z1 << (N/2)) + z0;\n";
    file << "endmodule\n";

    file.close();
}

void generate_testbench(int N, const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    file << "`timescale 1ns / 1ps\n\n";
    file << "module karatsuba_multiplier_tb;\n\n";
    file << "  parameter N = " << N << ";\n";
    file << "  reg [N-1:0] a, b;\n";
    file << "  wire [2*N-1:0] result;\n";
    file << "  reg [2*N-1:0] expected_result;\n";
    file << "  integer i, j;\n\n";
    file << "  // Instantiate the Karatsuba multiplier\n";
    file << "  karatsuba_multiplier #(N) uut (\n";
    file << "    .a(a),\n";
    file << "    .b(b),\n";
    file << "    .result(result)\n";
    file << "  );\n\n";
    file << "  initial begin\n";
    file << "    for (i = 1; i <= 100; i = i + 5) begin\n";
    file << "      for (j = 1; j <= 100; j = j + 5) begin\n";
    file << "        a = i;\n";
    file << "        b = j;\n";
    file << "        expected_result = a * b;\n";
    file << "        #10;\n";
    file << "        $display(\"Test: a = %d, b = %d, expected_result = %d, result = %d\", a, b, expected_result, result);\n";
    file << "        if (result !== expected_result)\n";
    file << "          $display(\"Error: result does not match expected_result for a = %d, b = %d\", a, b);\n";
    file << "      end\n";
    file << "    end\n";
    file << "    $finish;\n";
    file << "  end\n\n";
    file << "endmodule\n";

    file.close();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <N>" << std::endl;
        return 1;
    }

    int N = std::stoi(argv[1]);
    if (N <= 0) {
        std::cerr << "N must be a positive integer" << std::endl;
        return 1;
    }

    std::string verilog_filename = "karatsuba_multiplier.v";
    std::string testbench_filename = "karatsuba_multiplier_tb.v";

    generate_verilog(N, verilog_filename);
    generate_testbench(N, testbench_filename);

    std::cout << "Verilog file generated: " << verilog_filename << std::endl;
    std::cout << "Testbench file generated: " << testbench_filename << std::endl;

    return 0;
}

