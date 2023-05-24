// Function name: InitKeypad
void keypad_init(void)
{
    Keypad_PORT      = 0x00;  // Set Keypad port pin values zero
    Keypad_PORT_Dir = 0xF0;  // Last 4 pins input, First 4 pins output
    // Enable weak internal pull up on input pins
    //OPTION_REG &= 0x7F;
}

// Scan all the keypad keys to detect any pressed key.
char READ_SWITCHES(void)  
{  
  RowA = 1; RowB = 0; RowC = 0; RowD = 0;   //Test Row A 
  if (C1 == 1) { __delay_ms(250); while ( C1==1 ); return '7'; }
  if (C2 == 1) { __delay_ms(250); while (C2==1); return '8'; }
  if (C3 == 1) { __delay_ms(250); while (C3==1); return '9'; }
  if (C4 == 1) { __delay_ms(250); while (C4==1); return 'A'; }
  
  RowA = 0; RowB = 1; RowC = 0; RowD = 0;   //Test Row B
  if (C1 == 1) { __delay_ms(250); while (C1==1); return '4'; }
  if (C2 == 1) { __delay_ms(250); while (C2==1); return '5'; }
  if (C3 == 1) { __delay_ms(250); while (C3==1); return '6'; }
  if (C4 == 1) { __delay_ms(250); while (C4==1); return 'B'; }

  
  RowA = 0; RowB = 0; RowC = 1; RowD = 0;   //Test Row C
  if (C1 == 1) { __delay_ms(250); while (C1==1); return '1'; }
  if (C2 == 1) { __delay_ms(250); while (C2==1); return '2'; }
  if (C3 == 1) { __delay_ms(250); while (C3==1); return '3'; }
  if (C4 == 1) { __delay_ms(250); while (C4==1); return 'C'; }

  
  RowA = 0; RowB = 0; RowC = 0; RowD = 1;   //Test Row D
  if (C1 == 1) { __delay_ms(250); while (C1==1); return '#'; }
  if (C2 == 1) { __delay_ms(250); while (C2==1); return '0'; }
  if (C3 == 1) { __delay_ms(250); while (C3==1); return '='; }
  if (C4 == 1) { __delay_ms(250); while (C4==1); return 'D'; }

  return 'n';             // Means no key has been pressed
}


// Function name: GetKey
// Read pressed key value from keypad and return its value
char getkey(void)              // Get key from user
{
    char key = 'n';              // Assume no key pressed
    while(key=='n')              // Wait until a key is pressed
        key = READ_SWITCHES();   // Scan the keys again and again
    return key;                  //when key pressed then return its value
}

// Function name: keypad_getint
// Read a sequence of digits from the keypad and return their integer value
int keypad_getint(void)
{
    char digit;
    int value = 0;
    while(1) {
        digit = getkey();
        if (digit >= '0' && digit <= '9') {
            value = value * 10 + (digit - '0');
            // Wait for key release
            while (READ_SWITCHES() != 'n');
            // Display the digit on an LCD or other output device if desired
        } else if (digit == '=') {
            // Wait for key release
            while (READ_SWITCHES() != 'n');
            // Return the final value
            return value;
        }
    }
}