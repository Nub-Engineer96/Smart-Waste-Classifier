# Smart Waste Segregation System using Arduino

## Overview

This project is an Arduino-based Smart Waste Segregation System that automatically classifies waste into Metal, Wet, and Dry categories using multiple sensors and an automated sorting mechanism.

The system aims to reduce manual waste segregation and improve waste management efficiency through sensor-based classification and motorized bin selection.

---

## Features

* Automatic waste detection
* Metal waste identification using an inductive proximity sensor
* Wet/Dry waste classification using a moisture sensor
* Servo-operated disposal flap
* Stepper motor controlled bin positioning
* Fully automated waste segregation process

---

## Components Used

* Arduino Uno
* IR Sensor Module
* Inductive Proximity Sensor
* Rain/Moisture Sensor
* Servo Motor
* 28BYJ-48 Stepper Motor
* ULN2003 Stepper Motor Driver
* Buzzer
* 18650 Li-ion Batteries
* Breadboard
* Jumper Wires

---

## Working Principle

1. The IR sensor detects the presence of waste.
2. The proximity sensor checks whether the object is metallic.
3. If metal is detected, the waste is directed to the metal compartment.
4. If metal is not detected, the moisture sensor measures the moisture content.
5. Wet waste is directed to the wet compartment.
6. Dry waste is directed to the dry compartment.
7. The servo motor opens the disposal flap.
8. The stepper motor returns the system to its default position.

---

## Repository Structure

* Arduino Code/ – Arduino source code (.ino)
* Circuit Diagram/ – Circuit schematic and wiring diagrams
* Images/ – Prototype and working model photographs
* Videos/ – Demonstration videos
* README.md – Project documentation

---

## Demonstration

Project demonstration videos are available in the Videos folder.

---

## Future Improvements

* IoT-based monitoring system
* Mobile application integration
* Machine Learning based waste classification
* Cloud-based analytics dashboard

---

## Author

Amitabha Mukhopadhyay

Department of Electrical Engineering
Indian Institute of Engineering Science and Technology, Shibpur
