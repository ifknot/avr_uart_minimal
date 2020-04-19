# avr_uart_minimal
C++ singleton UART minimalistic serial write char and hex byte and char read

Combines Meyer's canonical singleton with Mika Tuupola's Sat, Nov 19, 2011 blog post [Simple Serial Communications With AVR libc](https://appelsiini.net/2011/simple-usart-with-avr-libc/)

## examples

```cpp
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

```
