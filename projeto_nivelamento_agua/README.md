<h1>Controle de Nível de Água com ESP32 🚰 </h1>
Este projeto foi desenvolvido como parte da Unidade 2 da disciplina de Microcontroladores, com o objetivo de controlar o nível de água em um recipiente utilizando um ESP32, um sensor ultrassônico, uma bomba submersa e um driver ULN2003. O sistema foi programado na IDE do Arduino e faz uso da biblioteca PID para realizar o controle preciso do nível da água.

### 🎯 Objetivo do Projeto
O principal objetivo deste projeto é demonstrar o controle automatizado do nível de água em um recipiente, utilizando um sistema com controle PID. O usuário pode definir a altura desejada da água via comunicação serial, e o sistema ajusta a operação da bomba submersa para manter o nível da água conforme especificado.

### 🛠 Componentes Utilizados
|Componentes                                | Função                                                                         |
| ----------------------------------- | -------------------------------------------------------------------------------------|
| ESP32                               | Microcontrolador responsável pelo processamento e controle do sistema                |
| Sensor Ultrassônico (HC-SR04)       | Utilizado para medir a altura da água no recipiente                                  |
| Bomba Submersa                      | Controlada pelo ESP32 para adicionar ou remover água conforme necessário             |
|Driver ULN2003                       | Intermediário entre o ESP32 e a bomba submersa para controlar o acionamento da bomba |
|IDE do Arduino                       | Ambiente de desenvolvimento utilizado para programar o ESP32                         |
|Biblioteca PID_v1                    |Implementa o controlador PID utilizado para ajustar o nível da água                   |
|Jumpers                              |Utilizados para fazer ligações entre os componentes sem precisar fazer uso de soldas  |
|Fonte de 5V                          |Alimentação da bomba submersa                                                         |
|Protoboard                           | placa de prototipagem eletrônica                                                     |  
|Torneira e seus componentes          | Para causar o distúrbios no sistema                                                  | 
|Mangueira de silicone                | para transferir a água                                                               |   
|Dois recipientes                     | 1 para ser o suporte com a água e outro para ser o que será enchido de acordo com o valor desejado|   
|Régua                                | Para mostrar o nivelamento da água                                                   |

### 💻 Funcionamento do Sistema
- **Leitura do Nível de Água**:

    O sensor ultrassônico mede a altura da água no recipiente, calculando a distância entre o sensor e a superfície da água. Esta distância é convertida para a altura da água.

- **Controle PID**:

  Um controlador PID ajusta a operação da bomba submersa com base na diferença entre a altura medida e a altura desejada (setpoint).
  O controlador PID calcula a saída necessária (valor de PWM) para acionar a bomba e ajustar o nível da água.

- **Interação com o Usuário**:

  O usuário define a altura desejada da água via comunicação serial. O sistema valida o valor e ajusta o setpoint do PID.
  O nível de água atual e o valor de PWM aplicado são exibidos no monitor serial.

### 📋 Como Utilizar

1. **Montagem do Circuito**:

  - Conecte o sensor ultrassônico aos pinos especificados no código (trigger e echo).
  - Conecte a bomba submersa ao driver ULN2003, que será controlado pelo pino PWM do ESP32.
  - Certifique-se de que todas as conexões estão corretas antes de prosseguir.

2. **Upload do Código**:
   
- Faça as alterações necessárias no código de acordo com o seu circuito, como a numerção dos seus pinos e do tamanho de seu recipiente.
- Instalar a biblioteca PID_v1, que pode ser pela própria IDE ou pelo [GitHub](https://github.com/br3ttb/Arduino-PID-Library).
- Carregue o código na placa ESP32 usando a IDE do Arduino.

3. **Definir Altura da Água**:

- Abra o monitor serial na IDE do Arduino, defina a altura desejada da água (valor que dependerá do tamanho do seu recipiente) e observe o sistema em ação.

### 🧪 Testes

<div align = "center"> 
<img src = "https://github.com/user-attachments/assets/9d804ef7-e522-4b07-8157-a1ecbf0cb6a7"  width = "200px">
<img src = "https://github.com/user-attachments/assets/0c2f6861-de46-4194-9248-88dc0514092f" width = "200px">
<img src = "https://github.com/user-attachments/assets/4fa46e9d-1e06-4950-b11e-ffd34151114f"  width = "200px">
 </div>

### 📝 Considerações finais
O projeto demonstra o controle de nível de água, mas ainda há espaço para melhorias. Uma das principais áreas a ser aprimorada é a sintonia do controlador PID e a precisão nos valores lidos pelo sensor ultrassônico. A escolha adequada dos parâmetros Kp, Ki e Kd pode resultar em um controle mais preciso e eficiente, e o uso de um outro sensor de distância pode melhorar a precisão da leitura.

Recomenda-se estudar os métodos de sintonia de controladores, como os critérios de Ziegler-Nichols, para melhorar o desempenho do sistema. A aplicação dessas técnicas pode permitir um ajuste mais refinado dos parâmetros PID, resultando em um controle mais preciso e confiável.
  
