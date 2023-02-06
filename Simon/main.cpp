#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "UTFT/UTFT.h"
#include "UTFT/color.h"
#include "UTFT/DefaultFonts.h"
#include "UTFT/ssd1289.h"



/*
* LCD resolution is 320x240
*/


//RGB colors
#define BLUE 0, 0, 204
#define YELLOW 255, 255, 0
#define WHITE 255, 255, 255
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define MIDDLE_VERTICAL_LINE 150, 0, 150, 239
#define MIDDLE_HORIZONTAL_LINE 0, 120, 319, 120



/*
* UTFT is a library that allows user to display images and text on various TFT (Thin-Film Transistor) displays
* UTFT display object will be used to draw components of the game on TFT LCD
*/

UTFT display; //Display class


/**
* The drawLine function is used to draw lines and rectangles on the display screen.
* The function sets the font to BigFont and color to white for the two vertical and horizontal lines in the middle of the screen.
* The function then uses fillRect to fill four different rectangles with colors red, green, blue and yellow.
* Each rectangle is accompanied with text indicating the key associated with it.
*/

void drawLine()
{
	display.setFont(BigFont);
	display.setColor(WHITE);
	display.drawLine(MIDDLE_VERTICAL_LINE);
	display.drawLine(MIDDLE_HORIZONTAL_LINE);
	
	
	// Red rectangle
	display.setColor(RED);
	display.fillRect(0, 0, 150, 120);
	display.setColor(WHITE);
	display.print("Key1", 50, 60);
	
	// Green rectangle
	display.setColor(GREEN);
	display.fillRect(0, 120, 150, 239);
	display.setColor(WHITE);
	display.print("Key3", 50, 180);
	
	// Blue rectangle
	display.setColor(BLUE);
	display.fillRect(150, 0, 319, 120);
	display.setColor(WHITE);
	display.print("Key2", 200, 60);
	
	// Yellow rectangle
	display.setColor(YELLOW);
	display.fillRect(150, 120, 319, 239);
	display.setColor(WHITE);
	display.print("Key4", 200, 180);
}

/**
 * The Simon class is used to create color elements in a game. 
 * The class has property rect that indicates which rectangle will be used for memory sequence 
 */
class Simon
{
	/** A flag used to indicate which rectangle will blink*/
	int rect;

	public:

	/**
	 * Default constructor for the Simon class.
	 * Generates random number form [1,4] interval and saves that value in rect parameter
	 */
	Simon(){
		this->rect = rand() % 4 + 1;
	}

	/**
	 * Constructor for the Simon class that takes rect integer.
	 * This constructor can be used to manually setup value of rect parameter
	 */
	Simon(int rect)
	{
		this->rect = rect;
	}

	/**
	 * This function is used to draw all rectangles on screen and blink one rectangle define by rect value
	 */
	void flashRect(){
		
		// Blink red rectangle
		if(rect == 1){
			display.setFont(BigFont);
			display.setColor(WHITE);
			display.drawLine(MIDDLE_VERTICAL_LINE);
			display.drawLine(MIDDLE_HORIZONTAL_LINE);
			
			display.setColor(GREEN);
			display.fillRect(0, 120, 150, 239);
			display.setColor(WHITE);
			display.print("Key3", 50, 180);
			
			
			display.setColor(BLUE);
			display.fillRect(150, 0, 319, 120);
			display.setColor(WHITE);
			display.print("Key2", 200, 60);
			
			
			display.setColor(YELLOW);
			display.fillRect(150, 120, 319, 239);
			display.setColor(WHITE);
			display.print("Key4", 200, 180);
			
			display.setColor(RED);
			display.fillRect(0, 0, 150, 120);
			display.setColor(WHITE);
			display.print("Key1", 50, 60);
			_delay_ms(500);
			display.setColor(RED);
			display.fillRect(0, 0, 150, 120);
			_delay_ms(500);
		}
		
		// Blink green rectangle
		if(rect == 3){
			display.setFont(BigFont);
			display.setColor(WHITE);
			display.drawLine(MIDDLE_VERTICAL_LINE);
			display.drawLine(MIDDLE_HORIZONTAL_LINE);
			
			display.setColor(BLUE);
			display.fillRect(150, 0, 319, 120);
			display.setColor(WHITE);
			display.print("Key2", 200, 60);
			
			
			display.setColor(YELLOW);
			display.fillRect(150, 120, 319, 239);
			display.setColor(WHITE);
			display.print("Key4", 200, 180);
			
			display.setColor(RED);
			display.fillRect(0, 0, 150, 120);
			display.setColor(WHITE);
			display.print("Key1", 50, 60);
			
			
			display.setColor(GREEN);
			display.fillRect(0, 120, 150, 239);
			display.setColor(WHITE);
			display.print("Key3", 50, 180);
			_delay_ms(500);
			display.setColor(GREEN);
			display.fillRect(0, 120, 150, 239);
			_delay_ms(500);
		}
		
		// Blink blue rectangle
		if(rect == 2){
			display.setFont(BigFont);
			display.setColor(WHITE);
			display.drawLine(MIDDLE_VERTICAL_LINE);
			display.drawLine(MIDDLE_HORIZONTAL_LINE);
			
			display.setColor(YELLOW);
			display.fillRect(150, 120, 319, 239);
			display.setColor(WHITE);
			display.print("Key4", 200, 180);
			
			display.setColor(RED);
			display.fillRect(0, 0, 150, 120);
			display.setColor(WHITE);
			display.print("Key1", 50, 60);
			
			
			display.setColor(GREEN);
			display.fillRect(0, 120, 150, 239);
			display.setColor(WHITE);
			display.print("Key3", 50, 180);
			
			
			display.setColor(BLUE);
			display.fillRect(150, 0, 319, 120);
			display.setColor(WHITE);
			display.print("Key2", 200, 60);
			_delay_ms(500);
			display.setColor(BLUE);
			display.fillRect(150, 0, 319, 120);
			_delay_ms(500);
		}
		
		// Blink yellow rectangle
		if(rect == 4){
			display.setFont(BigFont);
			display.setColor(WHITE);
			display.drawLine(MIDDLE_VERTICAL_LINE);
			display.drawLine(MIDDLE_HORIZONTAL_LINE);
			
			display.setColor(RED);
			display.fillRect(0, 0, 150, 120);
			display.setColor(WHITE);
			display.print("Key1", 50, 60);
			
			
			display.setColor(GREEN);
			display.fillRect(0, 120, 150, 239);
			display.setColor(WHITE);
			display.print("Key3", 50, 180);
			
			
			display.setColor(BLUE);
			display.fillRect(150, 0, 319, 120);
			display.setColor(WHITE);
			display.print("Key2", 200, 60);
			
			display.setColor(YELLOW);
			display.fillRect(150, 120, 319, 239);
			display.setColor(WHITE);
			display.print("Key4", 200, 180);
			_delay_ms(500);
			display.setColor(YELLOW);
			display.fillRect(150, 120, 319, 239);
			_delay_ms(500);
		}
	}
};


