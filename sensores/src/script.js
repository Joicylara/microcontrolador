// Importa os módulos Firebase
import { initializeApp } from 'https://www.gstatic.com/firebasejs/9.6.1/firebase-app.js';
import { getDatabase, ref, onValue } from 'https://www.gstatic.com/firebasejs/9.6.1/firebase-database.js';

// Configuração do Firebase
const firebaseConfig = {
    apiKey: "AIzaSyC8N4eAvDDESX9SzhTqg0uVpMO0zsV5wRI",
    authDomain: "sensores-micro-29f70.firebaseapp.com",
    databaseURL: "https://sensores-micro-29f70-default-rtdb.firebaseio.com",
    projectId: "sensores-micro-29f70",
    storageBucket: "sensores-micro-29f70.appspot.com",
    messagingSenderId: "873229173748",
    appId: "1:873229173748:web:cb414cafee3854448d2fa1",
    measurementId: "G-GJSSMQ4M5J"
};

// Inicializa o Firebase
const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

// Referência aos dados do sensor
const temperatureRef = ref(database, 'sensors/temperature');
const humidityRef = ref(database, 'sensors/humidity');

// Variáveis para armazenar o gráfico e o índice
let sensorChart;
let dataIndex = 0; // Inicia o índice em 0
const updateInterval = 5; // Intervalo de atualização em segundos

// Função para criar o gráfico
function createChart() {
    const ctx = document.getElementById('sensor-chart').getContext('2d');

    // Se o gráfico já existir, destrua-o
    if (sensorChart) {
        sensorChart.destroy();
    }

    sensorChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: [], // Labels do gráfico, representam os segundos
            datasets: [{
                label: 'Temperatura',
                data: [], // Dados da temperatura
                borderColor: 'rgba(255, 99, 132, 1)',
                backgroundColor: 'rgba(255, 99, 132, 0.2)',
                borderWidth: 1,
                fill: false // Não preenche a área abaixo da linha
            }, {
                label: 'Umidade',
                data: [], // Dados da umidade
                borderColor: 'rgba(54, 162, 235, 1)',
                backgroundColor: 'rgba(54, 162, 235, 0.2)',
                borderWidth: 1,
                fill: false // Não preenche a área abaixo da linha
            }]
        },
        options: {
            responsive: true,
            scales: {
                x: {
                    type: 'linear', // Usa um eixo linear
                    position: 'bottom',
                    title: {
                        display: true,
                        text: 'Segundos'
                    },
                    ticks: {
                        stepSize: updateInterval // Define o intervalo dos ticks
                    }
                },
                y: {
                    beginAtZero: true,
                    title: {
                        display: true,
                        text: 'Valor'
                    }
                }
            }
        }
    });
}

// Atualiza os dados do gráfico
function updateChart(temperature, humidity) {
    // Adiciona dados ao gráfico
    sensorChart.data.labels.push(dataIndex * updateInterval);
    sensorChart.data.datasets[0].data.push({x: dataIndex * updateInterval, y: temperature});
    sensorChart.data.datasets[1].data.push({x: dataIndex * updateInterval, y: humidity});

    dataIndex++; // Incrementa o índice

    // Mantém o gráfico com dados limitados para não sobrecarregar a memória
    if (sensorChart.data.labels.length > 20) {
        sensorChart.data.labels.shift();
        sensorChart.data.datasets.forEach(dataset => dataset.data.shift());
    }

    sensorChart.update();
}

// Atualiza a interface com os dados
onValue(humidityRef, (snapshot) => {
    const humidity = snapshot.val();
    document.getElementById('humidity').textContent = humidity !== null ? humidity.toFixed(1) : '--';
    if (sensorChart) {
        updateChart(parseFloat(document.getElementById('temperature').textContent), humidity);
    }
});

onValue(temperatureRef, (snapshot) => {
    const temp = snapshot.val();
    document.getElementById('temperature').textContent = temp !== null ? temp.toFixed(1) : '--';
    if (sensorChart) {
        updateChart(temp, parseFloat(document.getElementById('humidity').textContent));
    }
});

// Função para mostrar as abas
function showTab(tabId) {
    document.querySelectorAll('.tab-content').forEach(tab => {
        tab.classList.remove('active');
    });
    document.querySelectorAll('.tab-button').forEach(button => {
        button.classList.remove('active');
    });
    document.getElementById(tabId).classList.add('active');
    document.querySelector(`#${tabId}-tab`).classList.add('active');
}

// Adiciona manipuladores de eventos para as abas
document.getElementById('data-tab').addEventListener('click', () => showTab('data'));
document.getElementById('chart-tab').addEventListener('click', () => {
    showTab('chart');
    if (!sensorChart) {
        createChart();
    }
});
