/*task handler for jdy_31 bluetooth slave module*/
/*version 1.0*/
/*Reza Ebrahimi https://github.com/ebrezadev */
#ifndef JDY_SLAVE_H
#define JDY_SLAVE_H

enum commands {VERSION, RESET, DISCONNECT, MAC_REPORT, PIN_REPORT, PIN_CHANGE, BAUD_REPORT, BAUD_CHANGE, NAME_REPORT, NAME_CHANGE, DEFAULT_SETTING};

/*IMPORTANT: the first predefined task KEY, all other keys are incremental values starting from TASK_COMMAND_STARTER. master must send these keys which correspond to different tasks*/
#define TASK_COMMAND_STARTER                0X10        
#define NUMBER_OF_TASKS                     4       /*define number of tasks, for example 4*/

#define DEFAULT_BAUD_RATE_INDEX             0
#define NUMBER_OF_BAUD_RATES                6
#define MAX_LENGTH_OF_STRING                50        /*maximum length of our internal temporary string*/
#define STARTING_DELAY                      250
#define DISCONNECT_DELAY_MS                 100
#define RESET_DELAY_MS                      100

#define NOT_EMPTY                           1
#define EMPTY                               0

#define ATCOMMAND_LENGTH_VERSION            13
#define ATCOMMAND_LENGTH_DEFAULT_SETTING    13 
#define ATCOMMAND_LENGTH_RESET              11
#define ATCOMMAND_LENGTH_DISCONNECT         10
#define ATCOMMAND_LENGTH_MAC                11
#define ATCOMMAND_LENGTH_PIN                9
#define ATCOMMAND_LENGTH_BAUD               10
#define ATCOMMAND_LENGTH_NAME               10
#define ATCOMMAND_LENGTH_BAUD_CHANGE        10
#define ATCOMMAND_LENGTH_NAME_CHANGE        10
#define ATCOMMAND_LENGTH_PIN_CHANGE         9

void bluetooth_slave_init();
void bluetooth_command (uint8_t command);
void bluetooth_buffer_flush();
void bluetooth_receive_string (uint8_t *input_string, uint8_t string_length);
void bluetooth_send_string (uint8_t *output_string, uint8_t string_length);
void bluetooth_tasks_handler();

void bluetooth_uart_set (uint32_t baud_rate);
uint8_t bluetooth_buffer_status ();
void bluetooth_buffer_read (uint8_t *input_string, uint8_t string_length);
void bluetooth_send_byte (uint8_t input_byte);
void delay_function (uint32_t delay_ms);

void task_switcher(uint8_t index);

#endif
