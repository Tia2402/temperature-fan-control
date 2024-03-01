#define PIN_RED	9
#define PIN_BLUE 10
#define PIN_GREEN 11
#define PIN_TEMP A0
#define TEMP_OVERFLOW_1 25
#define TEMP_OVERFLOW_2 50
#define PIN_MOTOR 3
#define MAX_TEMP 125

void setup()
{
	DDRB = 0b00001110; // 0X0E pinii 9, 10, 11 de output
  	DDRD = 0b00001000; //0x08 pinul 3 de output
  	Serial.begin(115200);
  	
}

float readTemperature()
{
   // 5/1024 => int value. (float)5 forteaza sa returneze un float
  float voltageValue = analogRead(PIN_TEMP) * ((float)5/1024);
  return (voltageValue-0.5)*100;
}

void setColor(unsigned char r, unsigned char g, unsigned char b)
{
  	analogWrite(PIN_RED, r);
  	analogWrite(PIN_GREEN, g);
  	analogWrite(PIN_BLUE, b);
}
void loop()
{
  	float temperature = readTemperature();
  	Serial.println(temperature);
  	if(temperature < 25)
    	setColor(0, 255, 0); // GREEN
  	else if(temperature < 50)
      	setColor(255, 255, 0); //yellow
    else 
      	setColor(255, 0, 0); //red
    
    if(temperature < 0)
      analogWrite(PIN_MOTOR, 0);
    else
    {
      unsigned char pwmValue = (255 * temperature)/MAX_TEMP; 
      analogWrite(PIN_MOTOR, pwmValue);
    }
    
  	delay(500);
  	
  	
  	
}