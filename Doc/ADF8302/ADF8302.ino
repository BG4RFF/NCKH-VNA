int VMAG = A3;     
int VPHS = A4;
                       

long mag = 0;         
long phs = 0;


void setup()
{
  analogReference(EXTERNAL);
  Serial.begin(9600);        
}



void loop()
{
  mag = analogRead(VMAG);   
  phs = analogRead(VPHS);

  mag = -30 + mag * 60 / 1024;
  phs = 180 - phs * 180 / 1024;

  Serial.print("Magnitude: ");
  Serial.print(mag);
  Serial.print(" db");

  Serial.print(" || Phase: ");
  Serial.print(phs);
  Serial.println(" Degrees");

  delay(500);
}
