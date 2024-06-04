#include <OneWire.h>  
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include "DFRobot_EC10.h"
#include "DFRobot_PH.h"
#include "GravityTDS.h"
#include <EEPROM.h>

// Definição do pino do DS
#define dados 5
OneWire oneWire(dados);  //Protocolo OneWire
DallasTemperature sensors(&oneWire); //encaminha referências OneWire para o sensor

// Declaração do lcd
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Declaração EC e pH
#define EC_PIN A1
#define PH_PIN A2
float voltage, ecValue, phValue, temperature = 24;
float t;
float tdsValue = 0;
DFRobot_EC10 ec;
GravityTDS gravityTds;
DFRobot_PH ph;

// Declaração ORP
#define VOLTAGE 5.00  //system voltage
#define OFFSET 0      //zero drift voltage
#define LED 13        //operating instructions

double orpValue;
double orp;

#define ArrayLenth 40
#define orpPin 0

int orpArray[ArrayLenth];
int orpArrayIndex = 0;

unsigned long tempTimer = 0;
unsigned long orpTimer = 0;
unsigned long orpPrint = 0;
unsigned long ecTimer = 0;
unsigned long phTimer = 0;
unsigned long doTimer = 0;
unsigned long tdsTimer = 0;
unsigned long turbTimer = 0;

const unsigned long TEMP_INTERVAL = 2000;
const unsigned long ORP_INTERVAL = 20;
const unsigned long ORP_PRINT = 2000;
const unsigned long EC_INTERVAL = 2000;
const unsigned long PH_INTERVAL = 2000;
const unsigned long DO_INTERVAL = 2000;
const unsigned long TDS_INTERVAL = 2000;
const unsigned long TURB_INTERVAL = 2000;

// Declaração DO
#define VREF 5000    //VREF (mv)
#define ADC_RES 1024 //ADC Resolution

//Single-point calibration Mode=0
//Two-point calibration Mode=1
#define TWO_POINT_CALIBRATION 0

#define READ_TEMP (25) //Current water temperature ℃, Or temperature sensor function

//Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1600) //mv
#define CAL1_T (25)   //℃
#define CAL2_V (1300) //mv
#define CAL2_T (15)   //℃

const uint16_t DO_Table[41] = {
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};

uint8_t Temperaturet;
uint16_t ADC_Raw;
uint16_t ADC_Voltage;
uint16_t DO;

int16_t readDO(uint32_t voltage_mv, uint8_t temperature_c)
{
#if TWO_POINT_CALIBRATION == 0
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperature_c - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#endif
}

// Pinos do CD74HC4067
const int s0 = 12;
const int s1 = 11;
const int s2 = 10;
const int s3 = 9;
const int muxSIG = A3;

// Canais de TDS, DO e Turbidez
const int sensor1Channel = 0; // Conectado ao Y0
const int sensor2Channel = 1; // Conectado ao Y1
const int sensor3Channel = 2; // Conectado ao Y2

double avergearray(int* arr, int number) {
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0) {
    printf("Error number for the array to averaging!/n");
    return 0;
  }
  if (number < 5) {   //less than 5, calculated directly statistics
    for (i = 0; i < number; i++) {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  } else {
    if (arr[0] < arr[1]) {
      min = arr[0]; max = arr[1];
    }
    else {
      min = arr[1]; max = arr[0];
    }
    for (i = 2; i < number; i++) {
      if (arr[i] < min) {
        amount += min;        //arr<min
        min = arr[i];
      } else {
        if (arr[i] > max) {
          amount += max;    //arr>max
          max = arr[i];
        } else {
          amount += arr[i]; //min<=arr<=max
        }
      } //if
    } //for
    avg = (double)amount / (number - 2);
  } //if
  return avg;
}
// Definição dos caracteres personalizados
byte fish4[8] = {
  0b11100,
  0b10010,
  0b01001,
  0b00100,
  0b00100,
  0b00101,
  0b01001,
  0b00110
  };
byte fish2[8] = {
  0b00000,
  0b00011,
  0b01100,
  0b10000,
  0b00000,
  0b11000,
  0b00111,
  0b00000
  };
byte fish3[8] = {
  0b11111,
  0b00000,
  0b00001,
  0b00001,
  0b00000,
  0b01000,
  0b10011,
  0b01100
  };

byte fish1[8] = {
  0b00000,
  0b11000,
  0b00101,
  0b00010,
  0b00010,
  0b00101,
  0b11000,
  0b00000
  };

