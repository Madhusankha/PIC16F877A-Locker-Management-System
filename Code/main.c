/*
 * File:   main.c
 * Author: Pasindu
 *
 * Created on May 17, 2023, 8:45 PM
 */


#include <pic16f877a.h>
#include <xc.h>
#define _XTAL_FREQ 8000000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pic.h>
#include <ctype.h>
#include <stdint.h>


#define RS RE0
#define EN RE1
#define D4 RD0
#define D5 RD1
#define D6 RD2
#define D7 RD3

#define RowA RB0
#define RowB RB1
#define RowC RB2
#define RowD RB3
#define C1 RB4
#define C2 RB5
#define C3 RB6
#define C4 RB7

#define Keypad_PORT PORTB
#define Keypad_PORT_Dir TRISB

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include "lcd.h"
#include "keypad.h"
//#include "Servo.h"

// Define constants
#define MAX_LOCKERS 4
#define MAX_ATTEMPTS 3
#define LOCK_TIME 10000  // Lock time in seconds
#define UNLOCKED 0
#define TUNLOCKED 2
#define LOCKED 1

// Define pins
#define LED_GREEN RA0
#define LED_RED RA1
#define BUZZER RA2


#define SERVO_1 RC1 
#define SERVO_2 RC2
#define SERVO_3 RC3
#define SERVO_4 RC4

// Define variables
unsigned char locker_status[MAX_LOCKERS];
unsigned char locker_code[MAX_LOCKERS][4];
unsigned char locker_timer[MAX_LOCKERS];
unsigned char locker_attempts[MAX_LOCKERS];


// Function prototypes
void setup();
void admin_menu();
void customer_menu();
void add_locker();
void remove_locker();
void set_locker_status();
void display_locker_status();
unsigned char validate_access_code(unsigned char locker_number);
void lock(unsigned char locker_number);
void unlock(unsigned char locker_number);
void update_locker_status();
void update_locker_timer();
void display_locker_led();
void display_locker_lcd(unsigned char locker_number);
void buzzer_on();
void buzzer_off();
void quit(unsigned char locker_number);

void main() {
    setup();
    lcd_clear();
    lcd_gotoxy(1, 3);
    lcd_puts("SELECT OPTION");
    __delay_ms(1000);
    unsigned char key;
    
    while (1) {
        lcd_clear();
        lcd_gotoxy(1, 2);
        lcd_puts("ADMIN  CUSTOMER");
        lcd_gotoxy(2, 4);
        lcd_puts("A");
        lcd_gotoxy(2, 13);
        lcd_puts("C");
        key = getkey();
        
        switch (key) {
            case 'A':
                admin_menu();
                break;
            case 'C':
                customer_menu();
                break;
            case '#':
                continue;
        }
    }
}

void setup() {
    ADCON1 = 0x07;
    TRISD = 0X00;
    TRISE = 0X00;
    TRISB = 0Xff;
    TRISA = 0x00;
    TRISC = 0x00;  // Set all C pins as output
    
    LED_GREEN = 0;  // Turn off green LED
    LED_RED = 0;  // Turn off red LED
    BUZZER = 0;  // Turn off buzzer
    //SERVO = 0;  // Set servo to 0 degrees
    
    TRISAbits.TRISA3 = 0; 
    unsigned char i;
    
    lcd_init();  // Initialize LCD
    keypad_init();  // Initialize keypad
    
    for(i=0; i<MAX_LOCKERS; i++) {
        locker_status[i] = UNLOCKED;  // Set all lockers to unlocked initially
        locker_timer[i] = 0;  // Set all timers to 0 initially
        locker_attempts[i] = 0;  // Set all attempts to 0 initially
    }
    
}

