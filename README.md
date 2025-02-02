# Controle de Sequência de LEDs com Raspberry Pi Pico

Este projeto implementa uma sequência de LEDs utilizando a Raspberry Pi Pico. A sequência é ativada ao pressionar um botão, acendendo os LEDs e desligando-os um por vez em intervalos de 3 segundos.

## Funcionalidade

- Pressionar o botão inicia a sequência de LEDs.
- Todos os LEDs são acesos simultaneamente.
- O LED vermelho apaga após 3 segundos.
- O LED verde apaga após mais 3 segundos.
- O LED azul apaga após mais 3 segundos.
- A sequência pode ser reiniciada após a conclusão.

## Componentes Utilizados

- **Raspberry Pi Pico**
- **LEDs** (vermelho, verde e azul)
- **Resistores** de 220Ω para cada LED
- **Botão push**
- **Resistor pull-up de 10kΩ** (opcional, se não usar pull-up interno)

## Ligações

| Componente | Pino da Pico |
|------------|-------------|
| LED Azul   | GPIO 12 |
| LED Vermelho | GPIO 13 |
| LED Verde  | GPIO 11 |
| Botão     | GPIO 5  |

## Instalação e Uso

1. **Clone o repositório:**
   ```sh
   git clone https://github.com/seu-usuario/seu-repositorio.git
   cd seu-repositorio
   ```

2. **Compile o código:**
   Certifique-se de que o Raspberry Pi Pico SDK está configurado corretamente.
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Carregue o firmware:**
   - Conecte a Raspberry Pi Pico ao computador mantendo pressionado o botão BOOTSEL.
   - Copie o arquivo `.uf2` gerado para o dispositivo montado.

4. **Execução:**
   - Abra um terminal serial para visualizar as mensagens de depuração:
   ```sh
   minicom -b 115200 -o -D /dev/ttyUSB0
   ```
   - Pressione o botão para iniciar a sequência de LEDs.

## Exemplo de Saída no Terminal
```
Sistema em espera. Pressione o botão para iniciar.
Sequência de LEDs em andamento...
```

## Licença

Este projeto é de uso livre sob a licença MIT.

