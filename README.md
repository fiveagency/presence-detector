Description
===========

This is a firmware project for the STM32 microcontroller. 

Directory contents
==================

    \Libraries                # STM32 Standard Peripheral Library 
          \CMSIS  
          \STM32F10x_StdPeriph_Drive
          Makefile
    debug.c                   # Functions used for debbuging ( turn on/off corresponding 
    debug.h                   #  LED or send data to Hyperterminal )
    enc28j60.c                # Driver for ENC28J60 module 
    enc28j60.h
    gpio.c                    # Functions for init and work with GPIO ports
    gpio.h
    ip_arp_udp_tcp.c          # TCP/IP stack driver
    ip_arp_udp_tcp.h
    spi.c                     # Functions for init and work with SPI1
    spi.h
    simple_server.c           # HTTP server 
    simple_server.h
    net.h                     # TCP/IP flags
    timer.c                   # Functions for init and work with TIM2
    timer.h
    usart.c                   # Functions for init and work with USART1
    usart.h
    startup_stm32f10x_hd.c    # Board startup file
    stm32f103vet6.ld          # Linker script
    main.c                    # Main entry function
    Makefile                  # Makefile of project

      
Hardware environment
====================

This project runs on STM32 Development Board ( STM32F103VET6 ) and can be
easily tailored to any other STM32 Development Board. In addition to the
board, the following components are also used: ENC28J60 Ethernet LAN
Network Module, USB 2.0 to TTL UART 6PIN CP2102 Module and Infrared PIR
Motion Sensor Detector Module.

- STM32F103VET6 
  - CP2102 module connected to corresponding USART1 pins on board
  - MOSI, MOSI and CLK pins of ENC28J60 module connected to corresponding
    SPI1 pins on board
  - CS and RESET pins of ENC28J60 module connected to GPIOA Pin 4 and PIN 3 
    of board 
  - PIR sensor connected to GPIOA Pin 1
 
- Hyperterminal configuration:
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - BaudRate = 115200 baud
  - flow control: None 
                             
How to use it
=============

To compile the project first run `Makefile` in `Libraries` folder and then
run `Makefile` in main project folder. To burn the project firmware to a
board using _usart_ bootloader you can use tool `stm32flash`.

Example:

    stm32flash -w presence_detector.bin -v -g 0x0 /dev/ttyUSB0

Project members
===============

- Tomislav Denis
- Tomislav Grbin
- Krunoslav Zaher
