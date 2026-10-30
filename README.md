# Pocket Watch- KN
Its a mini pocket watch with a round display , a vibrating motor , a battery and a xiao esp32-C6 . and the best part? it charges wirelesslyyyyy
ikr so cool . so i designed the pcb in kicad , the case in fusion 360 and the firmware in vs code and ardunio ide oh about the firmware i forgot to tell you wht it does.
### Firmware:
- it has a deep sleep mode so most of the time its sleeping to conserve battery , it wakes up at when you shake it aggressively 
- when it turns on in the mrng and it broadcasts its own local wifi , you connect to it , open the webpage and a prompt pops up asking for day order or holiday
once you enter tht , it will show the tabular form of the time table of the day and sends a message to the watch and turns off
- during normal time the screen stays black and shows nothing , but you can shake to wake it up make it show the time and current/upcoming class.
- automatically 5mins before and at the start of the class it lights up and notifies you by turning on and vibrating
- Right before i leave for school it turns on and once i submit the day order the wifi turns off and it goes back to sleep
- THIS IS DESIGNED ACCORDING TO MY SCHOOL TIME TABLE SO YOU SHOULD PROBABLY MAKE CHANGES TO THE FIRMWARE IF YOU'RE PLANNING TO USE IT 
## PCB 
<img width="946" height="561" alt="image" src="https://github.com/user-attachments/assets/634237b8-6c97-4850-b247-b923b9855c3f" />
<img width="468" height="407" alt="image" src="https://github.com/user-attachments/assets/718b638b-173e-4ac1-9c23-e98ace43b6d3" />
<img width="586" height="457" alt="image" src="https://github.com/user-attachments/assets/5145f8cc-2d9d-40a1-a585-faa5876763c4" />
<img width="444" height="447" alt="image" src="https://github.com/user-attachments/assets/32a5b80b-a24c-4738-a995-8f7900573383" />

## Case (will make changes once the component's size are measured)
<img width="427" height="322" alt="image" src="https://github.com/user-attachments/assets/d24b66c7-e9f5-4d2a-b231-ff56b7886b63" />
<img width="494" height="381" alt="image" src="https://github.com/user-attachments/assets/c7a5df57-517c-445f-9062-b24ea7675945" />

## BOM
## Bill of Materials (BOM)

| Part | Quantity | Price (USD) | Vendor | Link |
|---|---:|---:|---|---|
| Flat 1034 Mobile Phone Vibrator Motor | 1 | $0.31 | Robu | [link](https://robu.in/product/flat-1027-mobile-phone-vibration-motor/) |
| STMicroelectronics LIS3DH 3-Axis Digital Accelerometer | 1 | $2.8 | Robu | [link](https://robu.in/product/smartelex-triple-axis-accelerometer-breakout-lis3dh/) |
| GoldenMorning GC9A01P 1.28" 240×240 SPI Round Display | 1 | $5.06 | Robu | [link](https://robu.in/product/goldenmorning-gc9a01-7p-240x240-spi-1-28-inch-round-display-module/) |
| 2N2222 NPN Transistor | 5 | $0.12 | Robu | [link](https://robu.in/product/2n2222-npn-transistor-pack-of-20/) |
| 1kΩ 1W Metal Film Resistor | 6 | $0.13 | Robu | [link](https://robu.in/product/1k-ohm-1w-metal-film-resistor-pack-of-40/) |
| 1N4148 Small Signal Diode | 2 | $0.15 | Robu | [link](https://robu.in/product/1n4148-tap-vishay-1n4148-tap-small-signal-diode-single-100-v-150-ma-1-v-8-ns-2-a/) |
| Seeed Studio XIAO ESP32C6 | 1 | $10.33 | Robu | [link](https://robu.in/product/seeed-studio-xiao-esp32c6/) |
| HEAVENGLOW Qi Wireless Micro USB Charging Receiver Module | 1 | $5.97 | Amazon | [link](https://www.amazon.in/gp/product/B0FN4J4VNT/ref=ox_sc_act_title_1?smid=A2AL6IVND0I91F&psc=1) |
| 3.7V 300mAh LiPo Battery | 1  | $3.8 | Amazon | [link](https://www.amazon.in/gp/product/B0DY89KG26/ref=ox_sc_saved_image_2?smid=AJ6SIZC8YQDZX&psc=1) |
| 5V 2A Wireless Charging Transmitter| 1 | $6.63 | Robu | [Robu link](https://robu.in/product/5v-2a-large-current-wireless-charger-module-transmitter-receiver-charging-coil-module/) |
| Power/kill Switch | 1 | $0.2 | robu | [link](https://robu.in/product-category/slide-switches/)| 
| Custom PCB | 1 | $13.00 | Lion Circuits | [link](https://www.lioncircuits.com/quote) |
| 3d Case | 2 | $10 | Printing legion  | [join Hack Club!!](https://printlegion.hackclub.com/)|
| **TOTAL** | | **$55.83** | | |
