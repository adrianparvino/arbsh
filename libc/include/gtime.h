#include <gstddef.h>

typedef size_t time_t;
typedef size_t clock_t;

struct tm {
	int tm_sec; 	// seconds after the minute — [0, 60]
	int tm_min; 	// minutes after the hour — [0, 59]
	int tm_hour; 	// hours since midnight — [0, 23]
	int tm_mday; 	// day of the month — [1, 31]
	int tm_mon; 	// months since January — [0, 11]
	int tm_year; 	// years since 1900
	int tm_wday; 	// days since Sunday — [0, 6]
	int tm_yday;  	// days since January 1 — [0, 365]
	int tm_isdst;  	// Daylight Saving Time flag
};