void admin_menu() {
    unsigned char key;
    
    unsigned char admin[4];
    unsigned char i;
    int pass = 6789;
    lcd_clear();
    lcd_gotoxy(1, 1);
    lcd_puts("ENTER PASSWORD:");
    lcd_gotoxy(2, 1);
    
    for(i=0; i<4; i++) {
        admin[i] = getkey();
        lcd_putc('*');
        if(admin[i] == '#'){
            break;
        }
    }
    
    if(pass == atoi(admin)){
        while (1) {
            
            lcd_clear();
            lcd_gotoxy(1, 2);
            lcd_puts("A-ADD B-REMOVE");
            lcd_gotoxy(2, 2);
            lcd_puts("C-CS D-SS #-EX");

            key = getkey();
            
            switch (key) {
                case 'A':
                    add_locker();
                    break;
                case 'B':
                    remove_locker();
                    break;
                case 'C':
                    display_locker_status();
                    break;
                case 'D':
                    set_locker_status();
                    break;    
                case '#':
                    return;
                case '*':
                    continue;
            }
        }
    }
    else{
        lcd_clear();
        lcd_gotoxy(1, 1);
        lcd_puts("INVALID PASSWORD");
        LED_RED = 1;
        __delay_ms(1000);
        LED_RED = 0;
        lcd_clear();
    } 
}

void customer_menu() {
    unsigned char locker_number, access_code[5], i, key, status;
    lcd_clear();
    lcd_gotoxy(1, 2);
    lcd_puts("ENTER LOCKER NO.");
    
    while (1) {
        key = getkey();
        
        if (isdigit(key)) {
            locker_number = key - '0';
            if (locker_number > MAX_LOCKERS) {
                buzzer_on();
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("INVALID LOCKER");
                __delay_ms(1000);
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("ENTER LOCKER NO.");
                continue;
            } else {
                break;
            }
        }
    }
    
    lcd_clear();
    lcd_gotoxy(1, 1);
    lcd_puts("ACCESS CODE");
    
    for (i = 0; i < 4; i++) {
        key = getkey();
        access_code[i] = key;
        lcd_gotoxy(2, i+1);
        lcd_putc('*');
    }
    
    access_code[4] = '\0';
    status = validate_access_code(locker_number);
    
    while(1){
      if (strcmp(locker_code[locker_number], access_code) == 0) {
        buzzer_off();
        lcd_gotoxy(1, 2);
        lcd_clear();
        unlock(locker_number);
      } 
      else{
        locker_attempts[locker_number]++;
        buzzer_on();
        lcd_clear();
        lcd_gotoxy(1, 2);
        lcd_puts("INVALID CODE");
        __delay_ms(1000);
        lcd_clear();
        if (locker_attempts[locker_number] >= MAX_ATTEMPTS) {
            buzzer_on();
            LED_RED = 1;
            __delay_ms(2000);  
            buzzer_off();
            LED_RED = 0;
            //lock(locker_number);
        }
        break;
    }
    //quit(locker_number);
      lcd_clear();
      lcd_gotoxy(1, 1);
      lcd_puts("STATUS:UNLOCKED");
      lcd_gotoxy(2, 1);
      lcd_puts("TO LOCK : D");
      key = getkey();
        if (key == 'D') {
        //buzzer_on();
            lcd_clear();
            lcd_gotoxy(1, 2);
            lcd_puts("LOCKED");
            __delay_ms(1000);
            lcd_clear();
            lock(locker_number);
            return;
    } 
    }
}

void add_locker() {
    unsigned char locker_number, key;
    
    lcd_clear();
    lcd_gotoxy(1, 2);
    lcd_puts("ENTER LOCKER NO.");
    
    while (1) {
        key = getkey();
        if(key == '#'){
            return;
        }
        if (isdigit(key)) {
            locker_number = key - '0';
            if (locker_number > MAX_LOCKERS) {
                buzzer_on();
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("INVALID LOCKER");
                __delay_ms(1000);
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("ENTER LOCKER NO.");
                continue;
            } else if (locker_status[locker_number] != UNLOCKED) {
                buzzer_on();
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("LOCKER IN USE");
                __delay_ms(1000);
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("ENTER LOCKER NO.");
                continue;
            } else {
                break;
            }
        }
    }
    
    lcd_clear();
    lcd_gotoxy(1, 2);
    lcd_puts("SET ACCESS CODE");
    
    for (unsigned char i = 0; i < 4; i++) {
        key = getkey();
        locker_code[locker_number][i] = key;
        lcd_gotoxy(2, i+1);
        lcd_putc('*');
        
    }
    
    locker_code[locker_number][4] = '\0';
    locker_attempts[locker_number] = 0;
    lock(locker_number);
}

