CFLAGS += -Wall -Wextra 

all:

	$(CC) dirwalk-driver.c -o dirwalk-driver $(CFLAGS)
	$(CC) globdriver.c -o globdriver $(CFLAGS)
	$(CC) ircline-driver.c -o ircline-driver $(CFLAGS)
	$(CC) itoadriver.c -o itoadriver $(CFLAGS)
	$(CC) readline-driver.c -o readline-driver $(CFLAGS) 
	$(CC) dtoa-driver.c -o dtoa-driver $(CFLAGS) -lm
	$(CC) stdio-driver.c -o stdio-driver $(CFLAGS) -lm
	$(CC) getline-driver.c -o getline-driver $(CFLAGS) -lm
	$(CC) getchar-driver.c -o getchar-driver $(CFLAGS) -lm

clean:

	$(RM) dirwalk-driver
	$(RM) globdriver
	$(RM) ircline-driver
	$(RM) itoadriver
	$(RM) readline-driver
	$(RM) dtoa-driver
	$(RM) stdio-driver
	$(RM) getline-driver
	$(RM) getchar-driver

