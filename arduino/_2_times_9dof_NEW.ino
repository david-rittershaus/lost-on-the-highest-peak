#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

#include <SPI.h>         
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

#define TCAADDR 0x70

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

unsigned int port1 = 4485;
unsigned int port2 = 4486;
unsigned int port3 = 4487;
unsigned int port4 = 4488;
IPAddress localIp(100, 100, 1, 20); //ip doesn't really matter
byte ip[] = { 100, 100, 1, 20};
IPAddress destIp(255, 255, 255, 255); //to the whole network
EthernetUDP Udp;


/* Assign a unique ID to the sensors */
Adafruit_9DOF                dof   = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel1 = Adafruit_LSM303_Accel_Unified(1);
Adafruit_LSM303_Accel_Unified accel2 = Adafruit_LSM303_Accel_Unified(2);
Adafruit_LSM303_Mag_Unified   mag1   = Adafruit_LSM303_Mag_Unified(3);
Adafruit_LSM303_Mag_Unified   mag2   = Adafruit_LSM303_Mag_Unified(4);
Adafruit_L3GD20_Unified       gyro1  = Adafruit_L3GD20_Unified(5);

float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;

float udpSend[2];

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}


void setup()
{
  Serial.begin(115200);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  Ethernet.begin(mac, ip);
  
  Udp.begin(port1);
  Udp.begin(port2);
  Udp.begin(port3);
  Udp.begin(port4); 
  //Serial.print("Local IP: ");
  //Serial.println(Ethernet.localIP());

  
  /* Initialise the sensors */
  Wire.begin();
  
  tcaselect(1);
  if(!accel1.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
        while(1);
  }
  
    if(!mag1.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    
    while(1);
  }
  
  if(!gyro1.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
   digitalWrite(4, HIGH);
    tcaselect(2);
    if(!accel2.begin())
  {
    /*There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    
    while(1);
  }
   if(!mag2.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    
    while(1);
  }
  
   digitalWrite(5, HIGH);
}

void loop(void)
{
    
  
    /* Get a new sensor event */
  int forceSensor = analogRead(A1);
  Serial.println(forceSensor);
  if (forceSensor == 0) {
    digitalWrite(6, HIGH);
    }
  else {
    
    digitalWrite(6, LOW);
   } 
  Udp.beginPacket(destIp, port1);
  Udp.println("A");
  Udp.println(forceSensor);
  Udp.endPacket();
 
  sensors_event_t event;
  tcaselect(1);
  //accel1.getEvent(&event);
   
     
  sensors_event_t accel1_event;
  sensors_event_t mag1_event;
  sensors_vec_t   orientation;
  
 accel1.getEvent(&accel1_event);
  mag1.getEvent(&mag1_event);
  
  
  dof.fusionGetOrientation(&accel1_event, &mag1_event, &orientation);
  
  Udp.beginPacket(destIp, port2);
  Udp.println("A");
  Udp.println(orientation.pitch);
  Udp.endPacket();
  //dof.magTiltCompensation(SENSOR_AXIS_Z, &mag1_event, &accel1_event);
  
  //Udp.println(orientation.heading);
  gyro1.getEvent(&event);
  Udp.beginPacket(destIp, port3);
  Udp.println("A");
  Udp.println(event.gyro.z);
  Udp.endPacket();
  
  tcaselect(2);
   
  //sensors_event_t accel2_event;
  sensors_event_t mag2_event;
  //sensors_vec_t   orientation;
  
 //accel1.getEvent(&accel2_event);
  
  
  //sensors_event_t mag2_event;
  
  //accel2.getEvent(&event);
  //dof.accelGetOrientation(&event, &orientation);
  
  
  mag2.getEvent(&mag2_event);
  dof.magGetOrientation(SENSOR_AXIS_Z, &mag2_event, &orientation);
  
 
  Udp.beginPacket(destIp, port4);
  Udp.println("A");
  Udp.println(orientation.heading);
  Udp.endPacket();
  //dof.magGetOrientation(SENSOR_AXIS_Y, &mag2_event, &orientation);
  
  //Udp.beginPacket(destIp, port4);
  //Udp.println("A");
  //Udp.println(orientation.heading);
  //Udp.println("Z");
  //Udp.endPacket();
   
  delay(10);
}


