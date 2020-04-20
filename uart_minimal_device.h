/*
 * uart_minimal_device.h
 *
 * Created: 4/16/2020 8:44:32 PM
 *  Author: ifknot
 */ 


#ifndef UART_DEVICE_H_
#define UART_DEVICE_H_

#ifndef	F_CPU// appease grumpy compilers
#define F_CPU 16000000UL // 16 MHz
#endif

#ifndef BAUD// appease grumpy compilers
#define BAUD 9600
#endif

#include <avr/io.h>
#include <util/setbaud.h>

namespace singleton {

	/**
	 * Minimal uart byte io (Meyer's canonical singleton implementation)
	 * @note Use -fno-threadsafe-statics 
	 * This disables the mutex around initialization of local static variables which is useless
	 * in single threaded and hence `__cxa_guard_acquire'	is undefined and will raise compile time error
	 */
	struct uart_minimal_device {

		inline static uart_minimal_device& instance() {
			static uart_minimal_device u;
			return u;
		}
	
		/**
		 * wait for a character write to serial
		 */
		static void write(char c);
	
		/**
		 * wait for a character read from serial
		 */
		static char read();
	
		/**
		 * write the lower 4 bits as upper case hexadecimal number
		 */
		static void write_nibble(char n);
	
		/**
		 * byte overloaded write hexadecimal
		 */
		static void write_hex(uint8_t n);

		uart_minimal_device(const uart_minimal_device &) = delete;
		
		uart_minimal_device & operator = (const uart_minimal_device &) = delete;
		
		~uart_minimal_device() = default;

	private:

		/**
		* default to the most common configuration: 9600, no parity, 8 data bits, 1 stop bit.
		* UCSZ20 UCSZ01 and UCSZ00 control the data size. 
		* Possible sizes are 5-bit (000), 6-bit (001), 7-bit (010), 8-bit (011) and 9-bit (111). 
		* Most common used data size is 8-bit.
		*/
		uart_minimal_device();
		
	};

}

#endif

/* examples:

auto& uart = singleton::uart_minimal_device::instance();

uart.write('?');
auto c = uart.read();

while(c != 0x0D) {
	uart.write(c);
	c = uart.read();
}
uart.write('\r');
uart.write('\n');
uart.write('b');
uart.write('y');
uart.write('e');

for(char i{0}; i < 255; ++i) {
	uart.write_hex((uint8_t)i);
	uart.write(' ');
	uart.write(i);
	uart.write('\r');
	uart.write('\n');
}

*/