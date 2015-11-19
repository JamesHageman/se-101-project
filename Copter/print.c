

//Function to print the game over screen
void printGameOver(int score)
{
  char gameOver[] = {'G', 'a', 'm', 'e', ' ', 'O', 'v', 'e', 'r', '!', '\0'};
  char scoreString[] = {'S', 'c', 'o', 'r', 'e', ':', '\0'};
  int hold = score;
  char *digit = malloc(score * sizeof(int));
  OrbitOledClear();
  OrbitOledSetCursor(3, 0);
  OrbitOledPutString(gameOver);
  OrbitOledSetCursor(3, 2.5);
  OrbitOledPutString(scoreString);
  
  int x = 0;
  
  do{
    digit[x] = hold%10;
    hold /= 10;
    x++;
  } while(hold != 0);
  
  digit[x] = '\0';
  
  OrbitOledSetCursor(5, 2.5);
  OrbitOledPutString(digit);
}

//Function to print the start menu of the game

void printStart()
{
  char startMenu[] = {'P','u', 's', 'h', ' ', 'A', 'n', 'y', ' ', 'B', 'u', 't', 't', 'o', 'n', ' ', 'T', 'o', ' ', 'S', 't', 'a', 'r', 't', ' ', 'G', 'a', 'm', 'e', '\0'};
  OrbitOledClear();
  OrbitOledSetCursor(0, 0);
  OrbitOledPutString(startMenu);
}
