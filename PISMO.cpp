#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include "DFRobot_EC10.h"
#include "DFRobot_PH.h"
#include <EEPROM.h>



// Declaração do DHT
#define DHTPIN 5          // Definição do pino do DTH
#define DHTTYPE DHT22     // Definição de qual DHT será utilizado, no caso o DHT22
DHT dht(DHTPIN, DHTTYPE); // DHT usando os valores declarados

// Declaração do lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Declaração do Sensor de pH, EC e ORP
#define EC_PIN A1  // Definição do pino do sensor de EC
#define PH_PIN A2  // Definição do pino do sensor de pH
float voltage,ecValue,phValue,temperature = 24;
float t;           // Variável para armazenar a temperatura
DFRobot_EC10 ec;   // EC sensor da DFRobot
DFRobot_PH ph;     // PH sensor da DFRobot


#define VOLTAGE 5.00    //voltagem de referência
#define OFFSET 0        //voltagem de offset
#define LED 13         

double orpValue;
double orp;

#define ArrayLenth  40    //times of collection
#define orpPin 0          //saida analógica do sensor ORP

int orpArray[ArrayLenth];
int orpArrayIndex=0;

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    printf("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}


void setup(void) {
   // Iniciação do lcd
    lcd.init();
    lcd.backlight();
  // Iniciação do DHT
    dht.begin();
  // Iniciação do Sensor de pH
    ph.begin();
  // Iniciação do Sensor de EC
    ec.begin();
  // Iniciação do Serial
    Serial.begin(9600);

  pinMode(LED,OUTPUT);
}

// Função para medir o ORP (Potencial de Oxidação-Redução)
void medidor_opr(){
  static unsigned long orpTimer=millis();   
  static unsigned long printTime=millis();
  if(millis() >= orpTimer)
  {
    orpTimer=millis()+20;
    orpArray[orpArrayIndex++]=analogRead(orpPin);   
    if (orpArrayIndex==ArrayLenth) {
      orpArrayIndex=0;
    }
    orpValue=((30*(double)VOLTAGE*1000)-(75*avergearray(orpArray, ArrayLenth)*VOLTAGE*1000/1023))/75-OFFSET;
    orp = map(orpValue,-3000,2000,-2000,2000);
  
  }
  if(millis() >= printTime)   
  {
    printTime=millis()+800;
    Serial.print("ORP: ");
    Serial.print((int)orp);
    Serial.println("mV");
    lcd.setCursor(0, 1);
    lcd.print("ORP: ");
    lcd.print((int)orp);
    lcd.println("mV");
    digitalWrite(LED,1-digitalRead(LED));
  }
}

// Função para medir a Temperatura
void medidor_temperatura(){
  t = dht.readTemperature();

  delay(1000);
  Serial.print("Temp. = ");
  Serial.println(t);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp. = ");
  lcd.print(t);
  lcd.print(" oC");
}

// Função para medir a Condutividade Elétrica
void medidor_ec(){
    static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U)  //intervalo de tempo: 1s
    {
      timepoint = millis();
      voltage = analogRead(EC_PIN)/1023.0*1.555;   // lê a voltagem
      
      // Ler temperatura do sensor DHT22
      temperature = dht.readTemperature();

      // ecValue =  ec.readEC(voltage,temperature);  // convert voltage to EC with temperature compensation
      ecValue =  voltage;  // convert voltage to EC with temperature compensation

      Serial.print("EC:");
      Serial.print(ecValue,2);
      Serial.println("ms/cm");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("EC: ");
      lcd.print(ecValue,2);
      lcd.println("ms/cm");
    }
    ec.calibration(voltage,temperature); 
}

// Função para medir o pH
void medidor_ph(){
   static unsigned long timepoint = millis();
    if (millis() - timepoint > 1000U) { // Intervalo de tempo: 1s
        timepoint = millis();

        // Ler temperatura do sensor DHT22
        temperature = dht.readTemperature();

        // Ler voltagem do sensor de pH
        voltage = analogRead(PH_PIN) / 1023.0 * 14;

        // Converter voltagem para valor de pH com compensação de temperatura
        phValue = voltage; //Ignorando conpensação de temperatura no simulador
        // phValue = ph.readPH(voltage, temperature); //Conpensação de temperatura para o sensor real

        // Imprimir pH no Monitor Serial
        Serial.print("pH: ");
        Serial.println(phValue, 2);

        // Exibir pH no LCD
        lcd.setCursor(0, 1);
        lcd.print("pH: ");
        lcd.print(phValue, 2);
    }
}

void loop(void) {
  // Chamando as funções
    medidor_temperatura();
    medidor_opr();
    delay(1000);
    medidor_ec();
    medidor_ph();
    delay(100);
}