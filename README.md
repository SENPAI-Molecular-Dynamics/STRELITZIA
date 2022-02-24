# STRELITZIA
## Manager for controlling SENPAI worker instances across different devices
STRELITZIA runs on one device and takes commands and data from a COFFIN instance.
It distributes the work across the worker instances, applying optimizations each frame for maximum efficiency.
Workers are controlled via the network and STRELITZIA catches and forwards any errors to COFFIN and automatically deals with the rescheduling.

## How to build
STRELITZIA is intended to be built on Linux using make.
The make rules are:
- `make` simply compiles the binary
- `make run` compiles and executes
- `make clean` removes binary files, returning the directory into its state before running `make`
- `make rebuild` cleans the directory and then builds it again from the ground up
- `make debug` starts a gdb instance on STRELITZIA
- `make valgrind` runs the valgrind memory checker

As a result, `gcc` and `make` are required.
`gdb` and `valgrind` are only needed for debugging.
Standart `glibc` is also nessecary.

## Usage
STRELITZIA can be configured through command-line arguments and through its config file.
```
Usage: strelitzia
c / -c / --config	[file]	specify config file
l / -l / --log		[file]	specify log file
h / -h / --help			show this usage
```

If a config file is not specified, STRELITZIA will use the default one at ./strelitzia.conf.
The log file can also be configured in the config file, but defaults to ./strelitzia.log.

The config file is read line-by-line.
Comments are denoted using `#`.
Anything that follows a `#` is ignored.
Spaces and tabs are ignored.
The format is a key-value pair.
The key is the first word in the line, followed by one or more values.
A reference for all possible config values may be found in strelitzia.conf in this Repository.
