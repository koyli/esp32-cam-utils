#include <Arduino.h>
#include <esp32-cam.h>

void Camera::warmup() {
    for (int i = 0; i < config.fb_count; ++i)
        {
            camera_fb_t * fb = esp_camera_fb_get();
            esp_camera_fb_return(fb);
            delay(50);
        }
}



// CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

camera_config_t Camera::config;

int Camera::configure(int fb_max, int quality, bool greyscale, framesize_t framesize) {

    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    config.frame_size = FRAMESIZE_UXGA;

    config.jpeg_quality = 6;  //74.5 from 7

    config.fb_count = fb_max + 1;

    // camera init
    esp_err_t cam_err = esp_camera_init(&config);
    if (cam_err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", cam_err);
        return 0;
    }

    delay(100);

    sensor_t * ss = esp_camera_sensor_get();
    ss->set_quality(ss, quality);
    ss->set_framesize(ss, (framesize_t)framesize);
    if (greyscale) {
        ss->set_special_effect(ss, 2);  // 0 regular, 2 grayscale
    } else {
        ss->set_special_effect(ss, 0);  // 0 regular, 2 grayscale
    }
    ss->set_brightness(ss, 1);  //up the blightness just a bit
    ss->set_saturation(ss, -2); //lower the saturation

    warmup();

    return -1;
}

