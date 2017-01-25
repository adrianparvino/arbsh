

char getchbuf[1025];

int getchbufp = 0;

int getch(void)
{
	return (getchbufp > 0) ? getchbuf[--getchbufp] : getchar();
}

void ungetch(int c)
{
	if (getchbufp >= 1025)
		return;
	else
	getchbuf[getchbufp++] = c;
}

