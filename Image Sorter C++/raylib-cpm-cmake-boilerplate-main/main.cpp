#include <raylib.h>
#include <raygui.h>
#include <cstdint>


int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 1200;


    const int imgWidth = 400;
    const int imgHeight = 400;

    // Load Texture From Image Has To Happen After InitWindow
    InitWindow(screenWidth, screenHeight, "Pixel Manipulation");

    Image test = LoadImage("Assets/Face1.png");
    Texture2D testTexture = LoadTextureFromImage(test);

    SetTargetFPS(60);

    Image img = GenImageColor(imgHeight, imgHeight, WHITE);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    auto pixels = (Color*)img.data;
    Texture tex = LoadTextureFromImage(img);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // your update logic goes here
        for(int row = 0; row < imgHeight; row++)
        {
            for(int col = 0; col < imgWidth; col++)
            {
                pixels[row * imgWidth + col] = (Color) {
                    (uint8_t)(GetRandomValue(0, 255)),
                    (uint8_t)(GetRandomValue(0, 255)),
                    (uint8_t)(GetRandomValue(0, 255)),
                    255
                };
            }
        }
        UpdateTexture(tex, pixels);

        // drawing logic goes here
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(testTexture, 0, 0, WHITE);
        EndDrawing();
    }

    UnloadTexture(testTexture);

    CloseWindow();
    return 0;
}