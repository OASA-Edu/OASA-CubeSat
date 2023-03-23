#include <Wire.h>

#define SLAVE_ADDR             8
#define BATTERY_VOLTAGE_PIN   A0
#define LIGHT_SENSOR1_PIN     A1
#define LIGHT_SENSOR2_PIN     A2
#define LIGHT_SENSOR3_PIN     A3
#define LIGHT_SENSOR4_PIN     A6
#define SOLENOID_PIN           7
#define MOTOR_PWM_PIN          3
#define MOTOR_IN1_PIN          5
#define MOTOR_IN2_PIN          6


// Hint : initial all variables 
unsigned long prev_t = 0; // previous time
unsigned long control_time = 50;  // run every ms 
unsigned long solenoid_t = 0;
const unsigned long solenoid_timer = 200; // solenoid active duration
bool start_solenoid_timer = false;

byte battery_voltage_sensor = 0;
byte light_sensor1 = 0;
byte light_sensor2 = 0;
byte light_sensor3 = 0;
byte light_sensor4 = 0;
bool motor_dir = true;
int motor_spd = 0;
bool is_deploy = false;
bool is_light_track = false;

void setup() {
  Serial.begin(115200);
  Wire.begin(SLAVE_ADDR); // join i2c bus with defined address
  Wire.onRequest(requestEvent); // trigger function when request by master
  Wire.onReceive(receiveEvent); // trigger function when data sent from master

  pinMode(SOLENOID_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  pinMode(MOTOR_IN1_PIN,OUTPUT);
  pinMode(MOTOR_IN2_PIN,OUTPUT);
}

void loop() {
  unsigned long cur_t = millis();
  if (cur_t - prev_t >= control_time) { // refresh data in every ms 
    prev_t = cur_t;
    battery_voltage_sensor = map(analogRead(BATTERY_VOLTAGE_PIN),0,1023,0,255);
    //TODO: function of configure light read
    
    // store output of light sensor 1 to light_sensor1 and set the range between 0 to 255
    // store output of light sensor 2 to light_sensor2 and set the range between 0 to 255
    // store output of light sensor 3 to light_sensor3 and set the range between 0 to 255
    // store output of light sensor 4 to light_sensor4 and set the range between 0 to 255

    if(is_deploy) {
       //TODO: function when click 'Deploy'
       //Aims: Deploy Cubesat when click 'Deploy' by control solenoid
       
       // set solenoid pin to high
       // if solenoid not activate yet (Hint: status of start_solenoid_timer) -> 
       // return solenoid_t is equal to current time
       // and then start to count solenoid time (Hint: status of start_solenoid_timer )
      
       //if solenoid activated and solenoid active duration >= default solenoid active duration (solenoid_timer) ->
       //then set solenoid pin to low
       // and then set is_deploy flag to disable and 
       //and then stop to count solenoid time (Hint: status of start_solenoid_timer )
      
    } 

    if (is_light_track) { 
      //TODO: function when click 'Light Tracking'
      //Aims: Tracking light source and rotate Cubesat front to light source
      
      //Hint : return max value between 1/2 LIGHT SENSOR 
      //Hint : return max value between 3/4 LIGHT SENSOR 
      //Hint : threshold to rotate the CubeSat
      //Hint : speed of rotate the CubeSat
      //Hint : if left side brighter -> turn left
      //Hint : if right side brighter -> turn right
      //Hint : else -> stay
      }
    
}}

void requestEvent() {
  Wire.write(battery_voltage_sensor);
  Wire.write(light_sensor1);
  Wire.write(light_sensor2);
  Wire.write(light_sensor3);
  Wire.write(light_sensor4);
}

void receiveEvent(int howMany) {
  while (Wire.available() > 1) {
    char c = Wire.read();
    switch (c) {
      case '!':
        Serial.println("Deploy!");
        is_deploy = true;
        break;
      case '^':
        is_light_track = !is_light_track;
        if (!is_light_track) {
          digitalWrite(MOTOR_IN1_PIN, LOW);
          digitalWrite(MOTOR_IN2_PIN, LOW);
          }
        Serial.print("Light tracking: ");
        Serial.println(is_light_track ? "ON" : "OFF");
        break;
      case '+':
        motor_dir = true;
        Serial.print(c);
        break;
      case '-':
        motor_dir = false;
        Serial.print(c);
        break;
    } 
  }
  motor_spd = Wire.read();
  Serial.println(motor_spd);
}
