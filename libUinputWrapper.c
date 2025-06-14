#include "libUinputWrapper.h"
#include <stdio.h>
#include <ctype.h>

int __uinput_fd = -1;

static int	checkIoctlErrors()
{
	int8_t errs[NB_BUTTONS];

	errs[0] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_0);
	errs[1] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_1);
	errs[2] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_2);
	errs[3] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_3);
	errs[4] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_4);
	errs[5] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_5);
	errs[6] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_6);
	errs[7] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_7);
	errs[8] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_8);
	errs[9] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_9);

	errs[10] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_A);
	errs[11] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_B);
	errs[12] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_C);
	errs[13] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_D);
	errs[14] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_E);
	errs[15] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_F);
	errs[16] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_G);
	errs[17] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_H);
	errs[18] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_I);
	errs[19] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_J);
	errs[20] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_K);
	errs[21] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_L);
	errs[22] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_M);
	errs[23] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_N);
	errs[24] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_O);
	errs[25] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_P);
	errs[26] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_Q);
	errs[27] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_R);
	errs[28] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_S);
	errs[29] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_T);
	errs[30] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_U);
	errs[31] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_V);
	errs[32] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_W);
	errs[33] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_X);
	errs[34] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_Y);
	errs[35] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_Z);

    errs[36] = ioctl(__uinput_fd, UI_SET_RELBIT, REL_X);
    errs[37] = ioctl(__uinput_fd, UI_SET_RELBIT, REL_Y);
	errs[38] = ioctl(__uinput_fd, UI_SET_KEYBIT, BTN_LEFT);
	errs[39] = ioctl(__uinput_fd, UI_SET_KEYBIT, BTN_RIGHT);

	errs[40] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_SPACE);
	errs[41] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_ENTER);
	errs[42] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_BACKSPACE);

	errs[43] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_UP);
	errs[44] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_DOWN);
	errs[45] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_LEFT);
	errs[46] = ioctl(__uinput_fd, UI_SET_KEYBIT, KEY_RIGHT);
	errs[47] = 0;
	
	for (int i = 0; i < NB_BUTTONS - 1; i++)
	{
		if (errs[i] < 0)
		{
			if (write(STDERR_FILENO, "uinput: failed to set ioctl\n", 29) < 0)
			{
				perror("write");
			}
			return (-1);
		}
	}
	return (0);
}

int setup_device(const char *device_name, const char *path_to_uinput)
{
	struct uinput_user_dev uinp;

	__uinput_fd = open(path_to_uinput, O_WRONLY);
	if (__uinput_fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (ioctl(__uinput_fd, UI_SET_EVBIT, EV_KEY) < 0 || ioctl(__uinput_fd, UI_SET_EVBIT, EV_REL) < 0)
	{
		perror("ioctl");
		return (-1);
	}

    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name, device_name, strlen(device_name));
    uinp.id.version = 1;
    uinp.id.bustype = BUS_USB;
    uinp.id.product = 1;
    uinp.id.vendor = 1;

	if (checkIoctlErrors() < 0)
	{
		return (-1);
	}
	if (write(__uinput_fd, &uinp, sizeof(uinp)) < 0)
	{
		perror("write");
		return (-1);
	}
    if (ioctl(__uinput_fd, UI_DEV_CREATE) < 0)
	{
		perror("ioctl");
		return (-1);
    }
	sleep(1);
	return (__uinput_fd);
}

int	send_event_to_device(int device_fd, unsigned int which_key, int key_value, int event_type, u_int32_t release_key_after_ms)
{
	struct input_event	event;

	memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
	if (event_type == MOUSE_MOV_EVENT)
	{
		event.type = EV_REL;
	}
	else if (event_type == KEY_EVENT)
	{
    	event.type = EV_KEY;
	}
	else
	{
		if (write(STDERR_FILENO, "uinput: invalid event type\n", 28) < 0)
		{
			perror("write");
		}
		return (-1);
	}
    event.code = which_key;
    event.value = key_value;
    if (write(device_fd, &event, sizeof(event)) < 0)
	{
		if (write(STDERR_FILENO, "uinput: write to device failed\n", 32) < 0)
		{
			perror("write");
		}
		return (-1);
    }

	if (release_key_after_ms > 0)
	{
		usleep(release_key_after_ms * 1000);
	}
	else
	{
		usleep(5000);
	}

	event.type = EV_SYN;
	event.code = SYN_REPORT;
	event.value = 1;
	if (write(device_fd, &event, sizeof(event)) < 0)
	{
		if (write(STDERR_FILENO, "uinput: write to device failed\n", 32) < 0)
		{
			perror("write");
		}
		return (-1);
	}
	return (0);
}

