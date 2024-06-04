# Projeto de Monitoramento de Qualidade da Água
**Componente da Plataforma Integrada de Sustentabilidade Marinha e Oceânica (PISMO)**

![Badge Dev](https://img.shields.io/badge/Status-Em%20Desenvolvimento-green?style=flat-square) ![Simulador Wokwi](https://img.shields.io/badge/Simulador-Wokwi-blue?style=flat-square&link=https%3A%2F%2Fwokwi.com%2Fprojects%2F399264501474196481) ![Badge License](https://img.shields.io/badge/License-MIT-brightgreen?style=flat-square)

Este projeto utiliza sensores para medir a qualidade da água, incluindo temperatura, pH, oxigênio dissolvido (DO), ORP (Potencial de Oxidação-Redução), condutividade elétrica (EC), sólidos totais dissolvidos (TDS) e turbidez. Os dados coletados são exibidos em um display LCD e também podem ser monitorados via Serial Monitor.

## Sumário

1. [Descrição do Projeto](#descrição-do-projeto)
2. [Componentes Necessários](#componentes-necessários)
3. [Esquema de Ligações](#esquema-de-ligações)
4. [Instalação e Configuração](#instalação-e-configuração)
5. [Como Usar](#como-usar)
6. [Funcionamento do Código](#funcionamento-do-código)
7. [Autores](#autores)
8. [Licença](#licença)

## Descrição do Projeto

Este projeto foi desenvolvido para monitorar a qualidade da água utilizando um conjunto de sensores conectados a um Arduino. As medições de temperatura, pH, Potencial de Oxidação-Redução (ORP), condutividade elétrica (EC), oxigênio dissolvido (DO), sólidos totais dissolvidos (TDS) e turbidez são feitas periodicamente e exibidas em um display LCD. O projeto é ideal para aplicações em aquários, estações de tratamento de água ou em estudos ambientais.

## Componentes Necessários

- 1 x Arduino Uno
- 1 x Sensor de Temperatura DS18B20
- 1 x Display LCD 20x4 com módulo I2C
- 1 x Sensor de pH
- 1 x Sensor de ORP (Potencial de Oxidação-Redução)
- 1 x Sensor de Condutividade Elétrica (EC)
- 1 x Sensor de Oxigênio Dissolvido (DO)
- 1 x Sensor de Sólidos Totais Dissolvidos (TDS)
- 1 x Sensor de Turbidez
- 1 x Multiplexador CD74HC4067
- 1 x LED
- Protoboard e Jumpers

## Esquema de Ligações

- **DS18B20 (Temperatura)**
  - VCC: 5V
  - GND: GND
  - Data: Pino 5

- **Display LCD**
  - SDA: A4
  - SCL: A5
  - VCC: 5V
  - GND: GND

- **Sensor de pH**
  - VCC: 5V
  - GND: GND
  - Saída: A2

- **Sensor de ORP**
  - VCC: 5V
  - GND: GND
  - Saída: A0
  - LED: Pino 13

- **Sensor de Condutividade Elétrica (EC)**
  - VCC: 5V
  - GND: GND
  - Saída: A1

- **Multiplexador CD74HC4067**
  - S0: Pino 12
  - S1: Pino 11
  - S2: Pino 10
  - S3: Pino 9
  - SIG: A3

- **Sensores conectados ao Multiplexador**
  - TDS: Canal 0
  - DO: Canal 1
  - Turbidez: Canal 2

## Instalação e Configuração

1. **Clone o repositório ou faça o download do código:**
   ```sh
   git clone https://github.com/APB-Abner/PISMO.git
   ```

2. **Instale as bibliotecas necessárias:**
   - LiquidCrystal I2C
   - DFRobot PH
   - DFRobot EC10
   - GravityTDS
   - OneWire
   - DallasTemperature
   - EEPROM

   Você pode instalar essas bibliotecas através do Gerenciador de Bibliotecas do Arduino IDE. As bibliotecas da DFRobot estão disponíveis no site da marca, que pode ser acessado [aqui](https://www.dfrobot.com).

3. **Abra o código no Arduino IDE.**

4. **Conecte os componentes conforme o esquema de ligações usando uma protoboard.**

5. **Carregue o código no Arduino.**

## Como Usar

1. **Ligue o Arduino e abra o Serial Monitor na IDE do Arduino.**
2. **Faça a calibração dos sensores necessários.** (Consulte o fabricante dos seus sensores)
3. **Aguarde as leituras dos sensores aparecerem no display LCD e no Serial Monitor.**

## Funcionamento do Código

**Nota:** Este projeto foi feito usando sensores da DFRobot, pode ser necessário modificar o código ao reproduzir usando outros sensores.


O código é dividido em funções para cada tipo de sensor:

- **medidor_temperatura()**: Lê a temperatura do sensor DS18B20 e exibe no LCD e Serial Monitor.
- **medidor_ph()**: Lê o valor analógico do sensor de pH, converte para pH e exibe no LCD e Serial Monitor.
- **medidor_opr()**: Lê o valor analógico do sensor de ORP, converte para mV e exibe no LCD e Serial Monitor.
- **medidor_ec()**: Lê o valor analógico do sensor de condutividade elétrica, converte para ms/cm (microsiemens por centímetro) e exibe no LCD e Serial Monitor.
- **medidor_DO()**: Lê o valor do sensor de oxigênio dissolvido (DO), converte para mg/L e exibe no LCD e Serial Monitor.
- **medidor_TDS()**: Lê o valor do sensor de sólidos totais dissolvidos (TDS), converte para ppm (partes por milhão) e exibe no LCD e Serial Monitor.
- **medidor_Turb()**: Lê o valor do sensor de turbidez, converte para NTU (unidade de turbidez nefelométrica) e exibe no LCD e Serial Monitor.
- **fish()**: controla a animação do peixe e das bolhas no LCD. 

O loop principal do programa alterna entre dois grupos de sensores a cada 2 segundos, chamando as funções correspondentes para atualizar as leituras, enquanto mantem sempre o o peixe em exibição.

### Caracteres Personalizados

O projeto inclui 8 caracteres personalizados para a animação de um peixe e bolhas no LCD. Os caracteres são definidos no início do código e carregados no LCD durante a configuração.

## Autores

- **Abner de Paiva Barbosa**: RM 558468
- **Fernando Luiz Silva Antonio**: RM 555201
- **Thomas de Almeida Reichmann**: RM 554812

## Licença

Este projeto é licenciado sob a [MIT License](https://opensource.org/licenses/MIT). Sinta-se livre para usar, modificar e distribuir conforme necessário.

---

Esperamos que este README forneça todas as informações necessárias para configurar e usar o projeto. Se tiver dúvidas ou problemas, sinta-se à vontade para abrir uma issue no repositório do GitHub.
