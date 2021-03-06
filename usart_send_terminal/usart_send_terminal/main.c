#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#define BAUDRATE 19200
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

//Declaration of our functions
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

//  char buffer =
//   char buff itoa(2, buffer, 10);

char String[]="DATASOFT123";
char str[]=" ";

int main(void)
{
	USART_init();        //Call the USART initialization code
	for (int i=0; i<100;i++)
	{
		str[i]=i;
	}
	while(1)
	{        //Infinite loop
		USART_putstring(String);    //Pass the string to the USART_putstring function and sends it over the serial
		_delay_ms(5000);        //Delay for 5 seconds so it will re-send the string every 5 seconds
		
		USART_putstring(str);
		_delay_ms(5000);
	}
	
	return 0;
}

void USART_init(void){
	
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8); //two registers as one
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}

unsigned char USART_receive(void){
	
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
	
}

void USART_send( unsigned char data){
	
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	
}

void USART_putstring(char* StringPtr){
	
	while(*StringPtr != 0x00)
	{
		USART_send(*StringPtr);
		StringPtr++;
	}
	
}