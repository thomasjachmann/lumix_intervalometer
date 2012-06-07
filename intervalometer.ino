/*
  Panasonic/Lumix Intervalometer
  Triggers shutter via remote control port (coupled via optocouplers).
 */

/***** BEGIN IO initialization *****/

const int inSwitch    = 12; // push button to change the running state with
const int outRunning  = 11; // LED to display the running state (on when running)
const int outAction   = 13; // LED to display the action state (on when triggering)
const int outFocus    = 10; // optocoupler to trigger focus
const int outShutter  = 9;  // optocoupler to trigger shutter
                            // pins 0-7 are used as input switches for timing

void setAsInput(int pin) {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH); // turn on Atmega's pullup resistor
}

void setup() {
  setAsInput(inSwitch);
  for (int i = 0; i < 8; i++) {
    setAsInput(i);
  }
  pinMode(outRunning, OUTPUT);
  pinMode(outAction, OUTPUT);
  pinMode(outFocus, OUTPUT);
  pinMode(outShutter, OUTPUT);
}

/***** END IO initialization *****/


/***** BEGIN loop *****/

unsigned long curTime = 0;
unsigned long nextActiveChangeTime = 0;
const int actionDuration = 500;

void loop() {
  curTime = millis();
  checkRunning();
  performAction();
}

/***** END loop *****/


/***** BEGIN switch to choose between running/sleeping *****/

boolean running = false;      // are we intervalometering?

int prevSwitch = HIGH;
int debounceSwitch = HIGH;
unsigned long prevSwitchDebounceTime = 0;
const int debounceInterval = 10;

void checkRunning() {
  int curSwitch = digitalRead(inSwitch);
  // debounce button
  if (curSwitch != debounceSwitch) {
    prevSwitchDebounceTime = curTime;
  }
  debounceSwitch = curSwitch;
  if (curTime - prevSwitchDebounceTime > debounceInterval) {
    // act upon fresh button presses
    if (prevSwitch == HIGH && curSwitch == LOW) {
      running = !running;
      digitalWrite(outRunning, running);
      if (running) {
        nextActiveChangeTime = curTime;
      }
    }
    prevSwitch = curSwitch;
  }
}

/***** END running switch *****/


/***** BEGIN action stuff *****/

unsigned long actionInterval() {
  unsigned long interval = 0;
  for (int i = 0; i < 8; i++) {
    if (digitalRead(i) == LOW) {
      interval += 1 << i;
    }
  }
  if (interval > 0) {
    interval = interval * 1000 - actionDuration;
  }
  return interval;
}
boolean active = false;       // are we executing the action?

void performAction() {
  if (curTime >= nextActiveChangeTime) {
    unsigned long curActionInterval = actionInterval();
    if ((running && curActionInterval > 0) || active) {
      active = !active;
      digitalWrite(outAction, active);
      digitalWrite(outShutter, active);
    }
    nextActiveChangeTime = curTime + (active ? actionDuration : curActionInterval);
  }
}

/***** END action stuff *****/
