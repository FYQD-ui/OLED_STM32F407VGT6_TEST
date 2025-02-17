#include "servo_test.h"
#include "tim.h"

/**
  * @brief  根据目标角度设置指定 PWM 通道的脉宽，从而控制 SG90 舵机转动
  * @param  htim: 定时器句柄指针
  * @param  channel: PWM 通道，例如 TIM_CHANNEL_1
  * @param  Angle: 目标角度（单位：度），范围 0~180
  */
void servo_set(TIM_HandleTypeDef* htim, uint32_t channel, float Angle)
{
    uint32_t pulse;
    /* 将角度线性映射到脉宽：
       当 Angle = 0° 时，pulse = 500us；
       当 Angle = 180° 时，pulse = 2500us；
       公式：pulse = (Angle / 180) * 2000 + 500 */
    pulse = (uint32_t)((Angle / 180.0f) * 2000.0f + 500.0f);
    __HAL_TIM_SetCompare(htim, channel, pulse);
}

/**
  * @brief  对指定舵机通道进行来回90°转动测试
  *         测试流程：
  *         - 设置为中位（90°），延时等待
  *         - 从中位平滑转到右侧极限（135°），再返回中位
  *         - 从中位平滑转到左侧极限（45°），再返回中位
  * @param  htim: 定时器句柄指针
  * @param  channel: PWM 通道，例如 TIM_CHANNEL_1
  */
void test_servo(TIM_HandleTypeDef* htim, uint32_t channel)
{
    float angle;
    
    // 归位到中位
    servo_set(htim, channel, SERVO_NEUTRAL);
    HAL_Delay(SERVO_DELAY_MS);
    
    // 从中位平滑转到右侧极限（90° -> 135°）
    for(angle = SERVO_NEUTRAL; angle <= SERVO_MAX_ANGLE; angle += SERVO_STEP)
    {
        servo_set(htim, channel, angle);
        HAL_Delay(SERVO_DELAY_MS);
    }
    // 平滑返回中位（135° -> 90°）
    for(angle = SERVO_MAX_ANGLE; angle >= SERVO_NEUTRAL; angle -= SERVO_STEP)
    {
        servo_set(htim, channel, angle);
        HAL_Delay(SERVO_DELAY_MS);
    }
    
    // 从中位平滑转到左侧极限（90° -> 45°）
    for(angle = SERVO_NEUTRAL; angle >= SERVO_MIN_ANGLE; angle -= SERVO_STEP)
    {
        servo_set(htim, channel, angle);
        HAL_Delay(SERVO_DELAY_MS);
    }
    // 平滑返回中位（45° -> 90°）
    for(angle = SERVO_MIN_ANGLE; angle <= SERVO_NEUTRAL; angle += SERVO_STEP)
    {
        servo_set(htim, channel, angle);
        HAL_Delay(SERVO_DELAY_MS);
    }
}

/**
  * @brief  依次测试所有配置的舵机 PWM 通道
  *         测试顺序为：
  *           TIM1_CH1, TIM2_CH2, TIM3_CH1, TIM3_CH2, TIM3_CH3, TIM3_CH4, TIM4_CH3, TIM4_CH4
  */
void Servo_Test_All(void)
{
    // 测试 TIM1_CH1（PA8）
    test_servo(&htim1, TIM_CHANNEL_1);
    HAL_Delay(500);
    
    // 测试 TIM2_CH2（PA1）
    test_servo(&htim2, TIM_CHANNEL_2);
    HAL_Delay(500);
    
    // 测试 TIM3 的各通道（PC6~PC9）
    test_servo(&htim3, TIM_CHANNEL_1);
    HAL_Delay(500);
    
    test_servo(&htim3, TIM_CHANNEL_2);
    HAL_Delay(500);
    
    test_servo(&htim3, TIM_CHANNEL_3);
    HAL_Delay(500);
    
    test_servo(&htim3, TIM_CHANNEL_4);
    HAL_Delay(500);
    
    // 测试 TIM4 的通道（PB8、PB9）
    test_servo(&htim4, TIM_CHANNEL_3);
    HAL_Delay(500);
    
    test_servo(&htim4, TIM_CHANNEL_4);
    HAL_Delay(500);
}
