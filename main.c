#include <math.h>
#include <raylib.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //---------------------------------------------------------
  const int screenWidth = 1024;
  const int screenHeight = 728;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Pendulum simulation");

  const Vector2 pivotPosition = {screenWidth / 2.0, screenHeight / 64.0};

  Vector2 bobPosition;
  int bobRadius = 20;
  float l = 8;
  float l_px = l * screenHeight / 10;

  bool pause = 0;
  int framesCounter = 0;
  float time = 0.0;
  // const float period = 2 * M_PI * sqrt(l / 9.81);
  // const float w = (2 * M_PI) / period;
  const float max_angle = (M_PI / 6);
  float angle;

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //----------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //-----------------------------------------------------
    if (IsKeyPressed(KEY_SPACE))
      pause = !pause;

    if (!pause) {
      angle = max_angle * cos(sqrt(9.81 / l) * time);
      bobPosition.x = (l_px * sin(angle)) + pivotPosition.x;
      bobPosition.y = (l_px * cos(angle)) + pivotPosition.y;
      time += GetFrameTime();
    } else {
      framesCounter++;
    }

    //-----------------------------------------------------
    // Draw
    //-----------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawLineV(pivotPosition, bobPosition, BLACK);
    DrawCircleV(pivotPosition, screenHeight / 128.0, BLUE);
    // DrawCircleV(pivotPosition, 1, BLACK);
    DrawCircleV(bobPosition, (float)bobRadius, RED);
    DrawCircleV(bobPosition, 2, BLACK);
    DrawText("PRESS SPACE to PAUSE BALL MOVEMENT", 10, GetScreenHeight() - 25,
             20, LIGHTGRAY);

    // On pause, we draw a blinking message
    if (pause && ((framesCounter / 30) % 2))
      DrawText("PAUSED",
               screenWidth / 2.0 -
                   MeasureText("PAUSED", screenHeight / 8) / 2.0,
               screenHeight / 2.0 - screenHeight / 8.0, screenHeight / 8, GRAY);

    DrawFPS(10, 10);

    EndDrawing();
    //-----------------------------------------------------
  }

  // De-Initialization
  //---------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //----------------------------------------------------------

  return 0;
}
