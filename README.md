# libUinputWrapper

### An easy-to-use library which provides mouse and keyboard simulation on Linux.

The reasons for the library's existence is that I found mouse and keyboard simulation to be overly and unnecessarily complicated on Linux. It's also to avoid using XLib. It is basically a wrapper library for interacting with the uinput kernel module.

This is still a work in progress, and as such, certain things are still incomplete.

Running `make` gives you a static library file that can be linked with other projects.
If you want to use these functions in C++, that can be done using the `LibUinputWrapper::` namespace.
All of the currently available functions are (sort of) documented in the header file.

#### Important:
In order for this library to work, you have to make sure the uinput kernel module is loaded. This can be done like so:

`sudo modprobe uinput`

`sudo chmod 666 {Path to uinput}`

The path to uinput is usually /dev/uinput or /dev/input/uinput depending on your system.

#### Command line `cmd_libuinput_test` utility
You can test this library in the command line by using the the `cmd_libuinput_test` program.
To create this program, use `make cmd`, then run the `cmd_libuinput_test` binary.

The available options are as follows:
- `-m`: simulate a mouse event. Available mouse events are: `rclick`, `lclick`, `up`, `down`, `left`, `right`.
- `-k`: simulate a key event. Available key events are: all alphanumeric keys.
