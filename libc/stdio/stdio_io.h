	





GFILE _iob[OPEN_MAX] = {
	{ 0, GGNULL, GGNULL, 1, 0, 0, 1, 0, 0},	/* stdin */
	{ 0, GGNULL, GGNULL, 1, 1, 1, 0, 0, 0},	/* stdout */
	{ 0, GGNULL, GGNULL, 1, 2, 1, 0, 0, 1}	/* stderr */ 
};

GFILE *gstdin = (&_iob[0]);
GFILE *gstdout = (&_iob[1]);
GFILE *gstderr = (&_iob[2]);
GFILE *gstdhold;

