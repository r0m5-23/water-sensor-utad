# Water Sensor UTAD

> Para mais fácil leitura deste ficheiro, usar o vscode (ou similar) e colocar em modo "__preview__".

## Obter o EUI da placa

O código necessário para essa tarefa esta na pasta _get_eui_

__Resultado:__

```plan
Your device EUI is: A8610A33374E820C
```

## Register Devices

```plan
Application ID: water_sensor_utad
Device EUI: A8610A33374E820C
```

__Resultado:__

```js
const char *appEui = "70B3D57ED002BD86";
const char *appKey = "6935F074F3ADB47783E5FB0DCAA7EFF9";
```

## Medições

O código encontra-se nos ficheiros `water_sensor_utad.ino` e `arduino_secrets.h`

### Obter valor

Apresentação das partes mais importantes do código e uma breve explicação de cada uma.

```c

  // Ler o valor da tensão
  // Read the voltage value
  voltage = analogRead(A0);

  // Se a tensão for maior que 1 volt, conta uma gota
  // If the voltage is greater than 1 volt, it counts a drop
  if (voltage > 210) drops++;

  // Média de gotas por minuto (60000ms) - Valor máximo previsto: 1200 gotas
  // Average drops per minute (60000ms) - Maximum expected value: 1200 drops
  if (millis() - time > 60000)
  {
    dropvalue = (float)drops * 0.6 + (float)dropvalue * 0.4;
    drops = 0;
    time = millis();
  }

  // Enviar valores para "the network of things" de hora em hora (360000ms)
  // Send values to "the network of things" hourly (360000ms)
  if (millis() - timeUpload > 360000)
  {

    // Tratamento de dados
    // Data processing
    int aux = (int)(dropvalue + 0.55);
    txBuffer[0] = (aux >> 8) & 0xff;
    txBuffer[1] = aux & 0xff;

    // Envio de dados
    // Sending data
    int err;
    modem.beginPacket();
    modem.write(txBuffer);
    err = modem.endPacket(true);

    // Redefinir temporizador
    // Reset timer
    timeUpload = millis();
  }
```

## Payload Formats

```js
function Decoder(bytes, port) {
  var decoded = {};
  
  var dropSize = 2.25 //mm
  var timeScale = 60 //60 min
  
  if (port === 1) decoded.water = (((bytes[0] << 8) | bytes[1]) * dropSize * timeScale).toFixed(2); 

  return {
    field1:decoded.water,
  }
}
```

### Teste do Payload

```plan
03 F3
```

__Resultado:__

```json
{
  "field1": "136485.00"
}
```

## Trabalho Realizado por

- __Eduardo Queirós - _22653___

- __Hugo Claro - _66509___

