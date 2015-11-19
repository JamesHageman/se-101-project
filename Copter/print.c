

//Function to print the game over screen
void printGameOver(long score)
{
  char *gameOver = "Game Over!";
  char scoreString[50];// = "Score: ";
  sprintf(scoreString, "Score: %d", score);
  OrbitOledClear();
  OrbitOledSetCursor(3, 0);
  OrbitOledPutString(gameOver);
  OrbitOledSetCursor(3, 2.5);
  OrbitOledPutString(scoreString);
}

//Function to print the start menu of the game

void printStart()
{
  char *startMenu = "Push Any Button To Start Game";
  OrbitOledClear();
  OrbitOledSetCursor(0, 0);
  OrbitOledPutString(startMenu);
}
