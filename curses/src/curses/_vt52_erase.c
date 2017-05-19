#include <gcurses/gcurses.h>

char *_vt52_erase(char *buf)
{
	sprintf(buf, "%s%s", ansiglb.t_gohome, ansiglb.t_clrcur2bot);
	return buf;
}
