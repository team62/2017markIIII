#warning "LCDStartup"
void LCDStartup () {
	string lines[10];
	string splash;
	string last = "";
	for(int i = 0; i<9; i++) {
		clearLCD();
		sprintf(splash,"%d%s%d", 6,last,2);
		displayLCDCenteredString(0,last);
		displayLCDCenteredString(1,splash);
		last = splash;
		delay(100);
	}
	string traveler1 = "6";
	string traveler2 = "2";
	for(int i = 0; i<16; i++) {
		clearLCD();
		last = traveler1;
		displayLCDString(0,0,last);
		sprintf(traveler1," %s",last);
		delay(55);
	}
	for(int i = 0; i<16; i++) {
		clearLCD();
		last = traveler2;
		displayLCDString(1,0,last);
		sprintf(traveler2," %s",last);
		delay(55);
	}
	clearLCD();
	int kanagasabapathyDelay = 200;
	displayLCDCenteredString(0,"Kan");
	delay(kanagasabapathyDelay);
	clearLCD();
	displayLCDCenteredString(0,"a");
	delay(kanagasabapathyDelay);
	clearLCD();
	displayLCDCenteredString(0,"gas");
	delay(kanagasabapathyDelay);
	clearLCD();
	displayLCDCenteredString(0,"a");
	delay(kanagasabapathyDelay);
	clearLCD();
	displayLCDCenteredString(0,"bap");
	delay(kanagasabapathyDelay);
	clearLCD();
	displayLCDCenteredString(0,"a");
	delay(kanagasabapathyDelay);
	clearLCD();
	string traveler3 = "thy";
	displayLCDCenteredString(0,traveler3);
	for(int i = 0; i<13; i++) {
		last = traveler3;
		sprintf(traveler3, "%s%s",last,"y");
		clearLCD();
		displayLCDCenteredString(0,traveler3);
		delay(55);
	}
	clearLCD();

	string phrases[6][2];
	phrases[0][0] = "Someone get";
	phrases[0][1] = "Jon a Tea";

	phrases[1][0] = "When Cam";
	phrases[1][1] = "Sees Sam";

	phrases[2][0] = "That's some";
	phrases[2][1] = "8965 shit";

	phrases[3][0] = "there is no need";
	phrases[3][1] = "to be upset";

	phrases[4][0] = "If only robotics";
	phrases[4][1] = "was this hype";

	phrases[5][0] = "Griffin";
	phrases[5][1] = "Table";

	int startupPhrase = random(5);

	displayLCDCenteredString(0,phrases[startupPhrase][0]);
	displayLCDCenteredString(1,phrases[startupPhrase][1]);
	delay(2000);
}

enum { MAIN_SCREEN = 0, BATT_SCREEN = 1, AUTON_SCREEN = 2, TEST_SCREEN = 3 };
int currentScreen = MAIN_SCREEN;
#warning "LCD"
task LCD () {
	bLCDBacklight = true;
	wait1Msec(400);
	clearLCD();

	//Display battery voltage at start so we know what's up
	string mainBatteryStatus, backupBatteryStatus;
	sprintf(mainBatteryStatus,"Cortex: %1.2f%c V", nImmediateBatteryLevel/1000.0);
	sprintf(backupBatteryStatus,"Xpander: %1.2f%c V", SensorValue[powerExpander]/280.0);
	displayLCDString(0, 0, mainBatteryStatus);
	displayLCDString(1, 0, backupBatteryStatus);
	wait1Msec(2000);

	while(true) {
		clearLCD();
		if(autonomousChoice != -1)
			displayLCDCenteredString(0,"AUTON SELECTED");
		else
			displayLCDCenteredString(0,"62 STAR Mark III");
		displayLCDString(1,0,"Batts Auton");
		waitForPress();
		if(nLCDButtons == 1) {
			waitForRelease();
			clearLCD();
			sprintf(mainBatteryStatus,"Cortex: %1.2f%c V", nImmediateBatteryLevel/1000.0);
			sprintf(backupBatteryStatus,"Xpander: %1.2f%c V", SensorValue[powerExpander]/280.0);
			displayLCDString(0, 0, mainBatteryStatus);
			displayLCDString(1, 0, backupBatteryStatus);
			waitForPress();
			waitForRelease();
		} else if(nLCDButtons == 2) {
			waitForRelease();
			int choice = 0;
			while(nLCDButtons != 2) {
				centerLine(0,autonomousMenu[choice]);
				centerLine(1,"<-- SELECT -->");

				if(nLCDButtons == LCD_LEFT_BUTTON) {
					waitForRelease();
					choice = choice==0?numberAutons-1:choice-1;
				} else if(nLCDButtons == LCD_RIGHT_BUTTON) {
					waitForRelease();
					choice = choice==numberAutons-1?0:choice+1;
				}

				delay(25);
			}
			waitForRelease();
			autonomousChoice = choice;
			delay(50);
		}
	}
}
