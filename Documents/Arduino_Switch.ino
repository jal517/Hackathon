 /*
  Copyright (c) 2015 Intel Corporation. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-
  1301 USA
*/


#include <CurieBLE.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;
const int ledPin = 7; // set ledPin to use on-board LED
const int ledPinn = 6; // set ledPin to use on-board LED
BLEPeripheral blePeripheral; // create peripheral instance
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorPin2 = A3;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor
int counter = 0;
int counter2 = 0;

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // create service

// create switch characteristic and allow remote device to read and write
BLECharCharacteristic switchChar("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // use the LED on pin 7 as an output
  pinMode(ledPinn, OUTPUT); // use the LED on pin 7 as an output

  // set the local name peripheral advertises
  blePeripheral.setLocalName("Arduino 101 -3684");
  // set the UUID for the service this peripheral advertises
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

  // add service and characteristic
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(switchChar);

  // assign event handlers for connected, disconnected to peripheral
  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // assign event handlers for characteristic
  switchChar.setEventHandler(BLEWritten, switchCharacteristicWritten);
// set an initial value for the characteristic
  switchChar.setValue(0);

  // advertise the service
  blePeripheral.begin();
  Serial.println(("Bluetooth device active, waiting for connections..."));
}

void loop() {
  // poll peripheral
  blePeripheral.poll();
  sensorValue = analogRead(sensorPin);
  sensorValue2 = analogRead(sensorPin2);
  if (sensorValue2 > 500)
  {
    if (counter == 0)
    {
      counter = 1;
    }
    else
    {
      counter = 0;
    }
  }
  else
  {
    
  }
  
  if (sensorValue > 500)
  {
    counter2 = 1;
  
  }
  else
  {
    counter2 = 0;
  }
  
  if (counter == counter2)
  {
    digitalWrite(ledPinn, LOW);
  }
  else
  {
    digitalWrite(ledPinn, HIGH);
  }
  
  delay(200);
}

void blePeripheralConnectHandler(BLECentral& central) {
  // central connected event handler
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLECentral& central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
}

void switchCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // central wrote new value to characteristic, update LED
  Serial.print("Characteristic event, written: ");
  Serial.println(switchChar.value());
  if (switchChar.value()) {
     digitalWrite(7, HIGH);      
  } else {
     digitalWrite(7, LOW);   
  }
}
