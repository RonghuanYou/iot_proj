// Student Name: Ronghuan You (your1)
// ID: 17911682
#define RED_PIN 2
#define YELLOW_PIN 3
#define GREEN_PIN 4

boolean green = false;
boolean yellow = false;
boolean red = false;

#define co2Zero 55 

void setup()
{
  pinMode(A0, INPUT);                           //MQ135 analog feed set for input
  pinMode(RED_PIN,OUTPUT);
  pinMode(YELLOW_PIN,OUTPUT);
  pinMode(GREEN_PIN,OUTPUT);
  Serial.begin(9600);  
}


void loop()
{
  // set up and calibration
  int co2now[10];                               //int array for co2 readings
  int co2raw = 0;                               //int for raw value of co2
  int co2ppm = 0;                               //int for calculated ppm
  int average = 0;                              //int for averaging
  
  for (int x = 0; x<10; x++)                  //samplpe co2 10x over 2 seconds
  {                   
    co2now[x] = analogRead(A0);
    delay(200);
  }

  for (int x = 0; x < 10; x++)                  //add samples together
  {                     
    average += co2now[x];  
  }
  
  co2raw = average/10;                            //divide samples by 10
  co2ppm = co2raw - co2Zero;                      //get calculated ppm
 
  if(co2ppm < 250)
  {
    digitalWrite(GREEN_PIN, HIGH);
    green = true;
    yellow = false;
    red = false;
  }
  
  if (green == true){
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(RED_PIN, LOW);
  }

  if( co2ppm > 210 and co2ppm < 500)
  {
    green = false;
    red = false;
    yellow = true;
  }
  
  if (yellow == true){
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, LOW);
  }

  if( co2ppm > 600)
  {
    red = true;
    green = false;
    yellow = false;
  }

  if (red == true){
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
  }

//  Serial.print("Air quality = "); Serial.print(co2ppm); Serial.println(" PPM");  

  String dataToSend = String(co2ppm);
  Serial.println(dataToSend);
  delay(50);
 

}
