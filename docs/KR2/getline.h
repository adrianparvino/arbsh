/* getline: read a line, return length */
int kr2getline(char *line, int max)
{
    if (fgets(line, max, stdin) == NULL)
         return 0;
    else
         return strlen(line);
}

