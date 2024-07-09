### RTOS
一，eLinux與Android作業系統的架構原理； 

二，eLinux與Android作業系統的開發流程； 

三，GNU Make、Makefile及Scripts； 

四，eLinux作業系統的uboot開機載入程式； 

五，eLinux作業系統核心； 

六，eLinux根檔案系統； 

七，eLinux可掛載驅動程式模組； 

八，eLinux輸出入介面控制器驅動程式。

## RTOS Repository
# Overview
This repository provides a comprehensive implementation of a Real-Time Operating System (RTOS) tailored for various embedded systems projects. The code covers multiple aspects of RTOS functionality, including task scheduling, interrupt handling, inter-task communication, and peripheral interfacing.

# Directory Structure
final/
  Contains the final version of the RTOS implementation, with fully integrated features and optimizations.

lab2_oled_example-main/
  Demonstrates the use of an OLED display with the RTOS.
Key files:
  main.c: Initializes the RTOS and OLED display, and demonstrates basic display functionalities.
  oled_driver.c: Contains driver code for interfacing with the OLED hardware.
  oled_driver.h: Header file for OLED driver declarations.
  
lab3_oled_dht11-main/
  Integrates the DHT11 temperature and humidity sensor with the OLED display.
Key files:
  main.c: Initializes the RTOS, OLED display, and DHT11 sensor, and displays sensor data on the OLED.
  dht11_driver.c: Driver code for reading data from the DHT11 sensor.
  dht11_driver.h: Header file for DHT11 sensor driver declarations.
  
lab5_16x16_matrix-main/
  Implements control of a 16x16 LED matrix using the RTOS.
Key files:
  main.c: Initializes the RTOS and controls the LED matrix display.
  led_matrix_driver.c: Contains driver code for the 16x16 LED matrix.
  led_matrix_driver.h: Header file for LED matrix driver declarations.

lab6_LED16x16_matrix-timer.main1/
  Enhances the 16x16 LED matrix control with timer-based animations.
Key files:
  main.c: Demonstrates the use of RTOS timers for animating the LED matrix.
  timer_driver.c: Implements timer functionalities for the RTOS.
  timer_driver.h: Header file for timer driver declarations.
  
lab7_st7789-main1/
  Demonstrates the use of the ST7789 display with the RTOS.
Key files:
  main.c: Initializes the RTOS and the ST7789 display, and demonstrates basic display functionalities.
  st7789_driver.c: Driver code for interfacing with the ST7789 display.
  st7789_driver.h: Header file for ST7789 driver declarations.
  
lab8_ethernet_server-main/
  Implements a basic Ethernet server using the RTOS.
Key files:
  main.c: Initializes the RTOS and sets up the Ethernet server.
  ethernet_driver.c: Contains driver code for Ethernet communication.
  ethernet_driver.h: Header file for Ethernet driver declarations.
  
# Key Features
Task Scheduling: Implements priority-based preemptive scheduling for real-time task management.

Interrupt Handling: Efficiently handles hardware interrupts to ensure real-time responsiveness.

Inter-task Communication: Provides mechanisms like semaphores, queues, and event flags for safe and efficient inter-task communication.

Peripheral Drivers: Includes drivers for various peripherals like OLED displays, DHT11 sensors, LED matrices, ST7789 displays, and Ethernet interfaces.
