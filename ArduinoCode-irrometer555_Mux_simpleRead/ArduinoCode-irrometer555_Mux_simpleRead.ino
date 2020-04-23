/*
  Irrometer Sensor circuit with 555 and 74HC7052
  Author: ABHAY S BHARADWAJ (abhay.bharadwaj@wolkus.com)
  THE SOFTWARE FILES ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE AND OR HARDWARE.
*/
#define swpfrequencyInputPin 6 // D6 of Arduino
#define muxS0 4 // D4 of Arduino
#define muxS1 5 // D5 of Arduino
#define sensorPowerEnablePin 7 //D7 of Arduino

void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  pinMode(swpfrequencyInputPin, INPUT);
  pinMode(muxS0, OUTPUT);
  pinMode(muxS1, OUTPUT);
  pinMode(sensorPowerEnablePin, OUTPUT);
  digitalWrite(muxS0, LOW);
  digitalWrite(muxS1, LOW);
  digitalWrite(sensorPowerEnablePin, LOW); //switch off by default
}

void loop()
{
  getData();
  delay(10000);
}

void getData()
{
  digitalWrite(sensorPowerEnablePin, HIGH);//switch ON sensor
  delay(100);
  /****** Irrometer-1 *******/
  float irrometerfrequencyTemp1 = readIrro(1);
  Serial.println("Primary Soil Moisture = " + String(irrometerfrequencyTemp1) + " Hz");
  /*******************************************************************/
  /****** Irrometer-2 *******/
  float irrometerfrequencyTemp2 = readIrro(2);
  Serial.println("Secondary Soil Moisture = " + String(irrometerfrequencyTemp2) + " Hz");
  /*******************************************************************/
  /****** Irrometer-3 *******/
  float irrometerfrequencyTemp3 = readIrro(3);
  Serial.println("Primary Soil Moisture = " + String(irrometerfrequencyTemp3) + " Hz");
  /*******************************************************************/
  /****** Irrometer-4 *******/
  float irrometerfrequencyTemp4 = readIrro(4);
  Serial.println("Secondary Soil Moisture = " + String(irrometerfrequencyTemp4) + " Hz");
  /*******************************************************************/
  digitalWrite(sensorPowerEnablePin, LOW);//switch off sensor
}

float readIrro(int a)
{
  delay(2000);
  if (a == 1)
  {
    digitalWrite(muxS1, LOW);
    digitalWrite(muxS0, LOW);
  }
  else if (a == 2)
  {
    digitalWrite(muxS1, LOW);
    digitalWrite(muxS0, HIGH);
  }
  else if (a == 3)
  {
    digitalWrite(muxS1, HIGH);
    digitalWrite(muxS0, LOW);
  }
  else if (a == 4)
  {
    digitalWrite(muxS1, HIGH);
    digitalWrite(muxS0, HIGH);
  }

  delay(1000);
  float totalTime = 0;
  int highPulseTime = 0, lowPulseTime = 0;
  float irrometerfrequencyTemp, frequencyTemp, freqCummulative = 0;
  int sample = 10;
  for (int i = 0; i < sample; i++) //take 10 samples of readings
  {
    highPulseTime = 0, lowPulseTime = 0, totalTime = 0;
    highPulseTime = pulseIn(swpfrequencyInputPin, HIGH);
    lowPulseTime = pulseIn(swpfrequencyInputPin, LOW);
    totalTime = highPulseTime + lowPulseTime;
    if (totalTime <= 0)
    {
      totalTime = 1000000;
    }
    frequencyTemp = 1000000 / totalTime;
    freqCummulative += frequencyTemp;
    delay(10);
  }
  irrometerfrequencyTemp = freqCummulative / sample;
  return irrometerfrequencyTemp;
}
