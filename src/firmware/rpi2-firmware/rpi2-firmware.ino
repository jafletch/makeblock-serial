#include <Wire.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <MeOrion.h>

#include "serial_packet.h"
#include "data_packet.h"
#include "config.h"

union{
    byte byteVal[4];
    float floatVal;
    long longVal;
}val;

union{
  byte byteVal[8];
  double doubleVal;
}valDouble;

union{
  byte byteVal[2];
  short shortVal;
}valShort;

char receivebuffer[50];
unsigned char receivelength = 0;

void setup(){
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  delay(300);
  digitalWrite(13,LOW);
  Serial.begin(115200);
  #if defined(__AVR_ATmega32U4__) 
    Serial1.begin(115200);
  #endif
}

void loop(){
  
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    
    receivebuffer[receivelength++] = c;

    if (c == PACKET_LIMIT_MARKER && receivelength > PACKET_MIN_SIZE)
    {
      char databuffer[50];
      unsigned char datalength = 0;
      if (serial_packet::decode_packet(receivebuffer, receivelength, databuffer, &datalength))
      {
        data_packet dp = data_packet::parse(databuffer, datalength);
      }
    }
  }
}


////void parseData(){
////  isStart = false;
////  int idx = readBuffer(3);
////  int action = readBuffer(4);
////  int device = readBuffer(5);
////  switch(action){
////    case GET:{
////        writeHead();
////        writeSerial(idx);
////        readSensor(device);
////        writeEnd();
////     }
////     break;
////     case RUN:{
////       runModule(device);
////       callOK();
////     }
////      break;
////      case RESET:{
////        //reset
////        dc.reset(M1);
////        dc.run(0);
////        dc.reset(M2);
////        dc.run(0);
////        dc.reset(PORT_1);
////        dc.run(0);
////        dc.reset(PORT_2);
////        dc.run(0);
//////        encoders[0].runSpeed(0);
//////        encoders[1].runSpeed(0);
////        callOK();
////      }
////     break;
////     case START:{
////        //start
////        callOK();
////      }
////     break;
////  }
////}
//void callOK(){
//    writeSerial(0xff);
//    writeSerial(0x55);
//    writeEnd();
//}
//void sendByte(char c){
//  writeSerial(1);
//  writeSerial(c);
//}
//void sendString(String s){
//  int l = s.length();
//  writeSerial(4);
//  writeSerial(l);
//  for(int i=0;i<l;i++){
//    writeSerial(s.charAt(i));
//  }
//}
//void sendFloat(float value){ 
//     writeSerial(0x2);
//     val.floatVal = value;
//     writeSerial(val.byteVal[0]);
//     writeSerial(val.byteVal[1]);
//     writeSerial(val.byteVal[2]);
//     writeSerial(val.byteVal[3]);
//}
//void sendShort(double value){
//     writeSerial(3);
//     valShort.shortVal = value;
//     writeSerial(valShort.byteVal[0]);
//     writeSerial(valShort.byteVal[1]);
//     writeSerial(valShort.byteVal[2]);
//     writeSerial(valShort.byteVal[3]);
//}
//void sendDouble(double value){
//     writeSerial(2);
//     valDouble.doubleVal = value;
//     writeSerial(valDouble.byteVal[0]);
//     writeSerial(valDouble.byteVal[1]);
//     writeSerial(valDouble.byteVal[2]);
//     writeSerial(valDouble.byteVal[3]);
//}
//short readShort(int idx){
//  valShort.byteVal[0] = readBuffer(idx);
//  valShort.byteVal[1] = readBuffer(idx+1);
//  return valShort.shortVal; 
//}
//float readFloat(int idx){
//  val.byteVal[0] = readBuffer(idx);
//  val.byteVal[1] = readBuffer(idx+1);
//  val.byteVal[2] = readBuffer(idx+2);
//  val.byteVal[3] = readBuffer(idx+3);
//  return val.floatVal;
//}
//void runModule(int device){
//  //0xff 0x55 0x6 0x0 0x1 0xa 0x9 0x0 0x0 0xa 
//  int port = readBuffer(6);
//  int pin = port;
//  switch(device){
//   case MOTOR:{
//     valShort.byteVal[0] = readBuffer(8);
//     valShort.byteVal[1] = readBuffer(9);
//     int speed = valShort.shortVal;
//     Serial.println(speed);
//     dc.reset(port);
//     if (speed > 0) {
//     dc.run(speed);
//     } else {
//      dc.stop();
//     }
//   } 
//    break;
//    case STEPPER:{
//     valShort.byteVal[0] = readBuffer(7);
//     valShort.byteVal[1] = readBuffer(8);
//     int maxSpeed = valShort.shortVal;
//     valShort.byteVal[0] = readBuffer(9);
//     valShort.byteVal[1] = readBuffer(10);
//     int distance = valShort.shortVal;
//     if(port==PORT_1){
//      steppers[0] = MeStepper(PORT_1);
//      steppers[0].setMaxSpeed(maxSpeed);
//      steppers[0].moveTo(distance);
//     }else if(port==PORT_2){
//      steppers[1] = MeStepper(PORT_2);
//      steppers[1].setMaxSpeed(maxSpeed);
//      steppers[1].moveTo(distance);
//     }
//   } 
//    break;
//    case ENCODER:{
//      valShort.byteVal[0] = readBuffer(7);
//      valShort.byteVal[1] = readBuffer(8);
//      int maxSpeed = valShort.shortVal;
//      valShort.byteVal[0] = readBuffer(9);
//      valShort.byteVal[1] = readBuffer(10);
//      int distance = valShort.shortVal;
//      int slot = port;
////      if(slot==SLOT_1){
////         encoders[0].move(distance,maxSpeed);
////      }else if(slot==SLOT_2){
////         encoders[1].move(distance,maxSpeed);
////      }
//    }
//    break;
//   case RGBLED:{
//     MeRGBLed led;
//     int idx = readBuffer(7);
//     int r = readBuffer(8);
//     int g = readBuffer(9);
//     int b = readBuffer(10);
//     led.reset(port);
//     if(idx>0){
//       led.setColorAt(idx-1,r,g,b); 
//     }else{
//        led.setColor(r,g,b); 
//     }
//     led.show();
//   }
//   break;
//   case SERVO:{
//     int slot = readBuffer(7);
//     pin = slot==1?mePort[port].s1:mePort[port].s2;
//     int v = readBuffer(8);
//     if(v>=0&&v<=180){
//       servo.attach(pin);
//       servo.write(v);
//     }
//   }
//   break;
//   case SEVSEG:{
//     Me7SegmentDisplay seg;
//     if(seg.getPort()!=port){
//       seg.reset(port);
//     }
//     float v = readFloat(8);
//     seg.display(v);
//   }
//   break;
//   case LIGHT_SENSOR:{
//     MeLightSensor ls;
//     if(ls.getPort()!=port){
//       ls.reset(port);
//     }
//     int v = readBuffer(8);
//     if (v) {
//      ls.lightOn();
//     } else {
//      ls.lightOff();
//     }
//   }
//   break;
//   case SHUTTER:{
//     if(generalDevice.getPort()!=port){
//       generalDevice.reset(port);
//     }
//     int v = readBuffer(7);
//     if(v<2){
//       generalDevice.dWrite1(v);
//     }else{
//       generalDevice.dWrite2(v-2);
//     }
//   }
//   break;
//   case DIGITAL:{
//     pinMode(pin,OUTPUT);
//     int v = readBuffer(7);
//     digitalWrite(pin,v);
//   }
//   break;
//   case PWM:{
//     pinMode(pin,OUTPUT);
//     int v = readBuffer(7);
//     analogWrite(pin,v);
//   }
//   break;
//   case SERVO_PIN:{
//     int v = readBuffer(7);
//     if(v>=0&&v<=180){
//       servo.attach(pin);
//       servo.write(v);
//     }
//   }
//   break;
//   case TOUCH_SENSOR: {
//    MeTouchSensor ts;
//     if(ts.getPort()!=port){
//       ts.reset(port);
//     }
//     int v = readBuffer(8);
//     ts.SetTogMode(v);
//   }
//   break;
//   case TIMER:{
//    lastTime = millis()/1000.0; 
//   }
//   break;
//  }
//}
//void readSensor(int device){
//  /**************************************************
//      ff 55 len idx action device port slot data a
//      0  1  2   3   4      5      6    7    8
//  ***************************************************/
//  float value=0.0;
//  int port,slot,pin;
//  port = readBuffer(6);
//  pin = port;
//  switch(device){
//   case  ULTRASONIC_SENSOR:{
//     MeUltrasonicSensor us;
//     if(us.getPort()!=port){
//       us.reset(port);
//     }
//     value = us.distanceCm();
//     sendFloat(value);
//   }
//   break;
//   case  TEMPERATURE_SENSOR:{
//     MeTemperature ts;
//     slot = readBuffer(7);
//     if(ts.getPort()!=port||ts.getSlot()!=slot){
//       ts.reset(port,slot);
//     }
//     value = ts.temperature();
//     sendFloat(value);
//   }
//   break;
//   case  LIGHT_SENSOR:{
//    MeLightSensor ls;
//     if(ls.getPort()!=port){
//       ls.reset(port);
//     }
//     value = ls.read();
//     sendFloat(value);
//     ls.lightOn();
//   }
//   break;
//   case  SOUND_SENSOR:
//   case  POTENTIONMETER:{
//     if(generalDevice.getPort()!=port){
//       generalDevice.reset(port);
//       pinMode(generalDevice.pin2(),INPUT);
//     }
//     value = generalDevice.aRead2();
//     sendFloat(value);
//   }
//   break;
//   case  JOYSTICK:{
//     slot = readBuffer(7);
//     if(generalDevice.getPort()!=port){
//       generalDevice.reset(port);
//       pinMode(generalDevice.pin1(),INPUT);
//       pinMode(generalDevice.pin2(),INPUT);
//     }
//     if(slot==1){
//       value = generalDevice.aRead1();
//       sendFloat(value);
//     }else if(slot==2){
//       value = generalDevice.aRead2();
//       sendFloat(value);
//     }
//   }
//   break;
//   case  INFRARED:{
//     if(ir.getPort()!=port){
//       ir.reset(port);
//     }
//     sendFloat(irRead);
//   }
//   break;
//   case  PIRMOTION:{
//    MePIRMotionSensor pir;
//     if(pir.getPort()!=port){
//       pir.reset(port);
//     }
//     value = pir.isHumanDetected();
//     sendByte(value);
//   }
//   break;
//   case  LINEFOLLOWER:{
//     MeLineFollower lf;
//     if(lf.getPort()!=port){
//       lf.reset(port);
//       //  pinMode(lf.pin1(),INPUT);
//       //  pinMode(lf.pin2(),INPUT);
//     }
//     value = lf.readSensors();
//     sendFloat(value);
//   }
//   break;
//   case LIMITSWITCH:{
//     slot = readBuffer(7);
//     if(generalDevice.getPort()!=port||generalDevice.getSlot()!=slot){
//       generalDevice.reset(port,slot);
//     }
//     if(slot==1){
//       pinMode(generalDevice.pin1(),INPUT_PULLUP);
//       value = generalDevice.dRead1();
//     }else{
//       pinMode(generalDevice.pin2(),INPUT_PULLUP);
//       value = generalDevice.dRead2();
//     }
//     sendFloat(value);  
//   }
//   break;
//   case  GYRO:{
//       MeGyro gyro;
//       int axis = readBuffer(7);
//       gyro.update();
//       if(axis==1){
//         value = gyro.getAngleX();
//         sendFloat(value);
//       }else if(axis==2){
//         value = gyro.getAngleY();
//         sendFloat(value);
//       }else if(axis==3){
//         value = gyro.getAngleZ();
//         sendFloat(value);
//       }
//   }
//   break;
//   case  VERSION:{
//     sendString(mVersion);
//   }
//   break;
//   case  DIGITAL:{
//     pinMode(pin,INPUT);
//     sendFloat(digitalRead(pin));
//   }
//   break;
//   case  ANALOG:{
//     pin = analogs[pin];
//     pinMode(pin,INPUT);
//     sendFloat(analogRead(pin));
//   }
//   break;
//   case TOUCH_SENSOR: {
//     MeTouchSensor ts;
//     if(ts.getPort()!=port){
//       ts.reset(port);
//     }
//     value = ts.touched();
//     sendByte((char)value);
//   }
//   break;
//   case TIMER:{
//     sendFloat((float)currentTime);
//   }
//   break;
//  }
//}