void remove_locker() {
    unsigned char locker_number, key;
    
    lcd_clear();
    lcd_gotoxy(1, 2);
    lcd_puts("ENTER LOCKER NO.");
       
    while (1) {
        key = getkey();
        if(key == '#'){
            return;
        }
        
        if (isdigit(key)) {
            locker_number = key - '0';
            if (locker_number > MAX_LOCKERS) {
                buzzer_on();
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("INVALID LOCKER");
                __delay_ms(1000);
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("ENTER LOCKER NO.");
                continue;
            } else if (locker_status[locker_number] != LOCKED) {
                buzzer_on();
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("LOCKER EMPTY");
                __delay_ms(1000);
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("ENTER LOCKER NO.");
                continue;
            } else {
                break;
            }
        }
    }
    unlock(locker_number);
    locker_status[locker_number] = UNLOCKED;
    lcd_clear();
    lcd_gotoxy(1, 2);
    lcd_puts("LOCKER REMOVED");
    __delay_ms(1000);
    lcd_clear();
    
}

void set_locker_status() {
    unsigned char locker_number, status, key;
    char lable;
    
    lcd_clear();
    lcd_gotoxy(1, 2);
    lcd_puts("ENTER LOCKER NO.");
    
    while (1) {
        key = getkey();
        if(key == '#'){
            return;
        }
        
        if (isdigit(key)) {
            locker_number = key - '0';
            if (locker_number > MAX_LOCKERS) {
                buzzer_on();
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("INVALID LOCKER");
                __delay_ms(1000);
                lcd_clear();
                lcd_gotoxy(1, 2);
                lcd_puts("ENTER LOCKER NO.");
                continue;
            } else {
                break;
            }
        }
    }
    if (locker_status[locker_number] != UNLOCKED){
        lcd_clear();
        lcd_gotoxy(1, 1);
        lcd_puts("SET LOCKER STATUS");
        //lcd_gotoxy(2, 2);
        //lcd_puts("STATUS");
        lcd_gotoxy(2, 4);
        lcd_puts("U:1 ");
        lcd_gotoxy(2, 11);
        lcd_puts("L:2");
        key = getkey();
    
        switch (key) {
            case '1':
                status = TUNLOCKED;
                unlock(locker_number);
                lable = 'U';
                break;
            case '2':
                status = LOCKED;
                lock(locker_number);
                lable = 'L';
                break;
        }
        
        locker_status[locker_number] = status;
        lcd_clear();
        lcd_gotoxy(1, 2);
        lcd_puts("STATUS SET:");
        lcd_gotoxy(1, 14);
        lcd_putc(lable);
        __delay_ms(1500);
        lcd_clear();
        
    }
    else{
        lcd_clear();
        lcd_gotoxy(1, 4);
        lcd_puts("LOCKER  NOT");
        lcd_gotoxy(2, 5);
        lcd_puts("AVAILABLE");
        __delay_ms(1000);
        lcd_clear();
    }
}

void display_locker_status() {
    
    unsigned char i;
    lcd_clear();
    lcd_gotoxy(1, 1);
    lcd_puts("LOCKER STATUS");
    for(i=0; i<=MAX_LOCKERS; i++) {
        if(locker_status[i] == UNLOCKED) {
            lcd_gotoxy(2, i);
            lcd_puts("U");
            //lcd_puts(" ");
        }
        else if(locker_status[i] == TUNLOCKED) {
            lcd_gotoxy(2, i);
            lcd_puts("U");
            //lcd_puts(" ");
        }
        else {
            lcd_gotoxy(2, i);
            lcd_puts("L");
            //lcd_puts(" ");
        }
        //lcd_puts(" ");
    }
    __delay_ms(3000);
}

