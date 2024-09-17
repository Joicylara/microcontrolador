<h1>🌡️📊 Monitoramento de Dados do Sensor DHT22 com Firebase</h1>

Este projeto desenvolvido na disciplina de microcontroladores, é uma aplicação que monitora os dados de temperatura e umidade de um sensor conectado ao microcontrolador ESP32 - WROOM, enviando-os em tempo real para o banco de dados Firebase. 
Os dados são exibidos em uma página web de forma clara e intuitiva.

### 📋 Funcionalidades
- Leitura em tempo real de sensores de temperatura e umidade. 
- Conexão com o Firebase para armazenar e acessar os dados remotamente. 
- Interface web dinâmica que exibe as leituras atuais dos sensores. 
- Visualização dos dados com ícones modernos e design responsivo.

### 🚀 Tecnologias Utilizadas
- ESP32 para capturar os dados do sensor.
- Firebase Realtime Database para armazenamento dos dados. 
- HTML, CSS, JavaScript para construção da interface web.
- Firebase Host para o deploy.

### ⚙️ Como Usar
1. Conecte o ESP32 ao seu sensor DHT22 para obter os dados de temperatura e umidade.
2. Configure o Firebase com suas próprias credenciais de projeto, atualizando as variáveis apiKey, authDomain, databaseURL, etc., no código da página web.
3. Faça upload do código para o ESP32, que irá enviar os dados ao Realtime Database.
4. Abra a aplicação web em um navegador para visualizar os dados em tempo real

### 🛠️ Configuração do Firebase
- Crie um projeto no Firebase Console e habilite o Realtime Database.
- Adicione as regras de segurança conforme necessário (para fins de teste, você pode usar .read e .write como true).
- Use as credenciais do Firebase no arquivo JavaScript da aplicação para conectar sua página ao banco de dados.


📷 Imagens do Projeto
<div align = "center"> 
  <h3>Imagem ilustrativa do esquemático da montagem</h3>
  <img src = "https://github.com/user-attachments/assets/1c46d975-9e53-43e9-a0be-0d303434d385"  width = "500px">
</div> 

<div align = "center">
   <h3>Imagem da interface dos dados da temperatura e umidade</h3>
   <img src = "https://github.com/user-attachments/assets/88378a31-2065-4c4e-af2f-a3869cdbaa5b" width = "1400px"> 
</div>

<div align = "center">
    <h3>Imagem da interface do gráfico dos dados</h3>
    <img src = "https://github.com/user-attachments/assets/58f6505b-b250-472e-ba2b-cd0647155c22" width = "1400px"> 
</div>
⚠ Os dados não estão sendo exibidos no gráfico porque o microcontrolador não está conectado no momento.

