/*
Hot water heater pump

Each time the infrared trigger is tripped the hot water heater pump relay
runs for x seconds and resets

created May 17, 2011
v3 - simplified - 11/18/2011
v4 - added multiple sensors
v5 - added time_of_day_operation function

by Robert Labatt
*/
//includes
  //may need to include some time library for the time_of_day_operation function


//define digital inputs from sensors
int motionSensor_1 = 2;         // infrared sensor #1 - Main Bathroom
int motionSensor_2 = 3;         // infrared sensor #2 - Kids Bathroom
int motionSensor_3 = 4;         // infrared sensor #3 - Kitchen

//define digital outputs connected to relays and signal lights
int relayPin = 7;               // relay that switches the pump
int pumpLed = 13;               // pump in operation LED indicator pin

//decide how long the pump should run and how log between pump cycles
int pumpRun = 2000;             // milli-seconds the pump runs for
int pumpWait = 5000;           // milli-seconds the pump waits between run times

//define variables to store motion and pump values
int motionSensor_1_val;         //master bathroom motion sensor
int motionSensor_2_val;         //kids bathroom motion sensor
int motionSensor_3_val;         //kitchen motion sensor
int relayPin_val;               //pump trigger relay pin
int pumpLed_val;                //pump opertation indicator LED
int time;                       //time of day

// declare functions
void print_status();            //used to print the status of all pins and the pump
void set_all_low();             //sets all pins to low
void pump_status_print();       //prints the pump status to the serial port
void time_of_day_operation();   //used to turn on the pump at a certain time of day (e.g., first thing in the morning)

void setup()
  {
    //open serial port
    Serial.begin(9600);
    
    pinMode (motionSensor_1, INPUT);
    pinMode (motionSensor_2, INPUT);
    pinMode (motionSensor_3, INPUT);
    pinMode (relayPin, OUTPUT);
    pinMode (pumpLed, OUTPUT);
    set_all_low();                //set pins to low initially
  }

void loop() 
  {  
    Serial.println(">>>>>>>>>>>>>>>>>>>");
    
    status();

    Serial.println(">>>>>>>>>>>>>>>>>>>");
    
    // run the pump if any IR sensor has sensed a trigger i.e. it is set to HIGH
    if ( digitalRead(motionSensor_1) || digitalRead(motionSensor_2) || digitalRead(motionSensor_3) == HIGH ) 
    {
      // turn on the pump in operation LED and the pump
      digitalWrite (pumpLed, HIGH);
      digitalWrite (relayPin, HIGH);
      Serial.println("Pump now ON");
      status();
      
      delay (pumpRun);        //leave pump on for set time "pumpRun"
      
      status();

      set_all_low();          //turn off pump, pump in operation LED

      Serial.println("Pump now OFF");
      
      //Serial.print("Pump waiting for water temp decay period of ") & pumpWait/1000 & (" seconds.");
      
      status();

      delay (pumpWait);       //do not turn pump on again until a time period has passed
      
      status();

      Serial.println(">>>>>>>>>>>>>>>>>>>");
    }  
  }

void set_all_low()    //set all pins to low
  {
    digitalWrite (motionSensor_1, LOW);
    digitalWrite (motionSensor_2, LOW);
    digitalWrite (motionSensor_3, LOW);
    digitalWrite (relayPin, LOW);
    digitalWrite (pumpLed, LOW);
  }

void status()    //read the set values and print to screen
  {
    Serial.print("Motion sensor 1 (Master BR) on Pin 2 reads: ");
    Serial.println(digitalRead(motionSensor_1));      
    Serial.print("Motion sensor 2 (Kids BR) on Pin 3 reads: ");
    Serial.println(digitalRead(motionSensor_2));
    Serial.print("Motion sensor 3 (Kitchen) on Pin 4 reads: ");
    Serial.println(digitalRead(motionSensor_3));
    Serial.print("Pump relay reads: ");
    Serial.println(digitalRead(relayPin));
    Serial.print("Pump LED reads: ");
    Serial.println(digitalRead(pumpLed));
    delay (2000);
  }