#include <gcurses/gcurses.h>

WINDOW _IO_canon[CURSES_MAX] = {
        //{ 0, 0, NULL, NULL, NULL, 0, 0},
       // { 1, 0, NULL, NULL, NULL, 0, 0},
        //{ 2, 0, NULL, NULL, NULL, 0, 0}
	{ 0, 0, NULL, NULL, NULL, 0, 0, NULL, NULL, { 0}, {0}, { 0 }},
	{ 0, 0, NULL, NULL, NULL, 0, 0, NULL, NULL, { 0 }, {0}, { 0 }},
	{ 0, 0, NULL, NULL, NULL, 0, 0, NULL, NULL, { 0 }, {0}, { 0 }},
};

