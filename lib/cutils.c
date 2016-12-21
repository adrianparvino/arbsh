

void cutilerror(char *message, int i)
{
	if ( i > 0 )
		perror("Error: ");
	fprintf(stderr, "%s", message);
	if ( i > -1 )
		exit (i);
}

