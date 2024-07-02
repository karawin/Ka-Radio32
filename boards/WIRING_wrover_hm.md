# Wiring


## LCD 

|     |ESP32 |ST7735 |
|-----|------|-------|
|MOSI |23    |SDA |
|CLK  |18    |SCK |
|CS   |5     |CS |
|DC   |4     |A0 |
|RST  |2     |RESET |
|BACKLIGHT   |15   |LED |

## I2S

|  |ESP32   |PCM5102 |
|-----|-----|--------|
|LRCK |25   |WSEL |
|BCLK |26   |BCLK |
|DATA |27   |DIN  |

## Rotary encoders
### Channels
|         |ESP32 |KY-040 |
|---------|------|-------|
|ENC0_A   |14 |CLK |
|ENC0_B   |13 |DT  |
|ENC0_BTN |12 |SW  |

### Volume
|         |ESP32 |KY-040 |
|---------|------|-------|
|ENC1_A   |32 |CLK |
|ENC1_B   |33 |DT  |
|ENC1_BTN |22 |SW  |

## Infrared receiver

|          |ESP32 |IR  |
|----------|------|----|
|IR_SIGNAL |21    |OUT |
