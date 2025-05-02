#include "libUinputWrapper.h"
#include <iostream>
#include <unistd.h>

int main()
{
	int fd = setup_device("test", "/dev/uinput");
	if (fd < 0)
	{
		return (-1);
	}
	std::cout << "typing...\n";
	press_key(fd, KEY_A, 20);
	std::cout << "\ntyped A\n";
	sleep(1);
	press_key(fd, KEY_B, 200);
	sleep(1);
	press_key(fd, KEY_H, 0);
	press_key(fd, KEY_E, 0);
	press_key(fd, KEY_L, 0);
	press_key(fd, KEY_L, 0);
	press_key(fd, KEY_O, 0);
	std::cout << "\nfinished typing\n";
	return 0;
}
