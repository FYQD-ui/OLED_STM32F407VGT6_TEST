#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* 定义 SG90 舵机的角度范围（单位：度）
   这里以中位 90° 为中心，左右极限分别取 45° 和 135°，
   即总摆动范围为 90° */
#define SERVO_MIN_ANGLE   45.0f   // 左侧极限
#define SERVO_MAX_ANGLE   135.0f  // 右侧极限
#define SERVO_NEUTRAL     90.0f   // 中位
#define SERVO_STEP        2.0f    // 每步改变的角度（单位：度）
#define SERVO_DELAY_MS    200     // 每步延时（单位：毫秒）

/**
  * @brief  根据目标角度设置指定 PWM 通道的脉宽，从而控制 SG90 舵机转动
  * @param  htim: 定时器句柄指针
  * @param  channel: PWM 通道，例如 TIM_CHANNEL_1
  * @param  Angle: 目标角度（单位：度），范围 0~180
  * @note   此处采用线性映射：脉宽 = Angle/180 * 2000 + 500 （单位：微秒）
  */
void servo_set(TIM_HandleTypeDef* htim, uint32_t channel, float Angle);

/**
  * @brief  对指定舵机通道进行来回90°转动测试
  *         测试流程：
  *         - 先将舵机置于中位（90°），延时等待归位
  *         - 从中位平滑转到右侧极限（135°），再平滑返回中位
  *         - 从中位平滑转到左侧极限（45°），再平滑返回中位
  * @param  htim: 定时器句柄指针
  * @param  channel: PWM 通道，例如 TIM_CHANNEL_1
  */
void test_servo(TIM_HandleTypeDef* htim, uint32_t channel);

/**
  * @brief  依次测试所有配置的舵机 PWM 通道
  *         测试顺序为：TIM1_CH1、TIM2_CH2、TIM3_CH1、TIM3_CH2、TIM3_CH3、TIM3_CH4、
  *         TIM4_CH3、TIM4_CH4，每一路测试完成后延时 500ms。
  */
void Servo_Test_All(void);

#ifdef __cplusplus
}
#endif

#endif /* SERVO_TEST_H */
