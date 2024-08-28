/*
* Monitoramento de dados vitais usando FreeRTOS
*
* Nome: Davi Marques Caldeira
* Curso: Bacharelado em Ciência da Computação
*/

#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

// Prototipos das funções de tarefa
void vTaskMonitorHeartRate(void* pvParameters);
void vTaskMonitorOxygenSaturation(void* pvParameters);
void vTaskMonitorTemperature(void* pvParameters);

int main_(void) {
    // Criando as tarefas
    xTaskCreate(vTaskMonitorHeartRate, "Batimentos", configMINIMAL_STACK_SIZE, (void*)"Batimentos:", tskIDLE_PRIORITY, NULL);
    xTaskCreate(vTaskMonitorOxygenSaturation, "Saturacao", configMINIMAL_STACK_SIZE, (void*)"Saturacao:", tskIDLE_PRIORITY, NULL);
    xTaskCreate(vTaskMonitorTemperature, "Temperatura", configMINIMAL_STACK_SIZE, (void*)"Temperatura:", tskIDLE_PRIORITY, NULL);

    // Iniciando o escalonador
    vTaskStartScheduler();

    // O código não deve chegar aqui
    for (;;);
}

// Tarefa para monitorar batimentos cardíacos
void vTaskMonitorHeartRate(void* pvParameters) {
    const char* param = (const char*)pvParameters;
    int heartRate;

    for (;;) {
        // Gerando um valor aleatório para os batimentos cardíacos
        heartRate = rand() % 121 + 20; // Entre 20 e 140
        vPrintStringAndNumber(param, heartRate);

        // Verificando as condições para alertas
        if (heartRate < 50) {
            printf("Alerta: Batimento cardíaco baixo!\n");
        }
        else if (heartRate > 90) {
            printf("Alerta: Batimento cardíaco alto!\n");
        }

        // Atrasando a tarefa por 1 segundo
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Tarefa para monitorar saturação de oxigênio
void vTaskMonitorOxygenSaturation(void* pvParameters) {
    const char* param = (const char*)pvParameters;
    int oxygenSaturation;

    for (;;) {
        // Gerando um valor aleatório para a saturação de oxigênio
        oxygenSaturation = rand() % 21 + 80; // Entre 80% e 100%
        vPrintStringAndNumber(param, oxygenSaturation);

        // Verificando as condições para alertas
        if (oxygenSaturation < 90) {
            printf("Alerta: Saturação de oxigênio baixa!\n");
        }

        // Atrasando a tarefa por 1 segundo
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Tarefa para monitorar temperatura
void vTaskMonitorTemperature(void* pvParameters) {
    const char* param = (const char*)pvParameters;
    int temperature;

    for (;;) {
        // Gerando um valor aleatório para a temperatura
        temperature = rand() % 8 + 34; // Entre 34°C e 41°C
        vPrintStringAndNumber(param, temperature);

        // Verificando as condições para alertas
        if (temperature < 35) {
            printf("Alerta: Hipotermia!\n");
        }
        else if (temperature > 37) {
            printf("Alerta: Febre!\n");
        }

        // Atrasando a tarefa por 1 segundo
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
