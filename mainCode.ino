#include <Servo.h> 
#include <SoftwareSerial.h>
#include<Stepper.h>


int pos = 0;    // variable to store the servo position 
int val = 0; // variable to store the value coming from the se
int test = 1;
int ruptPin = 2; // select the input pin for the interrupter
int bluetoothTx = 1;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 0;  // RX-I pin of bluetooth mate, Arduino D3
int positionArray[200];
int pressureArray[200];
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
Servo myservo;
Stepper myStepper = Stepper(200,13,12);

void setup() 
{
  
  Serial.begin(9600); // set up Serial library at 9600 bps
  analogReference(DEFAULT);
  myStepper.setSpeed(15);
  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
}

void loop() {
    int i,j,k,currStep;
    k = 0;
    for(i=0;i<200;i++)
    {
        pressureArray[i] = k;
        k++;
        if( k == 21)
        {
          k = 0;
        }  
    }    
    
    j = 0;  
    myservo.write(j);  
    findZero();
    delay(5000);
    while(1)
    {
        
        k = readPressure();
        for ( j= 0; j < 200;j++)
        {
            adjustMotor(k);         
            myStepper.step(4);
            delay(1000);
            k = readPressure();
        } 
        
           
    }
    

}

void testValve(int pres)
{
      if(pres == 0)
      {
          myservo.write(0);
      }
      else if(pres == 1)
      {
          myservo.write(4);
      }
      else if(pres == 2)
      {
          myservo.write(9);
      }
      else if(pres == 3)
      {
          myservo.write(13);
      }
      else if(pres == 4)
      {
          myservo.write(18);
      }
      else if(pres == 5)
      {
          myservo.write(21);
      }
      else if(pres == 6)
      {
          myservo.write(26);
      }
      else if(pres == 7)
      {
          myservo.write(30);
      }
      else if(pres == 8)
      {
          myservo.write(35);
      }
      else if(pres == 9)
      {
          myservo.write(39);
      }
      else if(pres == 10)
      {
          myservo.write(44);
      }
      else if(pres == 11)
      {
          myservo.write(48);
      }
      else if(pres == 12)
      {
          myservo.write(53);
      }
      else if(pres == 13)
      {
          myservo.write(57);
      }
      else if(pres == 14)
      {
          myservo.write(62);
      }
      else if(pres == 15)
      {
          myservo.write(66);
      }
      else if(pres == 16)
      {
          myservo.write(71);
      }
      else if(pres == 17)
      {
          myservo.write(75);
      }
      else if(pres == 18)
      {
          myservo.write(80);
      }
      else if(pres == 19)
      {
          myservo.write(85);
      }
      else
      {
          myservo.write(90);
      }
      
}      
          
  

/* Steps the stepper motor until the
   motor reaches the zero value */
void findZero()
{
    val = digitalRead(ruptPin);  
    while(val != 0)
    {
        myStepper.step(1);
        delay(15);
        val = digitalRead(ruptPin);
    }
}

/* Reads the current value from the 
   bluetooth sensor*/
void readBluetooth()
{
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    Serial.print((char)bluetooth.read());  
  }
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print((char)Serial.read());
  }
}

/* Adjust the servo motor to match the
   pressure value given */
int adjustMotor(int Pressure)
{
    int currentPressure;
    int currentStep = 0;
    myservo.write(currentStep);
    currentPressure = readPressure();
    while(currentPressure != Pressure)
    {
        if(currentPressure < Pressure)
        {
           currentStep -= 2;
           myservo.write(currentStep);
           delay(15);
        }
        else
        {
           currentStep += 2;
           myservo.write(currentStep);
           delay(15);
        }
    }
}   
           
    

/* Reads from the pressure sensor and 
   returns a value between 0 & 20 */
int readPressure()
{
    int pres,val;
    pres = analogRead(0);
    delayMicroseconds(100);
    if( pres >= 0 && pres <= 47)
    {
        val = 0;
    }
    else if( pres >= 48 && pres <= 95)
    {
        val = 1;
    }
    else if( pres >= 96 && pres <= 143)
    {
        val = 2;
    } 
    else if( pres >= 144 && pres <= 191)
    {
        val = 3;
    } 
    else if( pres >= 192 && pres <= 239)
    {
        val = 4;
    } 
    else if( pres >= 240 && pres <= 288)
    {
        val = 5;
    } 
    else if( pres >= 289 && pres <= 336)
    {
        val = 6;
    } 
    else if( pres >= 337 && pres <= 384)
    {
        val = 7;
    } 
    else if( pres >= 385 && pres <= 432)
    {
        val = 8;
    } 
    else if( pres >= 433 && pres <= 480)
    {
        val = 9;
    } 
    else if( pres >= 481 && pres <= 528)
    {
        val = 10;
    } 
    else if( pres >= 529 && pres <= 576)
    {
        val = 11;
    } 
    else if( 577 >= pres && pres <= 624)
    {
        val = 12;
    } 
    else if( pres >= 625 && pres <= 672)
    {
        val = 13;
    } 
    else if( pres >= 673 && pres <= 720)
    {
        val = 14;
    } 
    else if( pres >= 721 && pres <= 768)
    {
        val = 15;
    } 
    else if( pres >= 769 && pres <= 816)
    {
        val = 16;
    } 
    else if( pres >= 817 && pres <= 864)
    {
        val = 17;
    } 
    else if( pres >= 865 && pres <= 912)
    {
        val = 18;
    } 
    else if( pres >= 913 && pres <= 960)
    {
        val = 19;
    } 
    else
    {
        val = 20;
    }
    
    return val;
}    
