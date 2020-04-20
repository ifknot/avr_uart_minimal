/*
 * uart_minimal_device.cpp
 *
 * Created: 4/18/2020 10:30:16 PM
 *  Author: ifkno
 */ 


#include "uart_minimal_device.h"

namespace singleton {
	
	void uart_minimal_device::write(char c){
		UDR0 = c;
		loop_until_bit_is_set(UCSR0A, UDRE0);	// spin on data register until completed
	}

	char uart_minimal_device::read() {
		loop_until_bit_is_set(UCSR0A, RXC0);	// spin in read register until contains something
		return UDR0;
	}

	void uart_minimal_device::write_nibble(char n) {
		n &= 0x0F;	// keep bottom 4 bits
		if (n > 9) {
			n += 7;	// convert to ascii 'A' when '0' added
		}
		n += '0';	// convert to decimal
		write(n);
	}

	void uart_minimal_device::write_hex(uint8_t n) {
		write_nibble(n >> 4);	// AVR is little-endian
		write_nibble(n);
	}

	uart_minimal_device::uart_minimal_device() {
		UBRR0H = UBRRH_VALUE;				// load baud rate
		UBRR0L = UBRRL_VALUE;				//		"
		// if the desired BAUD rate within the given tolerance could only be achieved by setting the U2X bit
		#if USE_2X							// use _BV convenience macro
		UCSR0A |= _BV(U2X0);				// set the U2X bit in the UART configuration
		#else
		UCSR0A &= ~(_BV(U2X0));				// clear the U2X bit in the UART configuration
		#endif
		UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); // 8-bit data
		UCSR0B = _BV(RXEN0) | _BV(TXEN0);   // Enable RX and TX
	}

	
}