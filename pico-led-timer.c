#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos
#define LED_BLUE 12
#define LED_RED 13
#define LED_GREEN 11
#define BUTTON 5

// Variáveis de controle
volatile bool sequence_active = false;

// Protótipos das funções de callback
int turn_off_red_callback(alarm_id_t id, void *user_data);
int turn_off_green_callback(alarm_id_t id, void *user_data);
int turn_off_blue_callback(alarm_id_t id, void *user_data);

// Callback para desligar o LED vermelho
int turn_off_red_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED, 0);
    add_alarm_in_ms(3000, turn_off_green_callback, NULL, false);
    return 0;
}

// Callback para desligar o LED verde
int turn_off_green_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_GREEN, 0);
    add_alarm_in_ms(3000, turn_off_blue_callback, NULL, false);
    return 0;
}

// Callback para desligar o LED azul e permitir nova ativação
int turn_off_blue_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE, 0);
    sequence_active = false;
    return 0;
}

// Callback de interrupção do botão
void button_pressed_callback(uint gpio, uint32_t events) {
    if (!sequence_active) {
        sequence_active = true;
        gpio_put(LED_BLUE, 1);
        gpio_put(LED_RED, 1);
        gpio_put(LED_GREEN, 1);
        add_alarm_in_ms(3000, turn_off_red_callback, NULL, false);
    }
}

int main() {
    stdio_init_all();

    // Configuração dos LEDs
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);

    // Configuração do botão
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_pressed_callback);

    
    while (1) {
    if (sequence_active) {
        printf("Sequência de LEDs em andamento...\n");
    } else {
        printf("Sistema em espera. Pressione o botão para iniciar.\n");
    }
    sleep_ms(1000);
}

    return 0;
}
