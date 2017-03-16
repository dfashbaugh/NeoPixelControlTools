int snake(long frame, int i) {
  return i; 
}

int forward(long frame, int i) {
  return i;
}

int backward(long frame, int i) {
  return totalLEDs - 1 - i;
}

#define SIDE_LENGTH 72
int horizontal(long frame, int i)
{
  int returnValue = i / (SIDE_LENGTH + 1);

  return returnValue;
}

int vertical(long frame, int i)
{
  int returnValue = i % (SIDE_LENGTH+1);

  if( (i / (SIDE_LENGTH + 1)) % 2)
  {
    returnValue = (SIDE_LENGTH + 1) - returnValue;
  }

  return returnValue;
}


int intoSpace(long frame, int i)
{
  int returnValue = i / NUM_LEDS_PER_STRIP;

  // Case for strips 7-8
  if(returnValue == 7 || returnValue == 9)
  {
    if(i > (NUM_LEDS_PER_STRIP*returnValue) + (NUM_LEDS_PER_STRIP/2) )
      returnValue++;
  }

  // Case for strips 1-6
  return returnValue;
}

int longSnake(long frame, int i)
{
  return i/2;
}

int shortSnake(long frame, int i)
{
  return i*2;
}

int dekonstruktor(long frame, int i)
{
  if(frame%400 > 200)
  {
    return i + random(frame%200/4);
  }
  else
  {
    return i + random( (200-(frame%200) )/4);
  } 
}

int dekonstruktorIntoSpace(long frame, int i)
{
  return dekonstruktor(frame, intoSpace(frame, i));
}

int dekonstrucktorVertical(long frame, int i)
{
  return dekonstruktor(frame, vertical(frame, i));
}

int dekonstruktorHorizontal(long frame, int i)
{
  return dekonstruktor(frame, horizontal(frame, i));
}
