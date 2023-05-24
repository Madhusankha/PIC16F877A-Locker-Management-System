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


