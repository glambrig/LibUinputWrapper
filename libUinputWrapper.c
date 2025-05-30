#include "libUinputWrapper.h"
#include <stdio.h>
#include <ctype.h>

int wrapper_lib_uinput_fd = -1;

static int	checkIoctlErrors()
{
	int8_t errs[NB_BUTTONS];

	errs[0] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_0);
	errs[1] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_1);
	errs[2] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_2);
	errs[3] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_3);
	errs[4] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_4);
	errs[5] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_5);
	errs[6] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_6);
	errs[7] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_7);
	errs[8] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_8);
	errs[9] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_9);

	errs[10] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_A);
	errs[11] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_B);
	errs[12] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_C);
	errs[13] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_D);
	errs[14] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_E);
	errs[15] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_F);
	errs[16] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_G);
	errs[17] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_H);
	errs[18] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_I);
	errs[19] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_J);
	errs[20] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_K);
	errs[21] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_L);
	errs[22] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_M);
	errs[23] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_N);
	errs[24] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_O);
	errs[25] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_P);
	errs[26] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_Q);
	errs[27] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_R);
	errs[28] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_S);
	errs[29] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_T);
	errs[30] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_U);
	errs[31] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_V);
	errs[32] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_W);
	errs[33] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_X);
	errs[34] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_Y);
	errs[35] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_Z);

    errs[36] = ioctl(wrapper_lib_uinput_fd, UI_SET_RELBIT, REL_X);
    errs[37] = ioctl(wrapper_lib_uinput_fd, UI_SET_RELBIT, REL_Y);
	errs[38] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, BTN_LEFT);
	errs[39] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, BTN_RIGHT);
	errs[40] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_SPACE);
	errs[41] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_ENTER);
	errs[42] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_BACKSPACE);
	errs[43] = 0;
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

	wrapper_lib_uinput_fd = open(path_to_uinput, O_WRONLY);
	if (wrapper_lib_uinput_fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (ioctl(wrapper_lib_uinput_fd, UI_SET_EVBIT, EV_KEY) < 0 || ioctl(wrapper_lib_uinput_fd, UI_SET_EVBIT, EV_REL) < 0)
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
	if (write(wrapper_lib_uinput_fd, &uinp, sizeof(uinp)) < 0)
	{
		perror("write");
		return (-1);
	}
    if (ioctl(wrapper_lib_uinput_fd, UI_DEV_CREATE) < 0)
	{
		perror("ioctl");
		return (-1);
    }
	sleep(1);
	return (wrapper_lib_uinput_fd);
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

	if (lower == 'a') return KEY_A;
	if (lower == 'b') return KEY_B;
	if (lower == 'c') return KEY_C;
	if (lower == 'd') return KEY_D;
	if (lower == 'e') return KEY_E;
	if (lower == 'f') return KEY_F;
	if (lower == 'g') return KEY_G;
	if (lower == 'h') return KEY_H;
	if (lower == 'i') return KEY_I;
	if (lower == 'j') return KEY_J;
	if (lower == 'k') return KEY_K;
	if (lower == 'l') return KEY_L;
	if (lower == 'm') return KEY_M;
	if (lower == 'n') return KEY_N;
	if (lower == 'o') return KEY_O;
	if (lower == 'p') return KEY_P;
	if (lower == 'q') return KEY_Q;
	if (lower == 'r') return KEY_R;
	if (lower == 's') return KEY_S;
	if (lower == 't') return KEY_T;
	if (lower == 'u') return KEY_U;
	if (lower == 'v') return KEY_V;
	if (lower == 'w') return KEY_W;
	if (lower == 'x') return KEY_X;
	if (lower == 'y') return KEY_Y;
	if (lower == 'z') return KEY_Z;
	if (c == '0') return KEY_0;
	if (c == '1') return KEY_1;
	if (c == '2') return KEY_2;
	if (c == '3') return KEY_3;
	if (c == '4') return KEY_4;
	if (c == '5') return KEY_5;
	if (c == '6') return KEY_6;
	if (c == '7') return KEY_7;
	if (c == '8') return KEY_8;
	if (c == '9') return KEY_9;

	return (-1);
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
