#!/bin/bash

# Compile the generator
make clean
make

# Generate Verilog file for N=16
./karatsuba 16

# Check if Icarus Verilog (iverilog) is installed
if ! command -v iverilog &> /dev/null
then
    echo "iverilog could not be found, please install it to run the testbench"
    exit
fi

# Run the testbench
iverilog -o karatsuba_multiplier_tb karatsuba_multiplier_tb.v karatsuba_multiplier.v
vvp karatsuba_multiplier_tb

