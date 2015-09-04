#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 2
#define led_blue 11
#define led_yellow 12
#define led_red 13
#define upper_blue 35
#define upper_yellow 75
#define light_in A0
#define light_boundary 500

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
 
void setup(void){

  pinMode(led_blue, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(light_in, INPUT);
  
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  sensors.begin();
}
 
 
void loop(void){
  int integer_temperature;
  int lightValue = analogRead(light_in);

  if(lightValue > light_boundary){
    Serial.print(" Requesting temperatures...");
    sensors.requestTemperatures(); // Send the command to get temperatures
    Serial.println("DONE");
  
    Serial.print("Temperature for Device 1 is: ");
    Serial.print(sensors.getTempCByIndex(0));
    
    integer_temperature = sensors.getTempCByIndex(0);
    onLed(integer_temperature);
  }
  else{
    offLed();
  }
 
  delay(200); 
}

void offLed(){
  
  digitalWrite(led_blue,LOW);
  digitalWrite(led_yellow,LOW);
  digitalWrite(led_red,LOW);
  
}

void onLed(int temperature){
  
  if(temperature >= 0 && temperature < upper_blue ){
    
    digitalWrite(led_blue, HIGH);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_red, LOW);
  }
  else if( temperature >= upper_blue && temperature < upper_yellow){
    
    digitalWrite(led_blue, LOW);
    digitalWrite(led_yellow, HIGH);
    digitalWrite(led_red, LOW);
  }
  else if( temperature >= upper_yellow){
    
    digitalWrite(led_blue, LOW);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_red, HIGH);
  }
}
