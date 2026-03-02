# IIMSTC_MiniProjects_Cohert_4
IIMSTC Mini Project_01 – "Password-Based Door Lock System" using Arduino, Keypad, LCD, and Servo Motor. SDG Goal: 8 – Decent Work and Economic Growth.
#  Password Based Door Lock System

##  Project Overview
This project implements a secure password-based door locking system using Arduino. 
The system allows users to enter a 4-digit password using a 4x4 keypad. 
If the password is correct, the door unlocks using a servo motor. 
If incorrect, an alert system is activated.

This project supports SDG 9 – Industry, Innovation and Infrastructure.

##  Objectives
- To design a secure electronic door lock system
- To implement password authentication
- To simulate the system using TinkerCAD
- To enhance security using attempt limitation

##  Components Used
- Arduino UNO
- 16x2 LCD Display
- 4x4 Matrix Keypad
- Servo Motor (SG90)
- Green LED
- Red LED
- Buzzer
- Resistors (220Ω)
- Breadboard
- Jumper Wires

##  Working Principle
1. User enters a 4-digit password.
2. The system compares it with the stored password.
3. If correct:
   - LCD displays "Access Granted"
   - Green LED turns ON
   - Servo rotates to unlock
4. If incorrect:
   - LCD displays "Access Denied"
   - Red LED turns ON
   - Buzzer sounds
5. After 3 wrong attempts, the system temporarily locks.



