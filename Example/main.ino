/*task handler arduino example for jdy_31 bluetooth slave module*/
/*Reza Ebrahimi https://github.com/ebrezadev */
#include "jdy_slave.h"

void setup() {
  Serial.begin(9600);
  bluetooth_slave_init();       //initializing bluetooth serial port
}

void loop() {
  bluetooth_tasks_handler();        //checking for task commmands
  delay(500);
}
