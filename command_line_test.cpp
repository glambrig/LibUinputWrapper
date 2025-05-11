#include "libUinputWrapper.h"
#include <iostream>
#include <string>
#include <vector>

int g_ac;
char **g_av;

void fill_vector(std::vector<std::string> &v)
{
	try
	{
		for (int i = 0; i < g_ac; i++)
		{
			v.push_back(std::string(g_av[i]));
		}
	}
	catch(...)
	{
		std::cerr << "Unable to fill arg vector\n";
		exit(EXIT_FAILURE);
	}
}

int translate_string_into_key(const std::string & s)
{
	if (s.compare("0") == 0)
		return (KEY_0);
	else if (s.compare("1") == 0)
		return (KEY_1);
	else if (s.compare("2") == 0)
		return (KEY_2);
	else if (s.compare("3") == 0)
		return (KEY_3);
	else if (s.compare("4") == 0)
		return (KEY_4);
	else if (s.compare("5") == 0)
		return (KEY_5);
	else if (s.compare("6") == 0)
		return (KEY_6);
	else if (s.compare("7") == 0)
		return (KEY_7);
	else if (s.compare("8") == 0)
		return (KEY_8);
	else if (s.compare("9") == 0)
		return (KEY_9);
	else if (s == "A" || s == "a")
		return (KEY_A);
	else if (s == "B" || s == "b")
		return (KEY_B);
	else if (s == "C" || s == "c")
		return (KEY_C);
	else if (s == "D" || s == "d")
		return (KEY_D);
	else if (s == "E" || s == "e")
		return (KEY_E);
	else if (s == "F" || s == "f")
		return (KEY_F);
	else if (s == "G" || s == "g")
		return (KEY_G);
	else if (s == "H" || s == "h")
		return (KEY_H);
	else if (s == "I" || s == "i")
		return (KEY_I);
	else if (s == "J" || s == "j")
		return (KEY_J);
	else if (s == "K" || s == "k")
		return (KEY_K);
	else if (s == "L" || s == "l")
		return (KEY_L);
	else if (s == "M" || s == "m")
		return (KEY_M);
	else if (s == "N" || s == "n")
		return (KEY_N);
	else if (s == "O" || s == "o")
		return (KEY_O);
	else if (s == "P" || s == "p")
		return (KEY_P);
	else if (s == "Q" || s == "q")
		return (KEY_Q);
	else if (s == "R" || s == "r")
		return (KEY_R);
	else if (s == "S" || s == "s")
		return (KEY_S);
	else if (s == "T" || s == "t")
		return (KEY_T);
	else if (s == "U" || s == "u")
		return (KEY_U);
	else if (s == "V" || s == "v")
		return (KEY_V);
	else if (s == "W" || s == "w")
		return (KEY_W);
	else if (s == "X" || s == "x")
		return (KEY_X);
	else if (s == "Y" || s == "y")
		return (KEY_Y);
	else if (s == "Z" || s == "z")
		return (KEY_Z);
	else
		return (-1);
}

void handle_key(const int fd, const std::string & s)
{
	int key = translate_string_into_key(s);

	if (key != -1)
		libUinputWrapper::press_key(fd, key, 0);
	else
	{
		std::cerr << "Wrong key entered: key = " << s << '\n';
	}
}

void handle_mouse(const int fd, const std::string & s)
{
	if (s == "lclick")
	{
		libUinputWrapper::click(fd, LEFT_CLICK, 100);
		return ;
	}
	else if (s == "rclick")
	{
		libUinputWrapper::click(fd, RIGHT_CLICK, 100);
		return ;	
	}
	else if (s == "up" || s == "down" || s == "left" || s == "right")
	{
		if (s == "up")
		{
			libUinputWrapper::move_mouse_from_cursor(fd, 0, -25);
		}
		if (s == "down")
		{
			libUinputWrapper::move_mouse_from_cursor(fd, 0, 25);
		}
		if (s == "left")
		{
			libUinputWrapper::move_mouse_from_cursor(fd, -45, 0);
		}
		if (s == "right")
		{
			libUinputWrapper::move_mouse_from_cursor(fd, 45, 0);
		}
		return ;
	}
	std::cerr << "wrong mouse option ... must be: lclick/rclick/up/down/left/right\n";
}


int parse_args(const int fd)
{
	std::vector<std::string>	string_v;

	fill_vector(string_v);
	for (std::vector<std::string>::iterator it = string_v.begin() + 2; it != string_v.end(); it++)
	{
		if (it->compare("-k") == 0)
		{
			std::cout << "-k detected: arg = " << *(it + 1) << '\n';
			if (it + 1 != string_v.end())
				handle_key(fd, *(it + 1));
			else
			{
				std::cerr << "error: No argument provided to -k\n";
				return (-1);
			}
			if (it + 2 != string_v.end())
			{
				it++;
				continue ;
			}
		}
		else if (it->compare("-m") == 0)
		{
			std::cout << "-m detected: arg = " << *(it + 1) << '\n';
			if (it + 1 != string_v.end())
				handle_mouse(fd, *(it + 1));
			else
			{
				std::cerr << "error: No argument provided to -m\n";
				return (-1);
			}
			if (it + 2 != string_v.end())
			{
				it++;
				continue ;
			}
		}
	}
	
	return (0);
}

int main(int argc, char **argv)
{
	int fd;

	g_ac = argc;
	g_av = argv;
	if (argc < 2)
	{
		std::cerr << "Too few arguments:\n"
					<< "-m: simulate a mouse event. Available mouse events are: rclick, lclick, up, down, left, right.\n"
    				<< "-k: simulate a key event. Available key events are: all alphanumeric keys.\n";
		return (0);
	}
	fd = libUinputWrapper::setup_device("command-line-testing-device", std::string(argv[1]).c_str());
	if (fd < 0)
	{
		std::cerr << "error: setup_device() ... "
					<< "do you have the path to the uinput module as first argument?\n"
					<< "do you have the correct permissions? (sudo)";
		return (-1);
	}
	if (parse_args(fd) < 0)
	{
		std::cerr << "error: parse_args() failed\n";
		return (-1);	
	}
	return (0);
}
