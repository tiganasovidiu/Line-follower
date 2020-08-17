#include "QTRSensors.h"

#define NUM_SENSORS                   6     // number of sensors used
#define NUM_SAMPLES_PER_SENSOR        4  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN                   QTR_NO_EMITTER_PIN     // emitter is controlled by digital pin 2


QTRSensorsAnalog qtra((unsigned char[]) {
  0, 1, 2, 3, 4, 5}
  ,
NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];

void setup()
{
  delay(100);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    
  for (int i = 0; i < 400; i++)  
  {
    qtra.calibrate();       
  }
  digitalWrite(13, LOW);     

  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
 
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(100);
}


void loop()
{
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int position = qtra.readLine(sensorValues);

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(); // uncomment this line if you are using raw values
  //Serial.println(position); // comment this line out if you are using raw values

  delay(1000);
}

