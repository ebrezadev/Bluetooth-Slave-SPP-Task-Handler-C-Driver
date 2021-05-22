/*task handler for jdy_31 bluetooth slave module*/
/*version 1.0*/
/*Reza Ebrahimi https://github.com/ebrezadev */
#include "jdy_slave.h"

enum tasks {TASK_0, TASK_1, TASK_2, TASK_3};       /*fill this with desired task names, preferably TASK_0, TASK_1 and so on. filled with 4 tasks as ann example*/

/*fill switch statement tasks with desired tasks*/
void task_switcher(uint8_t index)
{
  switch (index)
  {
    case TASK_0:
      
      break;
    case TASK_1:
      
      break;
    case TASK_2:
      
      break;
    case TASK_3:
      
      break;
    default:
      break;
  }
}
