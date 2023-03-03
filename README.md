# picoMIPs-assembler



## Getting started

This tool was designed for use as a part of a coursework during my degree.

The task of the coursework was to create a minimalistic picoRISC (picoMIPs) core using the minimum amount of hardware.
This assembler does not support LW or SW instructions as the picoRISC does not have any data memory.

### Building the tool

This tool uses the Conan package manager. In order to build the tool run the following set of commands:
```
mkdir build ; cd build
conan install ..
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```
CMake will choose the generator with this method, a specific generator can be chosen with the command
```
cmake .. -G <Generator> -DCMAKE_BUILD_TYPE=Release
```

The compiled binary will be found under build/bin/ named 'picoMIPs-assembler'.

### Tool Usage

Usage of either command line arguments or passing file paths from within the program.<br>
*-b* or *--defines* to specify the architecture information<br>
*-s* or *--source* to specify the source assembly file<br>
*-o* or *--output* to specify the output file<br>

Define your architectures instruction set and register information in *.json* format.

You need to ensure that the register information is held within a field named *registers*
You need to ensure that the instruction information is held within a field named *instructions*
You need to ensure that the instruction field widths is held within a field named *widths*
You may choose if branches/jumps are either 'relative' or 'absolute' by the field named *branches*


With respect to registers, a range may be specified and the tool will automatically expand the range.
An example is:<br>
  *"$t0-$t3" : [8 , 11],*<br>
Which will be expanded to:<br>
*"$t0" : 8,*<br>
*"$t1" : 9,*<br>
*"$t2" : 10,*<br>
*"$t3" : 11,*<br>
The ranges and be continuous and increment the same amount.<br>

See the provided *picomips-instructions.json* file for an example.<br>

## Assembly constructions provided

*;* used for single-line comments<br>
/* */ used for multi-line comments

## Acknowledgements

This project uses the Conan package manager.
The JSON library used is https://json.nlohmann.me/xw
