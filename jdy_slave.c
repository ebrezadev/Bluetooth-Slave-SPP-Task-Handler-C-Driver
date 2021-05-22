/*task handler for jdy_31 bluetooth slave module*/
/*version 1.0*/
/*Reza Ebrahimi https://github.com/ebrezadev */
#include "jdy_slave.h"

uint8_t temporary_string[MAX_LENGTH_OF_STRING];       /*character array container for receiving strings*/
static uint16_t current_pin;        /*current PIN code for bluetooth module*/
static const uint32_t baud_rates[NUMBER_OF_BAUD_RATES] = {9600, 19200, 38400, 57600, 115200, 128000};       /*array of all possible baud rates for bluetooth module*/
static uint8_t current_baud_rate_index;       /*index of current baud rate, works with baud_rates[index]*/
static uint8_t predefined_task[NUMBER_OF_TASKS];

/*start of all AT commands of bluetooth module*/
const uint8_t ATCommandVersion[ATCOMMAND_LENGTH_VERSION] = "AT+VERSION\r\n\0";
const uint8_t ATCommandReset[ATCOMMAND_LENGTH_RESET] = "AT+RESET\r\n\0";
const uint8_t ATCommandDisconnect[ATCOMMAND_LENGTH_DISCONNECT] = "AT+DISC\r\n\0";
const uint8_t ATCommandMAC[ATCOMMAND_LENGTH_MAC] = "AT+LADDR\r\n\0";
const uint8_t ATCommandPIN[ATCOMMAND_LENGTH_PIN] = "AT+PIN\r\n\0";
const uint8_t ATCommandBaud[ATCOMMAND_LENGTH_BAUD] = "AT+BAUD\r\n\0";
const uint8_t ATCommandName[ATCOMMAND_LENGTH_NAME] = "AT+NAME\r\n\0";
const uint8_t ATCommandPINChange[ATCOMMAND_LENGTH_PIN_CHANGE] = "AT+PIN\r\n\0";
const uint8_t ATCommandBaudChange[ATCOMMAND_LENGTH_BAUD_CHANGE] = "AT+BAUD\r\n\0";
const uint8_t ATCommandNameChange[ATCOMMAND_LENGTH_NAME_CHANGE] = "AT+NAME\r\n\0";
const uint8_t ATCommandDefault[ATCOMMAND_LENGTH_DEFAULT_SETTING] = "AT+DEFAULT\r\n\0";
/*end of all AT commands of bluetooth module*/

static void string_eraser (uint8_t *input_string, uint8_t string_length);

/*setting uart baud rate for JDY-31, filling temporary_string with NULL, disconecting and unpairing. also filling our predefined_task[]*/
void bluetooth_slave_init()
{
  bluetooth_uart_set(baud_rates[DEFAULT_BAUD_RATE_INDEX]);        /*sets the serial port and baud rate to control bluetooth module*/
  delay_function(STARTING_DELAY);       /*needed for settling the serial peripheral*/
  string_eraser(temporary_string, MAX_LENGTH_OF_STRING);        /*filling our temporary string with null*/
  bluetooth_command(DISCONNECT);        /*DISCONECT allows us to send our commands to JDY_31, even if it is in data mode*/
  bluetooth_command(RESET);       /*after turning to commmand mode, RESET will unpair our bluetooth module from any paired master*/
  for (uint8_t index = 0; index < NUMBER_OF_TASKS; index++)       /*filling our tasks array with predefined and incremental command keys*/
  {
    predefined_task[index] = TASK_COMMAND_STARTER + index;
  }
}

/*commands handler (works in command mode, except for DISCONNECT which also works in data mode)*/
void bluetooth_command (uint8_t command)
{
  switch (command)
  {
    case VERSION:
      bluetooth_send_string (ATCommandVersion, ATCOMMAND_LENGTH_VERSION);
      break;
    case RESET:
      bluetooth_send_string (ATCommandReset, ATCOMMAND_LENGTH_RESET);
      delay_function(RESET_DELAY_MS);       /*a delay is needed*/
      break;
    case DISCONNECT:
      bluetooth_send_string (ATCommandDisconnect, ATCOMMAND_LENGTH_DISCONNECT);
      delay_function(DISCONNECT_DELAY_MS);
      break;
    case MAC_REPORT:
      bluetooth_send_string (ATCommandMAC, ATCOMMAND_LENGTH_MAC);
      break;
    case PIN_REPORT:
      bluetooth_send_string (ATCommandPIN, ATCOMMAND_LENGTH_PIN);
      break;
    case PIN_CHANGE:
      bluetooth_send_string (ATCommandPINChange, ATCOMMAND_LENGTH_PIN_CHANGE);
      break;
    case BAUD_REPORT:
      bluetooth_send_string (ATCommandBaud, ATCOMMAND_LENGTH_BAUD);
      break;
    case BAUD_CHANGE:
      bluetooth_send_string (ATCommandBaudChange, ATCOMMAND_LENGTH_BAUD_CHANGE);
      break;
    case NAME_REPORT:
      bluetooth_send_string (ATCommandName, ATCOMMAND_LENGTH_NAME);
      break;
    case NAME_CHANGE:
      bluetooth_send_string (ATCommandNameChange, ATCOMMAND_LENGTH_NAME_CHANGE);
      break;
    case DEFAULT_SETTING:
      bluetooth_send_string (ATCommandDefault, ATCOMMAND_LENGTH_DEFAULT_SETTING);
      break;
    default:
      break;
  }
}

/*tasks handler is our main function to call, in order to check for incoming tasks from master and handling them automatically*/
void bluetooth_tasks_handler()
{
  if (bluetooth_buffer_status() != EMPTY)       /*checks our bluetooth serial port buffer for incoming bytes*/
  {
    uint8_t command_string;
    bluetooth_receive_string (&command_string, 1);        /*receiving the incoming bytes ONE BYTE AT A TIME, BECAUSE WE HAVE CONSIDERED OUR TASK KEYS TO BE 1 BYTE*/
    for (uint8_t index = 0; index < NUMBER_OF_TASKS; index++)       /*checking the received task against our predefined task keys. if it was equal, it is passed on to task_switcher*/
    {
      if (command_string == predefined_task[index])
      {
        task_switcher(index);
      }
    }
  }
}

/*function to receive a string with predefined length, after checking buffer status*/
void bluetooth_receive_string (uint8_t *input_string, uint8_t string_length)
{
  string_eraser(input_string, string_length);       /*preparing temporary string to read serial buffer*/

  uint8_t buffer_length = bluetooth_buffer_status();

  bluetooth_buffer_read(input_string, string_length);
}

void bluetooth_buffer_flush()
{
  uint8_t trash_byte;
  while (bluetooth_buffer_status() != EMPTY)
  {
    bluetooth_buffer_read(&trash_byte, 1);
  }
}

/*function to send a string over serial port, could be AT commands or data. stops at NULL or predefined length, whichever happens first*/
void bluetooth_send_string (uint8_t *output_string, uint8_t string_length)
{
 for (uint8_t counter = 0; (counter < string_length) && (*output_string != '\0'); counter++)
  {
    bluetooth_send_byte (*output_string++);
  }
}

/*function to fill out character array with NULL*/
static void string_eraser (uint8_t *input_string, uint8_t string_length)
{
  for (uint8_t index = 0; index < string_length; index++)
    input_string[index] = '\0';
}
