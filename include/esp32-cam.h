#include "esp_camera.h"

class Camera {
 private:
    static void warmup();
    static camera_config_t config;
    
 public:
    static int configure(int fb_max, int quality, bool greyscale, framesize_t framesize);
    
};