/**
 * An array of 30 Simon objects.
 */
Simon simonArray[30];

/**
 * A flag that indicates CPUs turn
 */
int turnCPU = 1;

/**
 * A flag that indicates players turn
 */
int turnPlayer = 0;

/**
 * A counter for the length of current color sequence.
 */
int numberOfSimons = 1;

/**
 * An array used to store correct answers of color sequences.
 */
int correctAnswer[30];

/**
 * A flag that indicates player has answered incorrectly
 */
int error = 0;

/**
 * A counter for the number of current players correct answers.
 */
int countAnswer = 0;

/**
 * A counter for the number of correct answers in current color sequence.
 */
int totalCorrectAnswers = 1;

int main(void)
{
	
	// Button ports
	PORTB = 0xff;
	DDRB = 0x00;
	
	// LCD init
	display.clrScr();
	display.InitLCD(LANDSCAPE);

	
	// Fill simonArray with random numbers from 1-4
	for(int i = 0; i < 30; i++){
		int randomValue = rand() % 4 + 1;
		simonArray[i] = Simon(randomValue);
		correctAnswer[i] = randomValue;
	}

	// The while loop is the main game loop that updates and renders the game elements
	while (1)
	{
		// if player has answered incorrectly show Game over screen
		if(error == 1){
			display.clrScr();
			display.setColor(RED);
			display.setFont(BigFont);
			display.print("GAME OVER", CENTER, 110);
			while(1);
		}
		
		// If player has answered correctly go to the next iteration
		else{
			
			// If player has answered whole color sequence correctly show You win screen 
			if(numberOfSimons == 31){
				display.clrScr();
				display.setColor(WHITE);
				display.setFont(BigFont);
				display.print("YOU WIN", CENTER, 110);
				while(1);
			}
			
			// CPUs turn to blink next color sequence
			if(turnCPU == 1){
				for (int i = 0; i < numberOfSimons; i++)
				{
					simonArray[i].flashRect();
				}
				turnPlayer = 1;
				turnCPU = 0;
			}
			
			// Draw default screen while you wait for players input
			drawLine();
			
			// Check if pressed key1 is correct answer in the color sequence
			if((PINB & (1 << PB0)) == 0){
				int x = 1;
				if(correctAnswer[countAnswer] == x){
					countAnswer++;
					display.setColor(WHITE);
					display.print("CORRECT", CENTER, 110);
					}else{
					error = 1;
				}
				
				// Switch debounce
				_delay_ms(500);
			}
			
			// Check if pressed key2 is correct answer in the color sequence
			if((PINB & (1 << PB1)) == 0){
				int x = 2;
				if(correctAnswer[countAnswer] == x){
					countAnswer++;
					display.setColor(WHITE);
					display.print("CORRECT", CENTER, 110);
				}
				else{
					error = 1;
				}
				
				// Switch debounce
				_delay_ms(500);
			}
			
			// Check if pressed key3 is correct answer in the color sequence
			if((PINB & (1 << PB2)) == 0){
				int x = 3;
				if(correctAnswer[countAnswer] == x){
					countAnswer++;
					display.setColor(WHITE);
					display.print("CORRECT", CENTER, 110);
				}
				else{
					error = 1;
				}
				
				// Switch debounce
				_delay_ms(500);
			}
			
			// Check if pressed key4 is correct answer in the color sequence
			if((PINB & (1 << PB3)) == 0){
				int x = 4;
				if(correctAnswer[countAnswer] == x){
					countAnswer++;
					display.setColor(WHITE);
					display.print("CORRECT", CENTER, 110);
				}
				else{
					error = 1;
				}
				
				// Switch debounce
				_delay_ms(500);
			}
			
			// Check if player has memorized whole color sequence
			if(countAnswer == numberOfSimons){
				
				// Set CPUs turn flag to show next color sequence
				turnPlayer = 0;
				turnCPU = 1;
				
				// Increment length of next color sequence
				numberOfSimons++;
				countAnswer = 0;
			}
		}
	}
}