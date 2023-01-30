#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "UTFT/UTFT.h"
#include "UTFT/color.h"
#include "UTFT/DefaultFonts.h"
#include "UTFT/ssd1289.h"

/*
* RGB colors
*/

#define BLUE 0, 0, 204
#define YELLOW 255, 255, 0
#define WHITE 255, 255, 255
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define MIDDLE_VERTICAL_LINE 150, 0, 150, 239
#define MIDDLE_HORIZONTAL_LINE 0, 120, 319, 120



/*
* Global variables
*/
UTFT display; //Display class

//lcd display is 320x240

//create function that will draw horizontal line and vertical line that will be used to split the screen in 4 quadrants
void drawLine()
{
	display.setFont(BigFont);
	display.setColor(WHITE);
	display.drawLine(MIDDLE_VERTICAL_LINE);
	display.drawLine(MIDDLE_HORIZONTAL_LINE);
	
	
	//make each rectangle different color
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
}

//create Simon class that has a rect value
class Simon
{
	int rect;

	public:

	Simon(){
		this->rect = rand() % 4 + 1;
	}

	Simon(int rect)
	{
		this->rect = rect;
	}

	void flashRect(){
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

Simon simonArray[30];
int turnCPU = 1;
int turnPlayer = 0;
int numberOfSimons = 1;
int correctAnswer[30];
int error = 0;
int countAnswer = 0;
int totalCorrectAnswers = 1;

int main(void)
{
	
	//SET PORTS
	PORTB = 0xff;
	DDRB = 0x00;
	
	//LCD INIT
	display.clrScr();
	display.InitLCD(LANDSCAPE);

	
	//fill simonArray with random numbers from 1-4
	for(int i = 0; i < 30; i++){
		int randomValue = rand() % 4 + 1;
		simonArray[i] = Simon(randomValue);
		correctAnswer[i] = randomValue;
	}

	while (1)
	{
		if(error == 1){
			display.clrScr();
			display.setColor(RED);
			display.setFont(BigFont);
			display.print("GAME OVER", CENTER, 110);
			while(1);
		}
		else{
			if(numberOfSimons == 31){
				display.clrScr();
				display.setColor(WHITE);
				display.setFont(BigFont);
				display.print("YOU WIN", CENTER, 110);
				while(1);
			}
			if(turnCPU == 1){
				for (int i = 0; i < numberOfSimons; i++)
				{
					simonArray[i].flashRect();
				}
				turnPlayer = 1;
				turnCPU = 0;
			}
			drawLine();
			if((PINB & (1 << PB0)) == 0){
				int x = 1;
				if(correctAnswer[countAnswer] == x){
					countAnswer++;
					display.setColor(WHITE);
					display.print("CORRECT", CENTER, 110);
					}else{
					error = 1;
				}
				_delay_ms(500);
			}
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
				_delay_ms(500);
			}
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
				_delay_ms(500);
			}
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
				_delay_ms(500);
			}
			if(countAnswer == numberOfSimons){
				turnPlayer = 0;
				turnCPU = 1;
				numberOfSimons++;
				countAnswer = 0;
			}
		}
	}
}