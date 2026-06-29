# ⏰ Time-Driven Access Control System

An embedded security system developed using the **LPC2148 (ARM7)** microcontroller that grants or denies access based on a user-defined password and scheduled access time. The system displays real-time clock information, allows users to edit RTC and schedule settings through a 4×4 keypad, and provides secure access control using password authentication.

---

## 📌 Project Overview

The Time-Driven Access Control System is designed to provide controlled access based on predefined time schedules. The system continuously displays the current date, time, and day using the LPC2148's internal RTC. Users can configure the RTC and access schedule through a keypad, while password authentication ensures only authorized users gain access within the permitted time window.

---

## ✨ Features

- Real-Time Clock (RTC) display
- Displays current Time, Date, and Day on 16×2 LCD
- Password-protected access system
- Scheduled time-based access control
- Edit RTC information through keypad
- Edit scheduled access time
- Interrupt-driven menu system
- Password masking using '*'
- Wrong password detection
- Out-of-time access restriction
- LED/Buzzer indication for access status

---

## 🛠 Hardware Requirements

- LPC2148 ARM7 Microcontroller
- 16×2 LCD Display
- 4×4 Matrix Keypad
- Push Buttons (Switch1 & Switch2)
- LED / Buzzer
- USB-UART Converter / DB9 Cable
- 3.3V Power Supply

---

## 💻 Software Requirements

- Embedded C
- Keil μVision
- Flash Magic
- Proteus (Simulation)

---

## 📖 System Operation

### Normal Mode

- Initializes RTC, LCD, Keypad, and Interrupts.
- Displays:
  - Current Time
  - Current Date
  - Day of the Week
- Waits for user interaction.

### Password Authentication

- Press **Switch1** to enter password mode.
- Enter the password using the 4×4 keypad.
- Press **'='** to submit.
- If:
  - Password is correct
  - Current RTC time matches the scheduled access time
- Then:
  - Access is granted.
- Otherwise:
  - Wrong Password
  - or
  - Out of Scheduled Time

---

## ⚙ Interrupt Menu

Press **Switch2** to generate an external interrupt.

The following menu appears:

```
1. Edit RTC Information
2. Edit Schedule Time
3. Exit
```

Users can update:

- Hours
- Minutes
- Seconds
- Date
- Month
- Year
- Scheduled Access Time

After editing, the system returns to normal monitoring mode.

---

## 🔑 Keypad Layout

```
+-----+-----+-----+-----+
|  7  |  8  |  9  |  %  |
+-----+-----+-----+-----+
|  4  |  5  |  6  |  =  |
+-----+-----+-----+-----+
|  1  |  2  |  3  |  -  |
+-----+-----+-----+-----+
|  *  |  0  |  #  |  +  |
+-----+-----+-----+-----+
```

### Key Functions

| Key | Function |
|------|----------|
| 0–9 | Numeric Input |
| = | Enter / Confirm |
| - | Delete Previous Digit |
| + | Reserved |
| * | Reserved |
| # | Reserved |
| % | Reserved |

---

## 📂 Project Structure

```
Time-Driven-Access-Control-System/
│
├── main.c
├── rtc.c
├── rtc.h
├── lcd.c
├── lcd.h
├── keypad.c
├── keypad.h
├── interrupts.c
├── interrupts.h
├── delay.c
├── delay.h
├── types.h
├── lcd_defines.h
├── Proteus/
│   └── TimeDrivenAccessControl.pdsprj
├── README.md
└── Images/
```

---

## 🔄 Program Flow

```
Start
   │
   ▼
Initialize RTC
Initialize LCD
Initialize Keypad
Initialize Interrupts
   │
   ▼
Display Time, Date & Day
   │
   ▼
Switch1 Pressed?
   │
 ┌─No──────────────┐
 │                 │
 ▼                 │
Continue Display   │
                   │
                   ▼
Enter Password
   │
   ▼
Password Correct?
   │
 ┌─No──────────────► Wrong Password
 │
 ▼
Within Scheduled Time?
 │
 ┌─No──────────────► Out of Time
 │
 ▼
Access Granted
 │
 ▼
Return to Main Screen
```

---

## 🚀 How to Run

1. Open the project in **Keil μVision**.
2. Build the project.
3. Generate the HEX file.
4. Open the Proteus simulation.
5. Load the generated HEX file into the LPC2148.
6. Run the simulation.
7. Use:
   - **Switch1** → Password Authentication
   - **Switch2** → Edit RTC / Schedule

---

## 🎯 Learning Outcomes

- LPC2148 GPIO Programming
- Internal RTC Programming
- External Interrupts (EINT1)
- Matrix Keypad Interfacing
- LCD Interfacing
- Password Authentication
- Time-Based Access Control
- Embedded C Driver Development
- Menu-Driven Embedded Applications

---

## 📸 Demonstration

- Circuit Diagram
  <img width="1272" height="882" alt="Screenshot 2026-06-29 185734" src="https://github.com/user-attachments/assets/0fbf9ec8-132a-411f-a3d0-205dbf0232e6" />
- LCD Output Images
 <img width="1260" height="885" alt="Screenshot 2026-06-29 190043" src="https://github.com/user-attachments/assets/8053ddb2-09fe-450b-99ff-8c9bf3993600" />
- Password Authentication Demo
  <img width="1282" height="890" alt="Screenshot 2026-06-29 190254" src="https://github.com/user-attachments/assets/5ac36613-848f-45c6-b15c-8676bf9939af" />
- RTC Editing Menu
<img width="1271" height="890" alt="Screenshot 2026-06-29 190454" src="https://github.com/user-attachments/assets/0b4ec898-a54f-47fb-8c5f-0872d69e29a2" />
---

## 👨‍💻 Author

**Nayeni Tagore**

Aspiring Embedded Firmware Engineer

### Skills

- Embedded C
- ARM7 (LPC2148)
- Embedded Systems
- UART
- SPI
- I2C
- RTC
- External Interrupts
- GPIO Programming

---

## 📜 License

This project is developed for educational and learning purposes.
