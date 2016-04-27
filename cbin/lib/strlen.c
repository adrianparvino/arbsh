int strlen(char string[])
{
	int j;
	while ( string[j] != '\0' )
		++j;

	return j;
}

