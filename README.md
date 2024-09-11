# Simple_Calculator_Using_3SW

## Overview
This project implements a simple calculator using the ATmega32 microcontroller, an LCD for display, and three switches for user input (Enter, Up, and Down). The calculator performs basic arithmetic operations such as addition, subtraction, multiplication, division and can handle floation o/p.

## Key Components:
ATmega32 Microcontroller

16x2 LCD Display

3 Push Buttons (Enter, Up, Down)

Custom Drivers for DIO, LCD, and Switch.

## Features
User can input numbers and select operations using the switches.

The result of the operation is displayed on the LCD.

The application handles basic errors, such as division by zero.

## Hardware
ATmega32: The microcontroller that runs the calculator logic.

16x2 LCD: Displays the inputs and results.

3 Switches: Used to navigate and select operations or digits.

Up: Increases the current number or selects the next operation.

Down: Decreases the current number or selects the previous operation.

Enter: Confirms the input and performs the selected operation.

## Software Modules
The project consists of the following drivers and application layers:

1. DIO Driver:
Handles digital I/O operations for interfacing with the switches and LCD.

2. LCD Driver:
Manages interactions with the 16x2 LCD display, including initializing the display and sending data/commands for showing numbers and results.

3. Switch Driver:
Handles input from the 3 push buttons (Up, Down, Enter). It detects button presses and translates them into navigation or selection actions.

4. Application Logic:
The main application handles user inputs (numbers and operations), performs the required arithmetic, and displays the results on the LCD. It follows these steps:

    Displays a prompt to input the first number.
   
    Allows the user to select an operation (addition, subtraction, multiplication, or division).
   
    Displays a prompt to input the second number.
   
    Performs the operation and displays the result.
