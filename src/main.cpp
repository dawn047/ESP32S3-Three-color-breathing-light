#include <Adafruit_NeoPixel.h>
#include <math.h>

#define NEOPIXEL_PIN 48
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// 呼吸参数配置
const uint16_t BREATHE_INTERVAL = 20;  // 刷新间隔(ms)
const uint16_t CYCLE_DURATION = 3000;  // 单色呼吸周期(ms)

// 函数前置声明
void breatheEffect(uint8_t target_g, uint8_t target_r, uint8_t target_b);

void setup() {
  pixels.begin();
  pixels.setBrightness(80);  // 全局亮度设置
}

void loop() {
  breatheEffect(50, 0, 0);   // 红色呼吸 (G=0, R=255, B=0)
  breatheEffect(0, 50, 0);   // 绿色呼吸 (G=255, R=0, B=0)
  breatheEffect(0, 0, 80);   // 蓝色呼吸 (G=0, R=0, B=255)
}

// 正弦波呼吸效果函数
void breatheEffect(uint8_t target_g, uint8_t target_r, uint8_t target_b) {
  const uint32_t start_time = millis();
  
  while (millis() - start_time < CYCLE_DURATION) {
    float progress = (millis() - start_time) / (float)CYCLE_DURATION;
    float sine_value = sin(progress * PI);  // 0 → π 半周期
    
    // 计算当前颜色强度（非线性渐变）
    uint8_t current_g = target_g * sine_value;
    uint8_t current_r = target_r * sine_value;
    uint8_t current_b = target_b * sine_value;

    // 更新LED颜色
    pixels.setPixelColor(0, pixels.Color(current_g, current_r, current_b));
    pixels.show();
    
    delay(BREATHE_INTERVAL);
  }
}

//本代码实现了一个简单的RGB LED呼吸灯效果，通过正弦波函数实现非线性渐变，使得呼吸灯效果更加柔和。