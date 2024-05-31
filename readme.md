# Projeto de Monitoramento de Qualidade da Água
# Componete da Plataforma Integrada de Sustentabilidade Marinha e Oceânica(PISMO)

Este projeto utiliza sensores para medir a qualidade da água, incluindo temperatura, pH, turbidez,oxigênio dissolvido, ORP (Potencial de Oxidação-Redução) e condutividade elétrica. Os dados coletados são exibidos em um display LCD e também podem ser monitorados via Serial Monitor.

## Sumário

1. [Descrição do Projeto](#descrição-do-projeto)
2. [Componentes Necessários](#componentes-necessários)
3. [Esquema de Ligações](#esquema-de-ligações)
4. [Instalação e Configuração](#instalação-e-configuração)
5. [Como Usar](#como-usar)
6. [Funcionamento do Código](#funcionamento-do-código)
7. [Licença](#licença)

## Descrição do Projeto

Este projeto foi desenvolvido para monitorar a qualidade da água utilizando um conjunto de sensores conectados a um Arduino. As medições de temperatura, pH, turbidez e condutividade elétrica são feitas periodicamente e exibidas em um display LCD. O projeto é ideal para aplicações em aquários, estações de tratamento de água ou em estudos ambientais.

## Componentes Necessários

- 1 x Arduino Uno
- 1 x Sensor de Temperatura e Umidade DHT22
- 1 x Display LCD 16x2 com módulo I2C
- 1 x Sensor de pH
- 1 x Sensor de Turbidez
- 1 x Sensor de Condutividade Elétrica (EC)
- 1 x LED
- Protoboard e Jumpers

## Esquema de Ligações

- **DHT22**
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
  - Saída: A0

- **Sensor de Turbidez**
  - VCC: 5V
  - GND: GND
  - Saída: A3
  - LED: Pino 2

- **Sensor de Condutividade Elétrica (EC)**
  - VCC: 5V
  - GND: GND
  - Saída: A1
  - Eletrodo: Pino 3

## Instalação e Configuração

1. **Clone o repositório ou faça o download do código.**
   ```sh
   git clone https://github.com/APB-Abner/PISMO.git
   ```

2. **Instale as bibliotecas necessárias:**
   - DHT Sensor Library
   - LiquidCrystal I2C

   Você pode instalar essas bibliotecas através do Gerenciador de Bibliotecas do Arduino IDE.

3. **Abra o código no Arduino IDE.**

4. **Conecte os componentes conforme o esquema de ligações.**

5. **Carregue o código no Arduino.**

## Como Usar

1. **Ligue o Arduino e abra o Serial Monitor na IDE do Arduino.**
2. **Aguarde as leituras dos sensores aparecerem no display LCD e no Serial Monitor.**

## Funcionamento do Código

O código é dividido em funções para cada tipo de sensor:

- **medidor_temperatura()**: Lê a temperatura do sensor DHT22 e exibe no LCD e Serial Monitor.
- **medidor_ph()**: Lê o valor analógico do sensor de pH, converte para pH e exibe no LCD e Serial Monitor.
- **medidor_turbidez()**: Lê o valor analógico do sensor de turbidez, converte para NTU (Unidades Nefelométricas de Turbidez) e exibe no LCD e Serial Monitor.
- **medidor_ec()**: Lê o valor analógico do sensor de condutividade elétrica, converte para uS/cm (microsiemens por centímetro) e exibe no LCD e Serial Monitor.

O loop principal do programa chama essas funções periodicamente para atualizar as leituras.

## Licença

Este projeto é licenciado sob a [MIT License](https://opensource.org/licenses/MIT). Sinta-se livre para usar, modificar e distribuir conforme necessário.

---

Esperamos que este README forneça todas as informações necessárias para configurar e usar o projeto. Se tiver dúvidas ou problemas, sinta-se à vontade para abrir uma issue no repositório do GitHub.

## Projeto realizado por:
- **Abner de Paiva Barbosa**: RM 558468
- **Fernando Luiz Silva Antonio**: RM 555201
- **Thomas de Almeida Reichmann**: RM 554812