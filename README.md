# Water Level Monitoring System with Automatic Pump Control

This project utilizes an Arduino to monitor the water level in a tank and automatically control a pump to maintain the desired level. The system includes an OLED display to show real-time information.

## Main Components

- generic ESP32 board
- SSD1306 128x64 pixel OLED display
- Ultrasonic distance sensor
- Water pump
- Relay for pump control

## Functionality

1. Water level measurement:
   - The distance sensor continuously measures the height of the water surface in the tank.
   - The measurement is converted to water volume using mathematical functions suitable for the tank shape (cylindrical, rectangular, or truncated cone).

2. Automatic pump control:
   - When the water volume falls below a defined threshold (`minVolume`), the pump is automatically turned on.
   - The pump remains on until the volume reaches the desired level again.

3. Data display:
   - An OLED display shows the current water volume in liters.

## Configuration

The project can be configured by adjusting the following parameters:

- Tank dimensions (`h`, `radius`, `length`, `width`, `R`, `r`)
- Minimum volume threshold (`minVolume`)
- Component pin assignments (`SENSOR_PIN`, `RELAY_PIN`, `SCREEN_ADDRESS`)

## Library Installation

To compile and run the code, the following libraries are required:

- Wire.h
- Adafruit_GFX.h
- Adafruit_SSD1306.h

These libraries can be installed via the Arduino IDE's Library Manager.

## Usage

1. Connect components as described in the code comments.
2. Adjust parameters as necessary for your specific system.
3. Upload the code to the Arduino.
4. The system will begin monitoring the water level and automatically controlling the pump.

## Possible Improvements

- Add sound or visual alarms for critical water levels.
- Implement an automatic calibration system for the distance sensor.
- Add a simple user interface for parameter adjustment without needing to reprogram.

This project offers an efficient and automated solution for water level control in irrigation systems, industrial reservoirs, or other environments where continuous water monitoring is necessary.

### Code

