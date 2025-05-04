#include "libUinputWrapper.h"
#include <iostream>
#include <string>
#include <vector>

int g_ac;
char **g_av;

void fill_vector(std::vector<const char *> &v)
{
	try
	{
		for (int i = 0; i < g_ac; i++)
		{
			v.push_back(g_av[i]);
		}
	}
	catch(...)
	{
		std::cerr << "sum ting wong\n";
		exit(EXIT_FAILURE);
	}
	std::cout << "ok\n";
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
	else if (s.compare("a") == 0 || s.compare(std::toupper("a")) == 0)
		return (KEY_A);
	else if (s.compare("b") == 0 || s.compare(std::toupper("b")) == 0)
		return (KEY_B);
	else if (s.compare("c") == 0 || s.compare(std::toupper("c")) == 0)
		return (KEY_C);
	else if (s.compare("d") == 0 || s.compare(std::toupper("d")) == 0)
		return (KEY_D);
	else if (s.compare("e") == 0 || s.compare(std::toupper("e")) == 0)
		return (KEY_E);
	else if (s.compare("f") == 0 || s.compare(std::toupper("f")) == 0)
		return (KEY_F);
	else if (s.compare("g") == 0 || s.compare(std::toupper("g")) == 0)
		return (KEY_G);
	else if (s.compare("h") == 0 || s.compare(std::toupper("h")) == 0)
		return (KEY_H);
	else if (s.compare("i") == 0 || s.compare(std::toupper("i")) == 0)
		return (KEY_I);
	else if (s.compare("j") == 0 || s.compare(std::toupper("j")) == 0)
		return (KEY_J);
	else if (s.compare("k") == 0 || s.compare(std::toupper("k")) == 0)
		return (KEY_K);
	else if (s.compare("l") == 0 || s.compare(std::toupper("l")) == 0)
		return (KEY_L);
	else if (s.compare("m") == 0 || s.compare(std::toupper("m")) == 0)
		return (KEY_M);
	else if (s.compare("n") == 0 || s.compare(std::toupper("n")) == 0)
		return (KEY_N);
	else if (s.compare("o") == 0 || s.compare(std::toupper("o")) == 0)
		return (KEY_O);
	else if (s.compare("p") == 0 || s.compare(std::toupper("p")) == 0)
		return (KEY_P);
	else if (s.compare("q") == 0 || s.compare(std::toupper("q")) == 0)
		return (KEY_Q);
	else if (s.compare("r") == 0 || s.compare(std::toupper("r")) == 0)
		return (KEY_R);
	else if (s.compare("s") == 0 || s.compare(std::toupper("s")) == 0)
		return (KEY_S);
	else if (s.compare("t") == 0 || s.compare(std::toupper("t")) == 0)
		return (KEY_T);
	else if (s.compare("u") == 0 || s.compare(std::toupper("u")) == 0)
		return (KEY_U);
	else if (s.compare("v") == 0 || s.compare(std::toupper("v")) == 0)
		return (KEY_V);
	else if (s.compare("w") == 0 || s.compare(std::toupper("w")) == 0)
		return (KEY_W);
	else if (s.compare("x") == 0 || s.compare(std::toupper("x")) == 0)
		return (KEY_X);
	else if (s.compare("y") == 0 || s.compare(std::toupper("y")) == 0)
		return (KEY_Y);
	else if (s.compare("z") == 0 || s.compare(std::toupper("z")) == 0)
		return (KEY_Z);
	else
		return (-1);
}

void handle_key(const int fd, const std::string & s)
{
	int key = translate_string_into_key(s);
	if (key != -1)
		press_key(fd, key, 0);
	else
	{
		std::cerr << "wrong key entered\n"
	}
}

void handle_mouse(const int fd, const std::string & s)
{
	if (s == "lclick" || s == "rclick")
		libUinputWrapper::click(fd, 0);
	else if (s == "up" || s == "down" || s == "left" || s == "right")
	{
		if (s == "up")
			libUinputWrapper::move_mouse_from_cursor(fd, 0, 25);
		if (s == "down")
			libUinputWrapper::move_mouse_from_cursor(fd, 0, -25);
		if (s == "left")
			libUinputWrapper::move_mouse_from_cursor(fd, 25, 0);
		if (s == "right")
			libUinputWrapper::move_mouse_from_cursor(fd, -25, 0);
		return ;
	}
	std::cerr << "wrong mouse option ... must be: lclick/rclick/up/down/left/right\n";
}


int parse_args(const int fd)
{
	std::vector<const char *>	char_v;
	std::vector<std::string>	string_v;

	fill_vector(char_v);
	string_v::vector(char_v);

	for (std::vector<std::string>::iterator it = string_v.begin(); it != string_v.end(); it++)
	{
		if (s.compare("-k"))
		{
			if (it + 1 != string_v.end())
				handle_key(fd, *(it + 1));
			else
			{
				std::cerr << "no argument provided to -k\n";
				return (-1);
			}
			if (it + 2 != string_v.end())
			{
				it += 2;
				continue ;
			}
		}
		else if (s.compare("-m"))
		{
			if (it + 1 != string_v.end())
				handle_mouse(fd, *(it + 1));
			else
			{
				std::cerr << "no argument provided to -m\n";
				return (-1);
			}
			if (it + 2 != string_v.end())
			{
				it += 2;
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
		std::cout << "no arguments provided\n"
					<< "syntax: ./command_line_test "
					<< "{path to uinput module} "
					<< "{-k/-m} " 
					<< "{-k/-m parameter}...\n";
		return (0);
	}
	fd = libUinputWrapper::setup_device("command line testing device", std::string(argv[1]).c_str());
	if (fd < 0)
	{
		std::cerr << "sum ting wong: setup_device()\n";
		return (-1);
	}
	if (parse_args(fd) < 0)
	{
		std::cerr << "sum ting wong: parse_args()\n";
		return (-1);	
	}
	return (0);
}
