# 🍇 Sistema de Monitoramento Ambiental - Vinheria Agnello

## 👥 Membros do grupo

- Kazys Tatarunas - RM564020  
- Eduardo Viudes - RM564075  
- Victor Tadashi - RM563582  
- Lucas Marson - RM563975  
- Frederico de Paulo - RM562109  

## 📋 Descrição

Este projeto implementa um sistema de monitoramento ambiental para a **Vinheria Agnello**, utilizando sensores analógicos simulados de:

- **Luminosidade (LDR)**
- **Temperatura**
- **Umidade**

Os sensores estão conectados a um **Arduino**, que realiza leituras constantes, calcula **médias móveis** para suavizar as medições e toma decisões com base nesses dados.

## 🖼️ Esquema do Circuito

Abaixo está a imagem representando o circuito montado no Tinkercad:

![Esquema do Circuito - Tinkercad](./images/...)

> 💡 *Caso não consiga visualizar a imagem, você pode acessar diretamente o projeto no Tinkercad pelo link abaixo:*

🔗 **[Clique aqui para abrir o projeto no Tinkercad](https://www.tinkercad.com/things/5TLWpyhApiF-vinheria-cp2)**

## ⚙️ Funcionalidades

- 🔎 **Leitura de Sensores**  
  Coleta contínua de dados dos sensores de luminosidade, temperatura e umidade.

- 📉 **Média Móvel**  
  Suavização dos valores dos sensores para evitar variações bruscas.

- 🔴🟡🟢 **Sinalização com LEDs**  
  - LED **verde**: Condição ideal  
  - LED **amarelo**: Alerta  
  - LED **vermelho**: Condição crítica  

- 🔊 **Buzzer de Alerta**  
  Ativado quando qualquer uma das variáveis estiver fora dos padrões ideais.

- 🖥️ **Display**  
  Exibe mensagens rotativas a cada 5 segundos, informando o estado atual de:
  - Luminosidade  
  - Temperatura  
  - Umidade  

- 🧾 **Saída Serial**  
  Exibe os dados em tempo real no monitor serial para visualização no computador.

## 🔌 Componentes Utilizados

- Arduino Uno (ou similar)
- Sensor de luminosidade (LDR)
- Sensor de temperatura e umidade (simulados via potenciômetro ou sensores reais)
- LEDs: verde, amarelo e vermelho
- Buzzer
- Display
- Resistores, fios e protoboard

## 🛠️ Como Usar

1. Conecte os sensores e atuadores ao Arduino conforme o esquema do projeto.
2. Faça o upload do código para a placa utilizando a IDE do Arduino.
3. Abra o monitor serial para acompanhar as leituras em tempo real.
4. Observe os LEDs e o display LCD para o estado atual do ambiente.
5. O buzzer será ativado automaticamente em situações críticas.

## ✅ Objetivo

O sistema visa auxiliar a Vinheria Agnello no **monitoramento das condições ambientais**, garantindo um ambiente ideal para a conservação dos vinhos.
