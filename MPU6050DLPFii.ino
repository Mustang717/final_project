#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Variables for accelerometer and gyroscope data
int16_t ax, ay, az;
int16_t gx, gy, gz;

// Low-pass filter variables
float alpha_acc = 0.2; // Accelerometer weighting factor (adjust as needed)
float alpha_gyro = 0.8; // Gyroscope weighting factor (adjust as needed)
float filtered_acc_x = 0.0;
float filtered_acc_y = 0.0;
float filtered_acc_z = 0.0;
float filtered_gyro_x = 0.0;
float filtered_gyro_y = 0.0;
float filtered_gyro_z = 0.0;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  mpu.initialize();
  
  // Set gyro range to ±500 degrees per second
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
}

void loop() {
  // Read raw data from the MPU6050
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Low-pass filter for accelerometer data
  filtered_acc_x = alpha_acc * ax + (1 - alpha_acc) * filtered_acc_x;
  filtered_acc_y = alpha_acc * ay + (1 - alpha_acc) * filtered_acc_y;
  filtered_acc_z = alpha_acc * az + (1 - alpha_acc) * filtered_acc_z;

  // Low-pass filter for gyroscope data
  filtered_gyro_x = alpha_gyro * gx + (1 - alpha_gyro) * filtered_gyro_x;
  filtered_gyro_y = alpha_gyro * gy + (1 - alpha_gyro) * filtered_gyro_y;
  filtered_gyro_z = alpha_gyro * gz + (1 - alpha_gyro) * filtered_gyro_z;

  // Output the filtered data
  Serial.print("Filtered Acceleration (X): ");
  Serial.println(filtered_acc_x);
  Serial.print("Filtered Acceleration (Y): ");
  Serial.println(filtered_acc_y);
  Serial.print("Filtered Acceleration (Z): ");
  Serial.println(filtered_acc_z);
  Serial.print("Filtered Gyro (X): ");
  Serial.println(filtered_gyro_x);
  Serial.print("Filtered Gyro (Y): ");
  Serial.println(filtered_gyro_y);
  Serial.print("Filtered Gyro (Z): ");
  Serial.println(filtered_gyro_z);

  // Add a delay to control the loop rate (adjust as needed)
  delay(10);
}
