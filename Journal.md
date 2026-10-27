---
title: "KN-Pocket watch"
github: "https://github.com/Nitish5196/Pocket-watch"
description: "hii Kn-Pocket watch is a compact pocket watch which displays the time the class you have to attend/remeinders it has a deep sleep mode and you have to shake it to wake it up. it also has a vibrating motor to alert you when its time to do smth"
created_at: "2026-10-21"
total_time: "TBD"
---
## Oct 21 2026 - 8:20am: <journal Started adding components to cart>

Hiiii i selected all the components that i would need to make this project and added them to the cart , you can find the cart images below . you might wonder whts he doin with some random android wireless charger, the thing is i REALLY want to make this wireless but i cant find any wireless receiver online (why is everyone selling wireless charginf pads without receivers? what are you charging without a receiver)anyways so yea ill be using the wireless coil and pcb from tht phone charger to charge this project and another thing Rudy might say is "why do you have six 1K resistors in your cart if you only need one ?Im not funding that" thts because robu has a stupid min cart value thing tht they wont accept anything under 10inr( $.10) and the resistors,NPN and transistor cost like 2inr($0.02) so i added more to get to the min value .

<img width="1365" height="499" alt="image" src="https://github.com/user-attachments/assets/8ca870f4-f416-498a-80f6-d78fac512dd1" />
<img width="1326" height="653" alt="image" src="https://github.com/user-attachments/assets/0cb97460-bf1f-4a67-94ac-e5447f1c6f54" />
<img width="1027" height="637" alt="image" src="https://github.com/user-attachments/assets/9b903191-4d5f-4050-892a-51324a4bee16" />
<img width="944" height="417" alt="image" src="https://github.com/user-attachments/assets/1067c07e-edc2-40f2-a181-32048298ccfc" />
<img width="998" height="565" alt="image" src="https://github.com/user-attachments/assets/92946ca5-2e18-4965-a8a0-5ba1429d40df" />

**Total time spent: 1h 27mins**

## Oct 21 2026 - 10:00am: <PCB>
i used the xiao rp2040 symbol first but then i realised it didnt have a lot of pins like battery and stuff so i went to seeed studio's website to download the esp32 c6 symbol and footprint . then i realised i would not be able to solder the LIS3DH's pins so im using a breakout board for it and i changed the resistor from THT to SMD 
Sooo i made a few changes to the cart <img width="1068" height="596" alt="image" src="https://github.com/user-attachments/assets/ee700df9-833f-403c-b9ac-7092e096dc68" />
<img width="1323" height="596" alt="image" src="https://github.com/user-attachments/assets/d8d32a2d-7639-4a25-8c3e-88f7f7d1d3bb" />
Finished the Schematic and added the footprints to it <img width="690" height="246" alt="image" src="https://github.com/user-attachments/assets/ced60c6a-80eb-4eb9-a120-20007bf285f3" /><img width="946" height="561" alt="image" src="https://github.com/user-attachments/assets/1fff7a8c-34e5-4ca6-9460-1418e25e3e6e" />
finding the right components and its footprint it super hard
NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOooooooo the finished pcb (it was almost done i even added the 3d step of display and esp32 and aligned them ) it was few mins away from being finished , i didnt even get a "Kicad not responding" it just randomly closed and the restore backup folde has only schematic WHICH I ALREADY SAVED :/ ill do it again after lunch 

**Total time spent : 4hrs 35mins**

## Oct 21 2026 - 3:10pm: <PCB completed>
So i updated the pcb from schematic , created a 44mm diameter circular edge cuts , routed the components and added GND pour on the B.Cu and completed the schematic with ZERO DRC errors😼

<img width="444" height="447" alt="image" src="https://github.com/user-attachments/assets/e962f73a-a68c-4c1b-98f0-7f0845793d8a" />

<img width="644" height="485" alt="image" src="https://github.com/user-attachments/assets/a8818289-abfb-4102-8180-3033a7b5d761" />

 i also added the 3d steo of esp32, display and the switch. , thts ot the PCB IS DONE!! i might use  jumper cables/normal copper cables  to solder the pcb and the accelerometer
 
 <img width="468" height="407" alt="image" src="https://github.com/user-attachments/assets/0800401b-1875-445e-932d-210f026a2259" />

<img width="586" height="457" alt="image" src="https://github.com/user-attachments/assets/422b19bd-4224-4562-a846-f0f3ab66c404" />

Now we need to work on the firmware and case

**Total time spent :1hour**

## Oct 27 2026 <Case almost done>
Hiiii so i have been working on the case for the past week but i didnt track time properly but this is how it looks now <img width="396" height="385" alt="image" src="https://github.com/user-attachments/assets/933bc65c-1976-4572-981a-fcbf66eedb1b" />
<img width="880" height="458" alt="image" src="https://github.com/user-attachments/assets/8f01f265-8b46-4f23-aad6-ce76d40a9517" />
<img width="426" height="391" alt="image" src="https://github.com/user-attachments/assets/8b1b13c0-01b8-462e-b027-f1bcbbdcaa29" />
<img width="574" height="430" alt="image" src="https://github.com/user-attachments/assets/342facb2-139c-4ade-97a5-61803e2e599d" />
<img width="562" height="443" alt="image" src="https://github.com/user-attachments/assets/c4e6ee1d-e21d-45e8-ac99-7bc4db8a744c" />

i added 4 holes to add magnets to the lid and bottom case i MIGHT add hinges to them later , the usb port is accessible and i made the whole case in a round shape .rn it looks a bit ugly tbh but its alright cause this is just a rough case to get this submitted , the website of the components doest have the exact measurement so ill make changes to this case once i get the components and pcb to ensure the watch fits perfectly in its case . this is how the case looks as of now
### so whts left?
- need to add mounting holes to the pcb and supports for it in the case
- need to write a rough firmware for it AND IT WILL BE DONEEEEEEEEEEEEEE

** Time Spent : 3h **
