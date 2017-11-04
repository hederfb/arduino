#include <LiquidCrystal.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#define ONE_WIRE_BUS 7  
#define TEMPERATURE_PRECISION 9  
  
// Setup a oneWire instance to communicate with any OneWire devices  
OneWire oneWire(ONE_WIRE_BUS);  
  
// Pass our oneWire reference to Dallas Temperature.   
DallasTemperature sensors(&oneWire);  
  
int numberOfDevices; // Number of temperature devices found  
DeviceAddress tempDeviceAddress;  

int pinoSensor = A5;
float sensorValue = 0;    
float currentValue = 0;    
float voltsporUnidade = 0.0048875855327468;
float ruido =0.00;


//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  
void setup(void)  
{  

  lcd.begin(16, 2);
  lcd.print("TESTE");
  // start serial port  
  Serial.begin(9600);  

  pinMode(8, OUTPUT);
  pinMode(pinoSensor, INPUT);

  // Start up the library  
  sensors.begin();  
    
  // Grab a count of devices on the wire  
  numberOfDevices = sensors.getDeviceCount();  
    
  // locate devices on the bus  
  Serial.print(numberOfDevices, DEC);  
  
  // Loop through each device, print out address  
  for(int i=0;i<numberOfDevices; i++)  
  {  
    // Search the wire for address  
    if(sensors.getAddress(tempDeviceAddress, i))  
    {  
      Serial.print("Setting resolution to ");  
      Serial.println(TEMPERATURE_PRECISION, DEC);  
    
      // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)  
      sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);  
    
      Serial.print(sensors.getResolution(tempDeviceAddress), DEC);   
      Serial.println();  
    }  
  }
}  
  
// function to print the temperature for a device  
void printTemperature(DeviceAddress deviceAddress)  
{  
  float tempC = sensors.getTempC(deviceAddress);  
  Serial.print("Temp C: ");  
  Serial.println(tempC);

}  
  
void loop(void)  
{ 
  lcd.print("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
  float tempC;  
  // call sensors.requestTemperatures() to issue a global temperature   
  // request to all devices on the bus  
  sensors.requestTemperatures(); // Send the command to get temperatures  
    
    
  // Loop through each device, print out temperature data  
  for(int i=0;i<numberOfDevices; i++)  
  {  
    // Search the wire for address  
    if(sensors.getAddress(tempDeviceAddress, i))  
    {  
      // Output the device ID  
      //Serial.println(i,DEC);  
    
      // It responds almost immediately. Let's print out the data  
      //printTemperature(tempDeviceAddress); // Use a simple function to print out the data  
      tempC = sensors.getTempC(tempDeviceAddress);  
  
    }   
    //else ghost device! Check your power requirements and cabling     
  }

  Serial.print("Temp C: ");  
  Serial.print(tempC);


  currentValue =0;
  for(int index =0; index<100; index++){
    sensorValue = analogRead(pinoSensor); // le o sensor na pino analogico A0
    sensorValue = (sensorValue -511.2)* voltsporUnidade; // ajusta o valor lido para volts começando da metada ja que a saída do sensor é vcc/2 para corrente =0
    currentValue = currentValue +(sensorValue/66)*1000; // a saída do sensor 66 mV por amper
    delay(1);  
}
 
  currentValue = currentValue /100;
  // mostra o resultado no terminal
  Serial.print("corrente = " );      
  currentValue = currentValue- ruido;
  Serial.print(currentValue, 2);  
  Serial.println();

  //Serial.print(" - Potencia (Consumo): ");
  //Serial.print(valorCorrente * tensao);
  //Serial.println("Watts");

  delay(1000);
    
}  