byte bubbleBig[8] = {
	0b01110,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b01110,
	0b00000,
	0b00000
  };

byte bubbleSS[8] = {
	0b00000,
	0b01000,
	0b10100,
	0b01000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
  };

byte bubble[8] = {
  0b00000,
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b01110,
  0b00000,
  0b00000
  };

byte bubbleSmall[8] = {
	0b00000,
	0b01100,
	0b10010,
	0b10010,
	0b01100,
	0b00000,
	0b00000,
	0b00000
};
void setup(void) {
  // Iniciação do Serial
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
  // Iniciação do DS
    sensors.begin();
  // Iniciação do Sensor de pH
    ph.begin();
  // Iniciação do Sensor de EC
    ec.begin();
  // Iniciação do Sensor de TDS
    gravityTds.setPin(readMux(sensor2Channel));
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1023);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
  // Iniciação do lcd
    lcd.init();
    lcd.backlight();

  // Configuração dos pinos do CD74HC4067
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
  // Cria os caracteres personalizados
    lcd.createChar(0, fish4);
    lcd.createChar(1, fish3);
    lcd.createChar(2, fish2);
    lcd.createChar(3, fish1);
    lcd.createChar(4, bubbleSS);
    lcd.createChar(5, bubbleSmall);
    lcd.createChar(6, bubble);
    lcd.createChar(7, bubbleBig);
}

