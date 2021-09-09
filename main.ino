#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int up = 11;
int down = 10;
int start = 9;
int timeMin = 0;
int timeSec = 0;

void setup()
{
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(start, INPUT);
  lcd.begin(16, 2);
  printToLCD(3);
}

void loop()
{
  if (digitalRead(start))
  {
    startTimer();
  }
  increaseTime(500);
  decreaseTime(500);
  delay(10);
}

void increaseTime(int waitTime)
{
  if (!digitalRead(up))
  {
    return;
  }

  if (timeSec < 50)
  {
    timeSec += 10;
  }
  else
  {
    timeSec = 0;
    timeMin += 1;
  }

  delay(waitTime);

  if (waitTime > 50)
  {
    waitTime -= 50;
  }
  printToLCD(1);
  increaseTime(waitTime);
}

void decreaseTime(int waitTime)
{
  if (!digitalRead(down))
  {
    return;
  }

  if (timeSec > 0)
  {
    timeSec -= 10;
  }
  else if (timeMin > 0)
  {
    timeSec = 50;
    timeMin -= 1;
  }

  delay(waitTime);

  if (waitTime > 50)
  {
    waitTime -= 50;
  }
  printToLCD(1);
  decreaseTime(waitTime);
}

void startTimer()
{
  printToLCD(2);
  delay(1000);
  if (timeSec > 0)
  {
    timeSec -= 1;
  }
  else if (timeMin > 0)
  {
    timeSec = 59;
    timeMin -= 1;
  }
  else
  {
    timerSound(8, 5);
    return;
  }
  startTimer();
}

void timerSound(int pin, int duration)
{
  while (duration > 0)
  {
    printToLCD(2);
    tone(pin, 330, 250);
    delay(300);
    lcd.clear();
    tone(pin, 311, 250);
    delay(300);
    --duration;
  }
  printToLCD(1);
}

void printToLCD(int state)
{
  lcd.clear();
  if (state == 3)
  {
    lcd.setCursor(3, 0);
    lcd.print("Welcome to");
    lcd.setCursor(6, 2);
    lcd.print("Timer");
  }
  else
  {
    if (state == 1)
    {
      lcd.setCursor(3, 0);
      lcd.print("Duration:");
    }
    else
    {
      lcd.setCursor(3, 0);
      lcd.print("Time Left:");
    }
    lcd.setCursor(5, 2);
    if (timeMin < 10)
    {
      lcd.print(0);
      lcd.print(timeMin);
    }
    else
    {
      lcd.print(timeMin);
    }
    lcd.print(":");
    if (timeSec < 10)
    {
      lcd.print(0);
      lcd.print(timeSec);
    }
    else
    {
      lcd.print(timeSec);
    }
  }
}