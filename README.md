# PIC16F877A-Locker-Management-System :lock:

### A smart locker management system represents a contemporary and robust approach to storing personal belongings. The system's design aims to offer users convenience, security, and flexibility. This is a PIC microcontroller (PIC16F877A) based design.

## Working of the System:

**Initialization:** The system is initialized by setting up the microcontroller (PIC16F877A), configuring the necessary pins for input/output, initializing the LCD display, and keypad.

**Main Menu:** The system starts by displaying a main menu on the LCD screen, allowing the user to select between the "Admin" and "Customer" options.

![3](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/fc75365a-dc95-43cf-ae6d-586d4889fc3f)

**Admin Menu:** If the user selects the "Admin" option, they are prompted to enter a password. If the entered password matches the predefined password, the user gains access to the admin menu.


![4](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/0c85a358-07f0-463d-a631-587b34be6e04)

A: Add Locker | B: Remove Locker | C: Display Locker Status | D: Set Locker Status | #: Exit

+ Add Locker: The admin can choose to add a new locker by entering the locker number and setting an access code for it. The access code is a 4-digit code entered through the keypad, and the locker status is initially set to "UNLOCKED."

+ Remove Locker: The admin can remove an existing locker by entering the locker number. The system checks if the locker is empty (UNLOCKED), and if so, it is removed from the system.

+ Display Locker Status: The admin can view the status of all lockers on the LCD screen. The status is indicated by "U" for unlocked and "L" for locked.

+ Set Locker Status: The admin can manually set the status of a locker by entering the locker number and selecting either "U" for unlocked or "L" for locked.

**Customer Menu:** If the user selects the "Customer" option, they are prompted to enter a locker number. Once a valid locker number is entered, the user is prompted to enter a 4-digit access code.

![c1](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/a28badc3-28b3-46fe-9ee9-3631ad951ad3) 

**Validate Access Code:** The system checks if the entered access code matches the stored access code for the locker. If the codes match, the locker is considered unlocked and the user gains access.

![c2](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/f26a7481-159a-4e4d-8b6e-ffae8ae39f6e) ![c3](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/e695b15c-5d2a-4907-a08d-9eef6e16a88a)

**Invalid Code:** If the access code is invalid, the system increments the number of attempts for that locker and alerts the user with an "INVALID CODE" message on the LCD screen. If the number of attempts exceeds the maximum allowed attempts (MAX_ATTEMPTS), the system triggers a buzzer and indicates a failed attempt by turning on the red LED.

![c6](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/1ad9c1dc-32e6-43bc-8022-a450622ea467)

**Successful Access:** If the access code is valid, the system unlocks the locker by activating the necessary components and displays a "STATUS: UNLOCKED" message on the LCD screen.

![c5](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/e0536f64-85ee-480b-9bc7-ca2b0058f2f0)

**Lock the Locker:** After accessing the locker, the user has the option to manually lock it by pressing the 'D' key. Upon locking the locker, the system updates the status to "LOCKED" and displays a "LOCKED" message on the LCD screen.

![c4](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/112b1b40-af1d-40dc-b951-0a8aeb53eb57)

**Quit:** The user can quit the customer menu at any time by pressing the '#' key.

**Buzzer and LED:** Throughout the process, the system controls the buzzer and LED lights to provide audio and visual feedback to the user. The buzzer is activated for invalid access codes and when the maximum attempts are reached. The green LED indicates successful access, while the red LED indicates a failed attempt.

**Locker Status Update:** The system keeps track of the status, attempts, and timer for each locker, allowing the admin to monitor and manage the lockers effectively.


## Circuit Diagram

![02](https://github.com/Madhusankha/PIC16F877A-Locker-Management-System/assets/42806288/0d79e291-726e-4cfe-be96-fee638072e0a)

['/' -> 'A'],
['X' -> 'B'], 
['-' -> 'C'], 
['+' -> 'D'], 
['ON/C' -> '#']