// Função para selecionar o canal do CD74HC4067
void selectMuxChannel(int channel) {
  digitalWrite(s0, channel & 0x01);
  digitalWrite(s1, channel & 0x02);
  digitalWrite(s2, channel & 0x04);
  digitalWrite(s3, channel & 0x08);
}
// Função para ler o valor do sensor no canal especificado
int readMux(int channel) {
  selectMuxChannel(channel);
  return analogRead(muxSIG);
}
// Função para medir o ORP (Potencial de Oxidação-Redução)
void medidor_opr() {
  if (millis() - orpTimer >= ORP_INTERVAL) {
    orpTimer = millis();
    orpArray[orpArrayIndex++] = analogRead(orpPin);    //read an analog value every 20ms
    if (orpArrayIndex == ArrayLenth) {
      orpArrayIndex = 0;
    }
    orpValue = ((30 * (double)VOLTAGE * 1000) - (75 * avergearray(orpArray, ArrayLenth) * VOLTAGE * 1000 / 1023)) / 75 - OFFSET;
    orp = map(orpValue, -3000, 2000, -2000, 2000);
    //convert the analog value to orp according the circuit

    if (millis() - orpPrint >= ORP_PRINT) {
      orpPrint = millis();
      Serial.print("ORP: ");
      Serial.print((int)orp);
      Serial.println("mV");
      lcd.setCursor(0, 1);
      lcd.print("ORP: ");
      lcd.print((int)orp);
      lcd.print("mV");
      digitalWrite(LED, 1 - digitalRead(LED));
    }
  }
}
// Função para medir a Temperatura
void medidor_temperatura() {
  if (millis() - tempTimer >= TEMP_INTERVAL) {
    tempTimer = millis();
    sensors.requestTemperatures(); // Envia o comando para leitura da temperatura 
    t = sensors.getTempCByIndex(0);

    Serial.print("Temp. = ");
    Serial.println(t);
    lcd.setCursor(0, 0);
    lcd.print("Temp.:");
    lcd.print(t);
    lcd.print("\337C");
  }
}
// Função para medir a Condutividade Elétrica (EC)
void medidor_ec() {
  if (millis() - ecTimer >= EC_INTERVAL) {
    ecTimer = millis();
    voltage = analogRead(EC_PIN) / 1023.0 * 1.555;  // read the voltage

    // Ler temperatura do sensor DHT22
    temperature = sensors.getTempCByIndex(0);

    // ecValue =  ec.readEC(voltage,temperature);  // convert voltage to EC with temperature compensation
    ecValue = voltage;  // convert voltage to EC with temperature compensation

    Serial.print("EC:");
    Serial.print(ecValue, 2);
    Serial.println("ms/cm");
    lcd.setCursor(0, 2);
    lcd.print("EC: ");
    lcd.print(ecValue, 2);
    lcd.print("ms/cm");
    ec.calibration(voltage, temperature);
  }
}
// Função para medir o pH
void medidor_ph() {
  if (millis() - phTimer >= PH_INTERVAL) {
    phTimer = millis();
    // Ler temperatura do sensor DHT22
    temperature = sensors.getTempCByIndex(0);

    // Ler voltagem do sensor de pH
    voltage = analogRead(PH_PIN) / 1023.0 * 14;

    // Converter voltagem para valor de pH com compensação de temperatura
    phValue = voltage;  //Ignorando conpensação de temperatura no simulador
    // phValue = ph.readPH(voltage, temperature); //Conpensação de temperatura para o sensor real

    // Imprimir pH no Monitor Serial
    Serial.print("pH: ");
    Serial.println(phValue, 2);

    // Exibir pH no LCD
    lcd.setCursor(0, 3);
    lcd.print("pH: ");
    lcd.print(phValue, 2);
  }
}
// Função para medir TDS (Sólidos Totais Dissolvidos)
void medidor_TDS() {
  if (millis() - tdsTimer >= TDS_INTERVAL) {
    tdsTimer = millis();
    temperature = sensors.getTempCByIndex(0);
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = (gravityTds.getTdsValue()/7.285);  // then get the value
    Serial.print("TDS: ");
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    lcd.setCursor(0,1);
    lcd.print("TDS: ");
    lcd.print(tdsValue,0);
    lcd.print("ppm");
  }
}
// Função para medir DO (Oxigênio Dissolvido)
void medidor_DO() {
  if (millis() - doTimer >= DO_INTERVAL) {
    doTimer = millis();
    Temperaturet = sensors.getTempCByIndex(0);
    int sensor1Value = readMux(sensor1Channel);
    ADC_Raw = sensor1Value;
    ADC_Voltage = uint32_t(VREF) * ADC_Raw / ADC_RES;
    float DO = readDO(ADC_Voltage, Temperaturet)/1000.0;
    
    Serial.println("DO:\t" + String((readDO(ADC_Voltage, Temperaturet))/1000.0) + "mg/L\t");
    lcd.setCursor(0,0);
    lcd.print("DO: ");
    lcd.print(DO);
    lcd.print("mg/L");
  }
}
// Função para medir a Turbidez
void medidor_Turb() {
  if (millis() - turbTimer >= TURB_INTERVAL) {
    turbTimer = millis();
  int sensorValue = readMux(sensor3Channel);
  float voltage = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.println(voltage); // print out the value you read:
    lcd.setCursor(0,2);
    lcd.print("Turbidez: ");
    lcd.print(voltage);
    lcd.print("NTU");
    }
}
// Função para animar peixe
void fish(){
 // Animação do peixe e das bolhas
  for (int i = 3; i >= -1; i--) {

    lcd.setCursor(15, 3);
    lcd.write(byte(0)); // Desenha a parte superior do peixe
    lcd.setCursor(17, 3);
    lcd.write(byte(1)); 
    lcd.setCursor(16, 3);
    lcd.write(byte(2)); 
    lcd.setCursor(18, 3);
    lcd.write(byte(3)); 

    if (i <= 3) {
      lcd.setCursor(19, i);
      lcd.write(byte(7)); // Desenha a bolha maior

    }

    if (i <= 2) {
      lcd.setCursor(19, i + 1);
      lcd.write(byte(6)); // Desenha a bolha
    }

    if (i <= 1) {
      lcd.setCursor(19, i + 2);
      lcd.write(byte(5)); // Desenha a bolha menor
    }

    if (i <= 0) {
      // Desenha a bolha maior E
      lcd.setCursor(19, i+3);
      lcd.write(byte(4)); // Desenha a bolha pequena-
    }
    delay(250); // Espera antes da próxima atualização
  }
}
unsigned long sensorSwitchTimer = 0;
const unsigned long SENSOR_SWITCH_INTERVAL = 2000; // 2 segundos
bool isFirstGroupActive = true;

void loop(void) {
  unsigned long currentMillis = millis();

  // Verifica se é hora de alternar entre os grupos de sensores
  if (currentMillis - sensorSwitchTimer >= SENSOR_SWITCH_INTERVAL) {
    sensorSwitchTimer = currentMillis;
    isFirstGroupActive = !isFirstGroupActive; // Alterna o estado do grupo de sensores
    lcd.clear();
  }

  // Chamando as funções de acordo com o grupo ativo
  if (isFirstGroupActive) {
    medidor_temperatura();
    medidor_opr();
    medidor_ec();
    medidor_ph();
  } else {
    medidor_DO();
    medidor_TDS();
    medidor_Turb();
  }
  fish();
}
