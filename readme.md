# Projeto de Monitoramento de Qualidade da Água
**Componente da Plataforma Integrada de Sustentabilidade Marinha e Oceânica (PISMO)**

![Badge Dev](https://img.shields.io/badge/Status-Em%20Desenvolvimento-green?style=flat-square) ![Simulador Wokwi](https://img.shields.io/badge/Wokwi-Simulador-blue?style=flat-square&logo=data%3Aimage%2Fsvg%2Bxml%3Bbase64%2CPHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZlcnNpb249IjEiIHdpZHRoPSI1MDAiIGhlaWdodD0iNTAwIiB2aWV3Qm94PSIwIDAgNTAwIDUwMCI%2BDQogIDxwYXRoIGQ9Ik0xMDQuOCAzODguMjVjLTE1Ljc1IC0xOC40MjUgLTE5LjEyNSAtNDYuNTc1IC04IC02Ny4xIDEwLjEyNSAtMTguNyA4LjY1IC0yOC40IC0xNC41NzUgLTk2IC0yMy40MjUgLTY4LjI1IC0yNy45IC03Ni4yNSAtNDguMzc1IC04Ni4zNzUgLTQ3LjkgLTIzLjcyNSAtNDQuMTI1IC04Ni4zIDYuMDUgLTEwMCA0Ny4zIC0xMi45NSA4NC4zNSAzNC42MjUgNjAuNDUgNzcuNjI1IC0xMC40IDE4Ljc1IC05IDI3LjgyNSAxNC44MjUgOTYuNjI1IDI0LjIyNSA2OS45IDI4LjEyNSA3Ni44IDQ5LjEgODYuNDI1IDI5LjggMTMuNyA0MC41IDQ3LjA3NSAyNC4yMjUgNzUuNiAtMTYuMjUgMjguNSAtNjQuMTUgMzYuMDUgLTgzLjcgMTMuMm00Ny44IC0yNS4wNzVjMTEuNjI1IC05LjUgMTAuNjUgLTE5LjkgLTIuNTc1IC0yNy40NSAtNS45NSAtMy40IC0xMy42MjUgLTQuNjUgLTE3LjAyNSAtMi43NzUgLTEwLjU3NSA1Ljc1IC0xMC4xNzUgMjUuMzUgMC42MjUgMzEuNSA1LjY1IDMuMjI1IDE0LjE3NSAyLjY1IDE5IC0xLjI1ek02NS4zIDEwNC4yNWM4LjY1IC00LjcyNSA1LjYgLTI2LjkyNSAtNC41IC0zMi43IC04LjQyNSAtNC44IC0yNC44NzUgNi43MjUgLTI0LjUgMTcuMTc1IDAuMzI1IDkuNjUgMjAuMjI1IDIwLjMgMjkgMTUuNTI1TTI5OC42MjUgMzc1Yy0xNS43NSAtMTguNDI1IC0xOS4xMjUgLTQ2LjU3NSAtOCAtNjcuMSAxMC4xMjUgLTE4LjcgOC42NSAtMjguNCAtMTQuNTc1IC05NiAtMjMuNDI1IC02OC4yNSAtMjcuOSAtNzYuMjUgLTQ4LjM3NSAtODYuMzc1IC00Ny45IC0yMy43MjUgLTQ0LjEyNSAtODYuMyA2LjA1IC0xMDAgNDcuMyAtMTIuOTUgODQuMzUgMzQuNjI1IDYwLjQ1IDc3LjYyNSAtMTAuNCAxOC43NSAtOSAyNy44MjUgMTQuODI1IDk2LjYyNSAyNC4yMjUgNjkuOSAyOC4xMjUgNzYuOCA0OS4xIDg2LjQyNSAyOS44IDEzLjcgNDAuNSA0Ny4wNzUgMjQuMjI1IDc1LjYgLTE2LjI1IDI4LjUgLTY0LjE1IDM2LjA1IC04My43IDEzLjJtNDcuOCAtMjUuMDc1YzExLjYyNSAtOS41IDEwLjY1IC0xOS45IC0yLjU3NSAtMjcuNDUgLTUuOTUgLTMuNCAtMTMuNjI1IC00LjY1IC0xNy4wMjUgLTIuNzc1IC0xMC41NzUgNS43NSAtMTAuMTc1IDI1LjM1IDAuNjI1IDMxLjUgNS42NSAzLjIyNSAxNC4xNzUgMi42NSAxOSAtMS4yNXpNMjU5LjEyNSA5MWM4LjY1IC00LjcyNSA1LjYgLTI2LjkyNSAtNC41IC0zMi43IC04LjQyNSAtNC44IC0yNC44NzUgNi43MjUgLTI0LjUgMTcuMTc1IDAuMzI1IDkuNjUgMjAuMjI1IDIwLjMgMjkgMTUuNTI1IiBmaWxsPSIjZmZmIi8%2BDQogIDxwYXRoIGQ9Ik0xMTMuNTc1IDQwNS41Yy01MC42NzUgLTI5LjY3NSAtMzIuNSAtMTA0LjYyNSAyNS4zNzUgLTEwNC42MjUgMTguNzUgMCAyMC40IC00LjQyNSA0Ni42IC0yOS4yMjVzNzAuODI1IC02NS42NzUgMTAwLjg3NSAtODAuNTI1YzguMSAxMS40NzUgMTQuMjc1IDQwLjM1IDE1LjE3NSA0My43IC0xOS4zMjUgMCAtNjguNzUgMzcuODc1IC04OS43IDYzLjQyNSAtMjAuMjUgMjQuNzI1IC0yNC42MjUgMzUgLTIzLjIgNTQuNyAxLjMgMTguMjUgLTIuMDI1IDI3Ljc3NSAtMTMuNTUgMzguNSAtMTkuNDc1IDE4LjIyNSAtNDQuNjUgMjMuOTUgLTYxLjU3NSAxNC4wNW0zOSAtNDIuMzc1YzUuMzc1IC0xNCAtMC42MjUgLTIyLjU1IC0xNS44NSAtMjIuNTUgLTE0Ljg1IDAgLTIyLjQgMTAuMiAtMTcuMzI1IDIzLjQ1IDQuOTUgMTIuOSAyOC4xMjUgMTIuMjUgMzMuMTc1IC0wLjltMTc3LjA1IC02MS42MjVzNy4wNzUgLTE0LjEyNSAzNC44IC05Mi45MjVjMzYgLTEwMS45MjUgMzcuNzI1IC0xMTAuMTUgMjcuNCAtMTMxLjU3NSAtMjIuMTc1IC00NiAyMC44NzUgLTkyLjEgNjcuMjc1IC03MiAxNy4zNSA3LjUgMjMuMjc1IDE0LjYyNSAzMC45IDM3LjI1IDguMyAyNC41NzUgNy41NzUgMjkuNzUgLTYuMSA0MyAtOC41NSA4LjI3NSAtMjIuNCAxNy45IC0zMC44IDIxLjQgLTExLjc1IDQuOSAtMjQuMjc1IDMxLjM3NSAtNTQuNjI1IDExNS40NSAtMzYuMDc1IDk5LjkyNSAtMjYuNSA3MC40MjUgLTE2Ljc1IDg4LjUyNSAyNC4wMjUgNDQuNzUgLTYuNSAxMi4zIC01Mi4xIC05LjEyNW0xMjYuNjUgLTI0Ni4yNWMtMC4xNSAtMTUgLTguODc1IC0yMC43MjUgLTIzLjA1IC0xNS4xMjUgLTYuMzUgMi41MjUgLTEyLjEyNSA3LjcyNSAtMTIuOCAxMS41NSAtMi4xMjUgMTEuODUgMTMuNDI1IDIzLjc3NSAyNSAxOS4yIDYuMDI1IC0yLjM3NSAxMC45MjUgLTkuNDI1IDEwLjg1IC0xNS42eiIgZmlsbD0iI2ZmZiIvPg0KPC9zdmc%2BDQo%3D&link=https%3A%2F%2Fwokwi.com%2Fprojects%2F399406655920398337) ![Badge License](https://img.shields.io/badge/License-MIT-brightgreen?style=flat-square)

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
