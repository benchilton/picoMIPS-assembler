# picoMIPs-assembler



## Getting started

This tool was designed for use as a part of a coursework during my degree.

The task of the coursework was to create a minimalistic picoRISC (picoMIPs) core using the minimum amount of hardware.
This assembler does not support LW or SW instructions as the picoRISC does not have any data memory.

## Tool Usage

Define your architectures instruction set and register information in *.json* format.

You need to ensure that the register information is held within a field named *registers*
You need to ensure that the instruction information is held within a field named *instructions*


With respect to registers, a range may be specified and the tool will automatically expand the range.
An example is:
  *"$t0-$t3" : [8 , 12],*
This will be expanded to:
*"$t0" : 8,*
*"$t1" : 9,*
*"$t2" : 10,*
*"$t3" : 11,*
However the ranges must match and be continuous.

See the provided *picomips-instructions.json* file for an example.

## Assembly constructions provided

*;* used for single-line comments
/* */ used for multi-line comments

## Acknowledgements

This project uses the Conan package manager.
The JSON library used is https://json.nlohmann.me/xw
