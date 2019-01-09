# ME433spring
## Overview
This repository contains the documentation for assignments in Mechanical Engineering 433: Advanced mechatronics. Over the course of the quarter I learned a variety of skills including circuit board design, communication protocols and familiarized myself with sophisticated software and hardware platforms. I eventually used all of these skills to design a mobile robot which used visual data to follow a path. 
### Couse Info
Professor: Nick Marchuk
Course Page: [ME 433](https://github.com/ndm736/ME433_2018/wiki)
### Hardware
[PIC32MX250 Microcontroller](http://ww1.microchip.com/downloads/en/DeviceDoc/PIC32MX1XX2XX-28-36-44-PIN-DS60001168K.pdf),
[MCP1702 Voltage Regulator](http://ww1.microchip.com/downloads/en/DeviceDoc/22008E.pdf),
[8MHz crystal resonator](https://www.digikey.com/products/en?keywords=490-1212-ND),
[USB breakout board](https://www.pololu.com/product/2593),
[TFT LCD](https://www.aliexpress.com/item/Free-Shipping-1-8-inch-TFT-touch-LCD-Module-LCD-Screen-Module-SPI-serial-51-drivers/32263827143.html),
[I/O Expander](http://ww1.microchip.com/downloads/en/DeviceDoc/21919e.pdf),
[IMU](https://www.pololu.com/product/2736),
[Android Phone](https://www.amazon.com/gp/product/B00HPP3VW2/ref=oh_aui_detailpage_o00_s00?ie=UTF8&psc=1)
### Tools
Eagle, Onshape
### Languages
C, Java, Matlab
## HW1
In the first assignment I familiarized myself with the PIC32 microcontroller and its peripheral components and assembled a general puropose circuit board for the coming assignments. The ojective of the assignment was to build our circuit board and demonstrate that it could make an LED blink at a frequency of 1kHz. [HW1 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW1).
<img src="https://github.com/rohananthony95/me433spring/blob/master/HW1/hw1breadb.JPG"  width="240" height="240">
## HW2
In the second assignment I designed an EAGLE schematic of my original circuit. [HW2 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW2).
<img src="https://github.com/rohananthony95/me433spring/blob/master/HW3/HW3s.png"  width="240" height="240">
## HW3
Designed PCB and generated Gerber files. [HW3 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW3).
## HW4
In the fourth assignment I added an SPI DAC to our original circuit board configuration. I created functions to initialize and communicate with the DAC. The DAC output both a sine wave as well as a triangle wave. [HW4 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW4). 
<img src="https://github.com/rohananthony95/me433spring/blob/master/HW4/hw4.png"  width="240" height="240">
## HW5
Here I incorporated an pin expander to my breadboard and communicated to it using the I2C protocol. [HW5 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW5).
[HW5 demo download](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/rohananthony95/me433spring/blob/master/HW5/HW5.MOV).
## HW6
In this assignment I added an LCD module to my circuit board and communicated with it using SPI. [HW6 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW6).
[HW6 demo download](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/rohananthony95/me433spring/blob/master/HW6/HW6.mov).
## HW7
I added an I2C accelerometer to the board and wrote a program that displayed the orientation of the board on the LCD. [HW7 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW7).
[HW7 demo download](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/rohananthony95/me433spring/blob/master/HW7/HW7.MOV).
## HW8
The objective here was to implement the previous assignment in MPLABX Harmony. [HW8 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW9).
## HW9
The goal of this assignment was to configure the microcontroller to communicate with my computer using USB. [HW9 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW9).
[HW9 demo download](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/rohananthony95/me433spring/blob/master/HW9/HW9.MOV).
## HW10
I analyzed the gyroscope data sent to the computer via USB with FIR, IIR, and MAV filters. [HW10 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW10).
<img src="https://github.com/rohananthony95/me433spring/blob/master/HW10/processing/hw10.png"  width="240" height="240">
## HW11
The objective of this assignment was to control the cursor of my computer with the gyroscope of my circuit board. [HW11 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW11).
[HW11 demo download](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/rohananthony95/me433spring/blob/master/HW11/HW11.MOV).
## HW12
Here I familiarized myself with Android and wrote a simple application with a clean interface and basic modules like a slider.
[HW12 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW12).
## HW13
I wrote an Android application that could recognize green objects in the field of view of the camera. 
[HW13 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW13).
[HW13 demo download](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/rohananthony95/me433spring/blob/master/HW13/HW13.MOV).
## HW14
The purpose of this assignment was to make an Android application which could send data to the microcontroller and have that data returned back to the application demonstrating communication using USB. [HW14 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW14).
[HW14 demo download](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/rohananthony95/me433spring/blob/master/HW14/HW14.MOV).
## HW15
I created a base and wheels for the robot using CAD. I 3D printed the wheels and laser cut the frame of the robot using acrylic. [HW15 assignment description]
(https://github.com/ndm736/ME433_2018/wiki/HW15).
<img src="https://github.com/rohananthony95/me433spring/blob/master/HW15/base.png"  width="240" height="240"> 
<img src="https://github.com/rohananthony95/me433spring/blob/master/HW15/wheel.png"  width="240" height="240">
<img src="https://github.com/rohananthony95/me433spring/blob/master/HW15/side.png"  width="240" height="240">
## HW16
Wrote a simple PI controller for the wheel velocity of my robot. [HW16 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW16).
## HW17
Wrote the Android application to find the center of a rainbow line. [HW17 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW17).
## HW18
Combined all of the components and had a finished robot which followed a rainbow path. [HW18 assignment description](https://github.com/ndm736/ME433_2018/wiki/HW18).
