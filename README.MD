# RaddedMC's SmartButton
This project is currently a work-in-progress. Most things work but there are a few small things to be ironed out...
Requirements:
 - An ESP32 or ESP8266 Microcontroller
 - An internet connection / WiFi router
 - Some webhooks!
 - Some kind of button -- the PCB is designed for a stanard 6x6mm tactile switch
 - Also helpful to have an LED and/or passive piezo -- the PCB is designed for a Murata PKMCS0909E4000-R1
 - Two resistors; values will vary, but the schematic has a 220 and 320 ohm. Use a resistor appropriate for your LED
 
Instructions:
 - Build the below circuit:
 ![Fritzing diagram of RaddedMC's SmartButton circuit](EasyButton-ESP32-BB.png)
   - If you're using an ESP8266 NodeMCU, substitute D2, D4, and D6 with the pins labelled D4, D2, and D1 respectively. The LED resistor is 320 ohm and the button pulldown resistor is 220 ohm, however, these are not strict values
   - **OR** use the PCB in the PCB folder, credits to kelvinhall05 for the design!
 - Clone the EasyButton.ino file that matches your board
 - Make sure your Arduino IDE is set up for an ESP32 or ESP8266 NodeMCU board
 - Set Wifi SSID and password, and set up webhooks of your choosing (make sure that you use http:// in your URL as opposed to https://. 
 - You can change pins to whatever you like. Helpful if you want the ESP's built-in LED to blink when you do things or if you want to use one of the touch sensor pins instead of a boring clicky button. Pinout is currently configured for both boards to be compatible with one PCB.
 
**As mentioned, this project is a work in progress. Suggestions are appreciated, and these instructions might change over time.**

Feel free to dm me on Insta @RaddedMC or Discord at RaddedMC#4791 for any questions. Video for this project is in the works!
