# Advanced-Diploma-Mega-Project-1
This Repo includes SWCs for Mega project 1, the project interface between NucleoF446RE board and Blue Pill board

# Main function:
 Create System with Lock and display some options for user Like read time, Edit time, Add alarm and exit.
the user choose the option using Terminal,we have NucleoF446RE board read from Terminal using USART protocol and interface RTC module with Nucleo using I2C Protocol then display option on LCD using Blue Pill, Note we send Data from Nucleo to Blue Pill over SPI protocol.

# System consists of:
1. Terminal using Putty
2. NucleoF446RE board 
3. RTC Module DS1307
4. Button
5. Blue Pill 
6. LCD 
7. LED and Buzzer 

# SWCs:

	#MCAL
		1. RCC (Nucleo and Blue Pill)
		2. GPIO (Nucleo and Blue Pill)
		3. SYSTICK (Nucleo and Blue Pill)
		4. NVIC  (Nucleo)
		5. EXTI (Blue Pill)
		6. SPI (Nucleo and Blue Pill)
		7. I2C (Nucleo)
		8. USART (Nucleo)
	# HAL 
		1. LED 
		2. Button 
		3. Buzzer
		4. RTC DS1307
		5. LCD
	# Lib
		1. STD_types 
		2. BIT_Math 
	# APP
		1. App 


# Details:

1. to start user need to press User button on Nucleo board. then, it will ask him for ID and Password you have 4 times to try then system will lock for 1 m then need to press User button again.
2. the user use Terminal to interface with Nucleo, it will display some options for him(Read Time, Set Time, Set Alarm and Exit).
3. if user choose Read time option it will Display Time on LCD. Nucleo will receive Data from RTC through I2C then save it and transmit this data to Blue Pill through SPI to be displayed on LCD.
4. if User choose Set time option it will ask hime to enter new Time and Date then Nucleo will transmit it to RTC through I2C.
5. if user choose Set Alarm option it will ask him to enter some Info like Alarm number it must be valid from 1 to 5 and then it will ask him for the name after that the user will enter the Time and Date, and we have a periodic Task every 1 m check the Time from RTC to Fire alarm or no, if this time to fire Alarm we send signal to Blue Pill on EXTI Pin then receive Alarm information and display it on LCD.
6. if user choose Exit option it will lock the system and need from him to press the User button again to read ID and Password again.      		


