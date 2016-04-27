void striprel(char *source, char *end)
{
        int i = 0;
        int j = 0;
        while ( source[i] != '\0' )
        {
                if ( source[i] == '.' && source[i + 1] == '.' && source[i + 2] == '.' )
                {
                        i +=3;
                        while (  source[i] != '/' )
                                ++i;
                }
                if ( source[i] == '.' && source[i + 1] == '.' && source[i + 2] == '/' )
                        j = ( i + 3 )  ;
                if ( source[i] == '.'  && source[i + 1] == '/' )
                        j = ( i + 2 )  ;
                ++i;
        }
        i = 0;
        while ( source[i] != '\0' )
        {
                end[i] = source[j];
                ++i;
                ++j;
        }
        source[i] = '\0';


}

