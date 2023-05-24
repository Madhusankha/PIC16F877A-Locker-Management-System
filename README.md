# PIC16F877A-Locker-Management-System :lock:

### A smart locker management system represents a contemporary and robust approach to storing personal belongings. The system's design aims to offer users convenience, security, and flexibility. This is a PIC microcontroller (PIC16F877A) based design.

## Hardware Components:

+ PIC Microcontroller (PIC16F877A)

+ Keypad

+ LCD display

+ LEDs (Red and Green)

+ Buzzer

+ Servo Motors

## Working of the System:

**Initialization:** The system is initialized by setting up the microcontroller (PIC16F877A), configuring the necessary pins for input/output, initializing the LCD display, and keypad.

**Main Menu:** The system starts by displaying a main menu on the LCD screen, allowing the user to select between the "Admin" and "Customer" options.

![3](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/075ffdbb-6288-4874-b693-a8802eca5848)


**Admin Menu:** If the user selects the "Admin" option, they are prompted to enter a password. If the entered password matches the predefined password, the user gains access to the admin menu.

![4](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/6a80a9ce-a99d-41ac-b158-92dae5619669)

A: Add Locker | B: Remove Locker | C: Display Locker Status | D: Set Locker Status | #: Exit

+ Add Locker: The admin can choose to add a new locker by entering the locker number and setting an access code for it. The access code is a 4-digit code entered through the keypad, and the locker status is initially set to "UNLOCKED."

+ Remove Locker: The admin can remove an existing locker by entering the locker number. The system checks if the locker is empty (UNLOCKED), and if so, it is removed from the system.

+ Display Locker Status: The admin can view the status of all lockers on the LCD screen. The status is indicated by "U" for unlocked and "L" for locked.

+ Set Locker Status: The admin can manually set the status of a locker by entering the locker number and selecting either "U" for unlocked or "L" for locked.

**Customer Menu:** If the user selects the "Customer" option, they are prompted to enter a locker number. Once a valid locker number is entered, the user is prompted to enter a 4-digit access code.

![c1](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/c74e98ea-f642-4abb-bfbe-1100a232d9fa)

**Validate Access Code:** The system checks if the entered access code matches the stored access code for the locker. If the codes match, the locker is considered unlocked and the user gains access.

![c2](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/6b7046ca-58d1-4ed4-be32-94293b801ec4) 
![c3](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/de67b199-3f63-4cd7-9f06-16ce7372e35e)

**Invalid Code:** If the access code is invalid, the system increments the number of attempts for that locker and alerts the user with an "INVALID CODE" message on the LCD screen. If the number of attempts exceeds the maximum allowed attempts (MAX_ATTEMPTS), the system triggers a buzzer and indicates a failed attempt by turning on the red LED.

![c6](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/8693a5d2-7fc9-47b3-a364-89ec467f414a)

**Successful Access:** If the access code is valid, the system unlocks the locker by activating the necessary components and displays a "STATUS: UNLOCKED" message on the LCD screen.

![c5](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/ccf376d8-ac82-4519-bee4-cfbeb4e33b20)

**Lock the Locker:** After accessing the locker, the user has the option to manually lock it by pressing the 'D' key. Upon locking the locker, the system updates the status to "LOCKED" and displays a "LOCKED" message on the LCD screen.

![c4](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/002e0054-9e7a-47d9-ba37-1e65f493fca2)

**Quit:** The user can quit the customer menu at any time by pressing the '#' key.

**Buzzer and LED:** Throughout the process, the system controls the buzzer and LED lights to provide audio and visual feedback to the user. The buzzer is activated for invalid access codes and when the maximum attempts are reached. The green LED indicates successful access, while the red LED indicates a failed attempt.

**Locker Status Update:** The system keeps track of the status, attempts, and timer for each locker, allowing the admin to monitor and manage the lockers effectively.


## Circuit Diagram

![02](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/6077ea0b-0f60-460f-a7a5-76982fa58fc4)

['/' -> 'A'],
['X' -> 'B'], 
['-' -> 'C'], 
['+' -> 'D'], 
['ON/C' -> '#']