unsigned char validate_access_code(unsigned char locker_number) {
    if (locker_status[locker_number] == LOCKED) {
        return LOCKED;
    } else {
        return UNLOCKED;
    }
}

void lock(unsigned char locker_number) {
    
    switch (locker_number) {
        case 1:
            SERVO_1 = 1;
            __delay_us(800);
            //__delay_us(angle + 600);
            SERVO_1 = 0;
            break;
        case 2:
            SERVO_2 = 1;
            __delay_us(800);
            //__delay_us(angle + 600);
            SERVO_2 = 0;
            break;
        case 3:
            SERVO_3 = 1;
            __delay_us(800);
            //__delay_us(angle + 600);
            SERVO_3 = 0;
            break;
        case 4:
            SERVO_4 = 1;
            __delay_us(800);
            //__delay_us(angle + 600);
            SERVO_4 = 0;
            break;
    }
        //servo_rotate(locker_number, 0);
        locker_status[locker_number] = LOCKED;
        locker_timer[locker_number] = 0;
        display_locker_lcd(locker_number);  
     
}

void unlock(unsigned char locker_number) {

        switch (locker_number) {
        case 1:
            SERVO_1 = 1;
            __delay_us(1500);
            //__delay_us(angle + 600);
            SERVO_1 = 0;
            break;
        case 2:
            SERVO_2 = 1;
            __delay_us(1500);
            //__delay_us(angle + 600);
            SERVO_2 = 0;
            break;
        case 3:
            SERVO_3 = 1;
            __delay_us(1500);
            //__delay_us(angle + 600);
            SERVO_3 = 0;
            break;
        case 4:
            SERVO_4 = 1;
            __delay_us(1500);
            //__delay_us(angle + 600);
            SERVO_4 = 0;
            break;
    }
        
    //servo_rotate(locker_number, 180);
    locker_status[locker_number] = UNLOCKED;
    locker_timer[locker_number] = 0;
    display_locker_lcd(locker_number);    
}

void update_locker_status() {
    for (unsigned char i = 0; i < MAX_LOCKERS; i++) {
        if (locker_status[i] == LOCKED && locker_timer[i] > 0) {
            locker_timer[i]--;
            if (locker_timer[i] == 0) {
                lock(i);
            }
        }
    }
}

void update_locker_timer() {
    for (unsigned char i = 0; i < MAX_LOCKERS; i++) {
        if (locker_status[i] == LOCKED) {
            locker_timer[i]--;
            if (locker_timer[i] == 0) {
                lock(i);
            }
        }
    }
}

void display_locker_led() {
    for (unsigned char i = 0; i < MAX_LOCKERS; i++) {
        if (locker_status[i] == LOCKED) {
            LED_RED = 1;
            LED_GREEN = 0;
        } else {
            LED_RED = 0;
            LED_GREEN = 1;
        }
        
        __delay_ms(500);
    }
}

void display_locker_lcd(unsigned char locker_number) {
    lcd_clear();
    lcd_gotoxy(1, 1);
    lcd_puts("LOCKER:");
    lcd_gotoxy(1, 9);
    lcd_putc(locker_number + '0');
    lcd_gotoxy(2, 1);
    lcd_puts("STATUS:");
    lcd_gotoxy(2, 9);
    
    if (locker_status[locker_number] == LOCKED) {
        lcd_puts("LOCKED");
    } else {
        lcd_puts("UNLOCKED");
    }
    
    __delay_ms(2000);
    lcd_clear();
}

void buzzer_on() {
    BUZZER = 1;
}

void buzzer_off() {
    BUZZER = 0;
}


