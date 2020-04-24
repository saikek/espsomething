#ifdef false

#include <Arduino.h>

int BTN_LR = 34;
int BTN_UD = 35; 
int BTN_CLICK = 32; 

void setup()
{
  Serial.begin(115200);

  pinMode(BTN_LR, INPUT_PULLUP);
  pinMode(BTN_UD, INPUT_PULLUP);
  pinMode(BTN_CLICK, INPUT_PULLUP);
}

enum Direction{
  LEFT,
  RIGHT,
  UP,
  DOWN,
  CLICK
};

void handleDirectionChange(Direction direction){
  Serial.println((String)direction);
}

void loop()
{
  int value1 = analogRead(BTN_LR);
  int value2 = analogRead(BTN_UD);
  int value3 = analogRead(BTN_CLICK);

  if (value1 < 850){
    handleDirectionChange(LEFT);
  } else if(value1 > 3500){
    handleDirectionChange(RIGHT);
  }

  if (value2 < 850){
    handleDirectionChange(DOWN);
  } else if(value2 > 3500){
    handleDirectionChange(UP);
  }

  if (value3 < 200) {
    handleDirectionChange(CLICK);
  }

  Serial.print(value1);
  Serial.print("  ");
  Serial.print(value2);
  Serial.print("  ");
  Serial.print(value3);
  Serial.print("  ");
  Serial.println("");


  delay(100);
}


#endif