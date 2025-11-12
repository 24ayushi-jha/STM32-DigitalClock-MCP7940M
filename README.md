# 🕒 STM32 Digital Clock using MCP7940M RTC and 16x2 LCD

##  Overview
This project is a **Digital Clock System** built using an **STM32F030C8T6 microcontroller**, **MCP7940M RTC module**, and a **16x2 LCD display**. The RTC maintains accurate date and time using I2C communication, while the LCD displays the current **hour, minute, second, date, month, year, and weekday** in real-time.

A **4x4 keypad** is used for user input to modify or verify time and date settings.

---

##  Hardware Components
| Component | Description |
|------------|-------------|
| **STM32F030C8T6** | 32-bit ARM Cortex-M0 microcontroller |
| **MCP7940M** | I2C-based Real-Time Clock with battery backup |
| **LCD 16x2** | Display for showing time and date |
| **Keypad (4x4)** | Used for entering time/date and controlling settings |
| **Connecting Wires** | For signal and power connections |
| **Breadboard or PCB** | For prototyping connections |

---

##  Functional Features
- Displays real-time **hour, minute, second** on LCD.
- Shows **date, month, year, and weekday**.
- Converts between **BCD and decimal** formats for RTC communication.
- Reads and writes time data via **I2C protocol**.
- Allows **manual time update** and RTC initialization.
- Indicates **AM/PM** based on hour register.
- Includes **leap year detection** and weekday tracking.

---

##  Software Details
- **IDE:** STM32CubeIDE  
- **Language:** C (using HAL library)  
- **RTC Communication:** I2C protocol  
- **Display Interface:** 8-bit parallel communication  
- **Keypad Scanning:** GPIO matrix scanning  

---

##  Core Functional Blocks
1. **LCD Driver Functions**
   - `LCD_Send_Command()`, `LCD_Print_Data()`, `LCD_Init()`
   - Responsible for sending commands and data to the LCD in 8-bit mode.

2. **RTC Communication**
   - `HAL_I2C_Mem_Read()` and `HAL_I2C_Mem_Write()` used to read/write RTC registers.
   - `BCDToDec()` and `decToBCD()` handle format conversion.

3. **Time Display**
   - `Read_hour()`, `Read_minutes()`, `Read_Seconds()`, etc.
   - Continuously updates the time on LCD.

4. **Date Management**
   - Functions for reading and displaying date, month, and year.
   - `Set_date()`, `Set_month()`, `Set_year()` allow time initialization.

5. **Keypad Input**
   - Scans matrix-style keypad rows and columns.
   - Detects and processes pressed keys for user interaction.

---

##  Example LCD Output
```
TIME: 10:42:56 AM
DATE: 12:11:25  WED
```

---

##  Repository Structure
```
/Core
 ├── Inc
 ├── Src
 │    └── main.c      <-- main program file
/Drivers
/STM32CubeIDE
.gitignore
README.md
```

---

##  Circuit Overview
- LCD connected to STM32 GPIO pins (8-bit data mode + RS/RW/EN).
- MCP7940M connected via I2C (SDA, SCL).
- Keypad connected using GPIO pins for row-column scanning.

---

## Future Improvements
- Add user setting mode via keypad (time/date editing).
- Implement alarm or stopwatch feature.
- Add UART output for serial monitoring.

---

## References
- [MCP7940M Datasheet (Microchip)](https://ww1.microchip.com/downloads/en/DeviceDoc/20005010F.pdf)
- [STM32F0 Reference Manual](https://www.st.com/resource/en/reference_manual/dm00091010.pdf)
- STM32 HAL Library Documentation
