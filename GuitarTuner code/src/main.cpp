#include "arduinoFFT.h"
 
#define SAMPLES 128             //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 2048 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.
#define SCL_FREQUENCY 0x02

const double Cor = 0.98;
static const uint8_t NotenPins[] = {PD2, A5, A4, A3, A2, A1};

const double FreqE2 = 82.41;
const double FreqA2 = 110.00;
const double FreqD3 = 146.83;
const double FreqG3 = 196.00;
const double FreqH3 = 246.94;
const double FreqE4 = 329.63;



const double LowerFac = 0.92;
const double HigherFac = 1.08;


arduinoFFT FFT = arduinoFFT();
 
unsigned int samplingPeriod;
unsigned long microSeconds;
 
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values

void LEDaus(){
  for(int i = 0; i<6; i++){
    digitalWrite(NotenPins[i], LOW);
  }
}

void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType){
      for (uint16_t i = 0; i < bufferSize; i++){
        double abscissa;
        abscissa = ((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES);
        Serial.print(abscissa, 2);
        if(scaleType==SCL_FREQUENCY)
          Serial.print("Hz");
        Serial.print(" ");
        Serial.println(vData[i], 4);
      }
      Serial.println();
}

void setup() 
{
    pinMode(A5, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(PD2, OUTPUT);
    Serial.begin(115200); //Baud rate for the Serial Monitor
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
    pinMode(A0, INPUT);
}
 
void loop() 
{  
    /*Sample SAMPLES times*/
    for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script. 
     
        vReal[i] = analogRead(A0); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
        vImag[i] = 0; //Makes imaginary term 0 always

        /*remaining wait time between samples if necessary*/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
 
    /*Perform FFT on samples*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);


    
    /*Find peak frequency and print peak*/
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    if(peak > 0){
      peak = peak*Cor;
      //LEDs aus
        
      //E2 & E4
      if(LowerFac*FreqE4 < peak && peak < HigherFac*FreqE4){
        // LED aus
        LEDaus();
        digitalWrite(PD2, HIGH);
        digitalWrite(A1, HIGH);
      }
      
      // A2
      else if(LowerFac*FreqA2 < peak && peak < HigherFac*FreqA2){
        // LED aus
        LEDaus();
        digitalWrite(A5, HIGH);
      }
      
      // D3
      else if(LowerFac*FreqD3 < peak && peak < HigherFac*FreqD3){
        // LED aus
        LEDaus();
        digitalWrite(A4, HIGH);
      }
      
      // G3
      else if(LowerFac*FreqG3 < peak && peak < HigherFac*FreqG3){
        // LED aus
        LEDaus();
        digitalWrite(A3, HIGH);
      }
      
      // H3
      else if(LowerFac*FreqH3 < peak && peak < HigherFac*FreqH3){
        // LED aus
        LEDaus();
        digitalWrite(A2, HIGH);
      }
      else{
        LEDaus();
      }
      delay(50);

      PrintVector(vReal, (SAMPLES >> 1), SCL_FREQUENCY);
      delay(5000);
      
      Serial.println(peak);     //Print out the most dominant frequency.
      

      
    }
    
 
    /*Script stops here. Hardware reset required.*/
    //while (1); //do one time
}

