#ifndef __SERVO_CONTROL_H
#define __SERVO_CONTROL_H

#include "tim.h"

#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180

// 这里只是声明函数，不要定义
void setServoAngle(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t angle);
void robot_walk_forward(void);
void robot_walk_backward(void);
void robot_turn_left(void);
void robot_turn_right(void);
void robot_stop(void);

#endif // __SERVO_CONTROL_H
