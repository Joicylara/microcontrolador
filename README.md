<h1>🖥️ Disciplina de Microcontroladores - Projetos e Trabalhos</h1>
Este repositório contém os principais projetos e atividades desenvolvidos ao longo da disciplina de Microcontroladores ministrada pelo professor Dr. [Alberto Mascarenhas](https://sites.google.com/site/awmascarenhas)

Durante a disciplina foi explorado diversos conceitos e tecnologias relacionadas ao controle de sistemas embarcados, comunicação e sensores.

### 📝 Trabalhos Realizados
1. 🏐 Controle de Levitação de uma Bolinha
O objetivo deste projeto foi desenvolver um sistema de controle de levitação de uma bolinha de isopor utilizando um microcontrolador PIC16F877A. O sistema ajusta a velocidade de um cooler via PWM para manter a bolinha a uma altura desejada, medida por um sensor ultrassônico.

- Desafio: Manter a bolinha estável na altura definida.
- Solução: Implementação de controle PID e comunicação serial para definir a altura alvo.

2. 📲 Interface de Controle usando MQTT e ESP32
Neste trabalho, foi criado uma interface no MIT Inventor para controlar um LED e exibir os valores de um potenciômetro conectado a um ESP32. A comunicação entre o app e o ESP32 foi realizada via MQTT.

- Funcionalidades:
   - Ligar/desligar o LED remotamente.
   - Monitorar e exibir em tempo real os valores do potenciômetro.

3. 🌊 Controle de Nível de Água
Foi desenvolvido um sistema de controle de nível de água, onde o microcontrolador monitora o nível em um reservatório. Utilizei o sensor ultrassônico para determinar a altura da água no tanque,  foi utilizado também uma bomba submersa d'água para encher o recipiente conforme necessário.

- Desafio: Garantir a precisão das medições e o acionamento eficiente da bomba.
- Solução: Implementação de controle PID e utilização de sensor mais preciso para verificar o nível da água.

4. 🌡️💧 Sensor DHT22 com Firebase
Neste projeto, foi utilizado o sensor DHT22 para monitorar temperatura e umidade. Os dados lidos foram enviados para o Firebase em tempo real, criando um sistema de monitoramento remoto via interface web.

- Tecnologias:
    - Firebase Realtime Database
    - WiFi ESP32
    - Comunicação com sensores (DHT22).
 
5. 📊 Apresentação sobre o Microcontrolador STM8S003F3P
Preparação da apresentação técnica sobre o microcontrolador STM8S003F3P, abordando suas principais características, vantagens, aplicações e arquitetura. O foco foi mostrar suas capacidades e como ele se compara a outros microcontroladores no mercado.

### 📚 Conhecimentos Aplicados
Ao longo da disciplina, foram explorados os seguintes conceitos:

- Programação de microcontroladores (PIC16F877A, ESP32, STM8).
- Controle por PWM.
- Comunicação via MQTT e Firebase.
- Integração de sensores e atuadores.
- Controle de sistemas de feedback (PID).
- Criação de interfaces para controle remoto.

### 🚀 Professor: Alberto Mascarenhas
Agradecimentos ao professor Alberto Mascarenhas por toda a orientação e apoio ao longo da disciplina, proporcionando desafios práticos que ampliaram o conhecimento em sistemas embarcados.
