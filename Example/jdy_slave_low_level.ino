/*task handler for jdy_31 bluetooth slave module*/
/*version 1.0*/
/*Reza Ebrahimi https://github.com/ebrezadev */
#include "jdy_slave.h"
#include <AltSoftSerial.h>

AltSoftSerial altSerial;        /*RX, TX connected to BT module*/

/*defining serial port for bluetooth module and setting the baudrate*/
void bluetooth_uart_set (uint32_t baud_rate)
{
  altSerial.begin(baud_rate);
}

/*returning the number of available bytes in serial buffer*/
uint8_t bluetooth_buffer_status ()
{
  return altSerial.available();
}

/*reading the serial buffer into input_string[] with predefined length*/
void bluetooth_buffer_read (uint8_t *input_string, uint8_t string_length)
{
  for (uint8_t index = 0; index < string_length; index++)
  {
    input_string[index] = altSerial.read();
  }
}

/*function to send one byte through bluetooth serial port*/
void bluetooth_send_byte (uint8_t input_byte)
{
  altSerial.write(input_byte);
}

/*delay function inn milliseconds*/
void delay_function (uint32_t delay_ms)
{
  delay(delay_ms);
}
