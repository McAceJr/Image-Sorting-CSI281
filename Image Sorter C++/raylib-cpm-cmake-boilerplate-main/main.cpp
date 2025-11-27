#include <raylib.h>
#include <raygui.h>
#include <cstdint>
#include <iostream>
#include <math.h>
#include <unordered_map>
#include <vector>


int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 1200;

    bool repeats = false;

    // Load Texture From Image Has To Happen After InitWindow
    InitWindow(screenWidth, screenHeight, "Pixel Sort");

    SetTargetFPS(60);

    Image imageFrom = LoadImage("Assets/TestChecker2.png");
    auto pixelsFrom = (Color*)imageFrom.data;
    Image imageTo = LoadImage("Assets/Test4Lines1.png");
    auto pixelsTo = (Color*)imageTo.data;

    const int imgFromWidth = imageFrom.width, imgFromHeight = imageFrom.height;
    const int imgToWidth = imageTo.width, imgToHeight = imageTo.height;
    const int imgResultWidth = (imgFromWidth >= imgToWidth) ? imgFromWidth : imgToWidth;
    const int imgResultHeight = (imgFromHeight >= imgToHeight) ? imgFromHeight : imgToHeight;
    Image imageResult = GenImageColor(imgResultWidth, imgResultHeight, WHITE);
    auto pixelsResult = (Color*)imageResult.data;
    Texture2D resultTexture = LoadTextureFromImage(imageResult);

    std::unordered_map<int, int> usedPositions;

    /*Image img = GenImageColor(imgHeight, imgHeight, WHITE);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    auto pixels = (Color*)img.data;
    Texture tex = LoadTextureFromImage(img);*/

    //Go through every pixel
    for(int row = 0; row < imgResultHeight; row++) {
        for(int col = 0; col < imgResultWidth; col++) {

            int closestDistance = 10000000;
            auto currentPixelFrom = pixelsFrom[row * imgFromWidth + col];
            int position;

            for(int row2 = 0; row2 < imgResultHeight; row2++) {
                for(int col2 = 0; col2 < imgResultWidth; col2++) {

                    int pos = row2 * imgFromWidth + col2;

                    if (usedPositions[pos] >= 1 && !repeats) {

                    }
                    else {
                        auto currentPixelTo = pixelsTo[pos];

                        int distance = abs(currentPixelFrom.r - currentPixelTo.r + currentPixelFrom.g - currentPixelTo.g + currentPixelFrom.b - currentPixelTo.b + currentPixelFrom.a - currentPixelTo.a);

                        if (distance < closestDistance) {
                            closestDistance = distance;
                            position = pos;
                        }
                    }

                }
            }

            usedPositions[position]++;

            pixelsResult[position] = currentPixelFrom;

        }
    }

    UpdateTexture(resultTexture, pixelsResult);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        

        // drawing logic goes here
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextureEx(resultTexture, Vector2(0, 0), 0, 4.0f, WHITE);
        EndDrawing();
    }

    UnloadTexture(resultTexture);

    CloseWindow();
    return 0;
}
