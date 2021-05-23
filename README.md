# Bluetooth Slave JDY-31 SPP (Serial Port Profile) Task Handler C Driver
* version 1.0
* Reza Ebrahimi

This library is written in **portable C**, and is **MCU independent**. JDY-31 is a bluetooth V4.0 SPP slave module. In order to implement it to your MCU of choice, you need to manipulate functions inside jdy_slave.h, jdy_slave_low_level.c and jdy_slave_tasks.c.

An arbitrary number of tasks could be defined by user (256 tasks maximum, theoretically).

Any resemblance to pre-existing code is unintentional.

## GENERAL INFORMATION

JDY-31 SPP bluetooth module, otherwise known as SPP-C, is a bluetooth slave module based on BK3231S Bluetooth SoC by Beken. It supports a total of 8 AT Commands:
AT+VERSION
AT+RESET
AT+DISC
AT+LADDR
AT+PIN
AT+BAUD
AT+NAME
AT+DEFAULT

## HOW TO USE

After configuring low level functions inside jdy_slave_low_level, you need to add your predefined tasks and their names into the case-switch statement inside jdy_slave_tasks.c. Next, add the task names inside the 'enum tasks', and NUMBER_OF_TASKS inside jdy_slave.h. 
Inside your own firmware, use bluetooth_slave_init() to start communicating with SPP module, and bluetooth_tasks_handler() to check for incoming tasks.

## C FUNCTIONS

Functions can be categorized in different levels. Higher level functions use Lower level functions.

LEVEL 1:
* void bluetooth_uart_set (uint32_t baud_rate)
* uint8_t bluetooth_buffer_status ()
* void bluetooth_buffer_read (uint8_t *input_string, uint8_t string_length)
* void bluetooth_send_byte (uint8_t input_byte)
* void delay_function (uint32_t delay_ms)

LEVEL 2:
* void bluetooth_command (uint8_t command)
* void bluetooth_buffer_flush()
* void bluetooth_receive_string (uint8_t *input_string, uint8_t string_length)
* void bluetooth_send_string (uint8_t *output_string, uint8_t string_length)
* void task_switcher(uint8_t index)
* static void string_eraser (uint8_t *input_string, uint8_t string_length)

LEVEL 3:
* void bluetooth_tasks_handler()
* void bluetooth_slave_init()
