const int MOTOR_PIN = 0;
const int RANDOM_SEED_PIN = 1;
const int SWITCH_CHAOS_PIN = 3;
const int SWITCH_NORMAL_PIN = 4;

const int MODE_OFF = 0;
const int MODE_NORMAL = 1;
const int MODE_CHAOS = 2;

int speeds[] = {63, 127, 191, 255};

int motorSpeed;
int mode;
unsigned long lastSwitchMillis;
unsigned long millisUntilNextSwitch;

void setup() {
	pinMode(MOTOR_PIN, OUTPUT);
	pinMode(SWITCH_NORMAL_PIN, INPUT);
	pinMode(SWITCH_CHAOS_PIN, INPUT);
	
	mode = MODE_NORMAL;
	motorSpeed = 0;
	randomSeed(analogRead(RANDOM_SEED_PIN));	
}

void loop() {
	updateMode();
	actByMode();
	analogWrite(MOTOR_PIN, motorSpeed);
}

void updateMode() {
	if (digitalRead(SWITCH_NORMAL_PIN) == HIGH) {
		mode = MODE_NORMAL;
	}
	else if (digitalRead(SWITCH_CHAOS_PIN) == HIGH) {
		mode = MODE_CHAOS;
	}
	else {
		mode = MODE_OFF;
	}
}

void actByMode() {
	switch (mode) {
	    case MODE_OFF:
	    	motorSpeed = 0;
	      break;	    
	    case MODE_NORMAL:
	    	motorSpeed = 255;
	      break;
	    case MODE_CHAOS:
	      selectSpeed();
	    	break;
	    default: {}
	      // do something
	}
}

void selectSpeed() {
	if ((millis() - lastSwitchMillis) > millisUntilNextSwitch) {
		long roll = random(8);
		if (roll == 0) {
			motorSpeed = 0;
			millisUntilNextSwitch = 2000 + random(2) * 1000;
		}
		else if (roll < 3) {
			motorSpeed = 80;
			millisUntilNextSwitch = 2000 + random(3) * 1000;
		}
		else if (roll < 5) {
			motorSpeed = 150;
			millisUntilNextSwitch = 2000 + random(2) * 1000;
		}		
		else {
			motorSpeed = 255;
			millisUntilNextSwitch = 3000 + random(3) * 1000;
		}
		lastSwitchMillis = millis();		
	}
}
