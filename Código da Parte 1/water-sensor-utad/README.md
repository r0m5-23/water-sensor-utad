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

## Envio de dados para o servidor

O código encontra-se nos ficheiros `water_sensor_utad.ino` e `arduino_secrets.h`

## Payload Formats

```js
function Decoder(bytes, port) {
  var decoded = {};

  if (port === 1) decoded.water = (((bytes[0] << 8) | bytes[1]) / 100.0).toFixed(2);

  return decoded;
}
```

### Teste - Payload

```
00 F9
```

__Resultado:__

```plan
{
  "water": "2.49"
}
```

## Trabalho Realizado por

> Eduardo Queirós - 22653<br>
> Hugo Claro - 66509