int	click(int device_fd, u_int8_t which_click, u_int32_t release_key_after_ms)
{
	if (which_click == LEFT_CLICK)
	{
		if (send_event_to_device(device_fd, BTN_LEFT, 1, KEY_EVENT, release_key_after_ms) < 0)
		{
			return (-1);
		}
		if (send_event_to_device(device_fd, BTN_LEFT, 0, KEY_EVENT, release_key_after_ms) < 0)
		{
			return (-1);
		}
	}
	else if (which_click == RIGHT_CLICK)
	{
		if (send_event_to_device(device_fd, BTN_RIGHT, 1, KEY_EVENT, release_key_after_ms) < 0)
		{
			return (-1);
		}
		if (send_event_to_device(device_fd, BTN_RIGHT, 0, KEY_EVENT, release_key_after_ms) < 0)
		{
			return (-1);
		}
	}
	else
	{
		if (write(STDERR_FILENO, "uinput: invalid click type\n", 27) < 0)
		{
			perror("write");
		}
		return (-1);
	}
	return (0);
}

int	press_key(int device_fd, u_int16_t key, u_int32_t release_key_after_ms)
{
	if (send_event_to_device(device_fd, key, 1, KEY_EVENT, release_key_after_ms) < 0)
	{
		return (-1);
	}
	if (send_event_to_device(device_fd, key, 0, KEY_EVENT, release_key_after_ms) < 0)
	{
		return (-1);
	}
	return (0);
}

int	move_mouse_to_pos(int device_fd, int16_t x, int16_t y, struct screensize screensize)
{
	if (send_event_to_device(device_fd, REL_X, screensize.x - x, MOUSE_MOV_EVENT, 0) < 0)
	{
		return (-1);
	}
	if (send_event_to_device(device_fd, REL_Y, screensize.y - y, MOUSE_MOV_EVENT, 0) < 0)
	{
		return (-1);
	}
	return (0);
}

int	move_mouse_from_cursor(int device_fd, int16_t x, int16_t y)
{
	if (send_event_to_device(device_fd, REL_X, x, MOUSE_MOV_EVENT, 0) < 0)
	{
		return (-1);
	}
	if (send_event_to_device(device_fd, REL_Y, y, MOUSE_MOV_EVENT, 0) < 0)
	{
		return (-1);
	}
	return (0);	
}

static int receive_keycode_from_char(const char c)
{
	char lower = tolower(c);

	switch (lower)
	{
		case 'a': return KEY_A;
		case 'b': return KEY_B;
		case 'c': return KEY_C;
		case 'd': return KEY_D;
		case 'e': return KEY_E;
		case 'f': return KEY_F;
		case 'g': return KEY_G;
		case 'h': return KEY_H;
		case 'i': return KEY_I;
		case 'j': return KEY_J;
		case 'k': return KEY_K;
		case 'l': return KEY_L;
		case 'm': return KEY_M;
		case 'n': return KEY_N;
		case 'o': return KEY_O;
		case 'p': return KEY_P;
		case 'q': return KEY_Q;
		case 'r': return KEY_R;
		case 's': return KEY_S;
		case 't': return KEY_T;
		case 'u': return KEY_U;
		case 'v': return KEY_V;
		case 'w': return KEY_W;
		case 'x': return KEY_X;
		case 'y': return KEY_Y;
		case 'z': return KEY_Z;
		case '0': return KEY_0;
		case '1': return KEY_1;
		case '2': return KEY_2;
		case '3': return KEY_3;
		case '4': return KEY_4;
		case '5': return KEY_5;
		case '6': return KEY_6;
		case '7': return KEY_7;
		case '8': return KEY_8;
		case '9': return KEY_9;
		default: return -1;
	}
}

int type_string(int device_fd, const char *s)
{
	size_t		len;
	u_int16_t	key;

	len = strlen(s);
	for (size_t i = 0; i < len; i++)
	{
		key = receive_keycode_from_char(s[i]);
		if (key < 0)
		{
			return (-1);
		}
		if (press_key(device_fd, key, 0) < 0)
		{
			return (-1);
		}
	}
	return (0);
}

int cleanup_device(int device_fd)
{
	if (device_fd > 0)
	{
		if (ioctl(device_fd, UI_DEV_DESTROY) < 0)
		{
			return (-1);
		}
		if (close(device_fd) < 0)
		{
			return (-1);
		}
	}
	return (0);
}
