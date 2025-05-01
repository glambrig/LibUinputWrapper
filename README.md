# uinputWrapperLib

### An easy-to-use library which provides mouse and keyboard simulation on Linux.

The reasons for the library's existence is that I found mouse and keyboard simulation to be overly and unnecessarily complicated on Linux. It's also to avoid using XLib.

This is still a work in progress, and as such, certain things are still incomplete.

Running `make` gives you a static library file that can be linked with other projects.
If you want to use these functions in C++, that can be done using the `uinputWrapperLib::` namespace.
