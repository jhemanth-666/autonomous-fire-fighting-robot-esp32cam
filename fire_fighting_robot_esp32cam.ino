/*************************************************
 Autonomous Fire Fighting Robot using ESP32-CAM
 Author: Hemanth Prasad Juttiga
*************************************************/

#include "esp_camera.h"

// ---------------- PIN DEFINITIONS ----------------
#define FLAME_SENSOR 13
#define PUMP 12

#define IN1 14
#define IN2 15
#define IN3 2
#define IN4 4

// ---------------- CAMERA CONFIG ------------------
camera_config_t config;

// ---------------- SETUP --------------------------
void setup() {
  Serial.begin(115200);

  pinMode(FLAME_SENSOR, INPUT);
  pinMode(PUMP, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(PUMP, LOW);

  initCamera();

  Serial.println("🔥 Fire Fighting Robot Ready");
}

// ---------------- LOOP ---------------------------
void loop() {
  int fire = digitalRead(FLAME_SENSOR);

  if (fire == LOW) {   // Fire detected
    Serial.println("🔥 Fire Detected!");

    stopRobot();
    delay(500);

    digitalWrite(PUMP, HIGH);  // Pump ON
    delay(3000);
    digitalWrite(PUMP, LOW);   // Pump OFF

  } else {
    moveForward();
    Serial.println("No Fire - Moving Forward");
  }
}

// ---------------- MOTOR FUNCTIONS ----------------
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ---------------- CAMERA INIT --------------------
void initCamera() {
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = 5;
  config.pin_d1       = 18;
  config.pin_d2       = 19;
  config.pin_d3       = 21;
  config.pin_d4       = 36;
  config.pin_d5       = 39;
  config.pin_d6       = 34;
  config.pin_d7       = 35;
  config.pin_xclk     = 0;
  config.pin_pclk     = 22;
  config.pin_vsync    = 25;
  config.pin_href     = 23;
  config.pin_sccb_sda = 26;
  config.pin_sccb_scl = 27;
  config.pin_pwdn     = 32;
  config.pin_reset    = -1;

  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.println("❌ Camera Init Failed");
  } else {
    Serial.println("📷 Camera Initialized");
  }
}
