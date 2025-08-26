all: 		led

led: 		led.c
		$(CC) led.c -o led -ledit

install: 	led
		sudo cp led /usr/local/bin

clean:		
		rm -f led