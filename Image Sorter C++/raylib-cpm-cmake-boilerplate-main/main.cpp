#include <raylib.h>
#include <raygui.h>
#include <cstdint>
#include <iostream>
#include <math.h>


int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 1200;

    // Load Texture From Image Has To Happen After InitWindow
    InitWindow(screenWidth, screenHeight, "Pixel Manipulation");

    SetTargetFPS(60);

    Image imageFrom = LoadImage("Assets/photos-icon.png");
    auto pixelsFrom = (Color*)imageFrom.data;
    Image imageTo = LoadImage("Assets/red_to_green.png");
    auto pixelsTo = (Color*)imageTo.data;

    const int imgFromWidth = imageFrom.width, imgFromHeight = imageFrom.height;
    const int imgToWidth = imageTo.width, imgToHeight = imageTo.height;
    const int imgResultWidth = (imgFromWidth >= imgToWidth) ? imgFromWidth : imgToWidth;
    const int imgResultHeight = (imgFromHeight >= imgToHeight) ? imgFromHeight : imgToHeight;
    Image imageResult = GenImageColor(imgResultWidth, imgResultHeight, WHITE);
    auto pixelsResult = (Color*)imageResult.data;
    Texture2D resultTexture = LoadTextureFromImage(imageResult);

    int sortRange = 4;

    /*Image img = GenImageColor(imgHeight, imgHeight, WHITE);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    auto pixels = (Color*)img.data;
    Texture tex = LoadTextureFromImage(img);*/

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Go through every pixel
        for(int row = 0; row < imgResultHeight; row++) {
            for(int col = 0; col < imgResultWidth; col++) {

                Color closestPixel = pixelsFrom[row * imgResultWidth + col];
                int closestDistance = 10000000;
                auto currentPixelFrom = pixelsFrom[row * imgFromWidth + col];

                //Sort Range a 5by5 cube centered around the current pixel
                for (int sortRow = -sortRange; sortRow <= sortRange; sortRow++) {
                    for (int sortCol = -sortRange; sortCol <= sortRange; sortCol++) {

                        if ((row + sortRow >= 0 && row + sortRow < imgResultWidth) || (col + sortCol && col + sortCol < imgResultHeight)) {
                            auto currentPixelTo = pixelsTo[(row + sortRow) * imgFromWidth + (col + sortCol)];

                            int distance = abs(currentPixelFrom.r - currentPixelTo.r + currentPixelFrom.g - currentPixelTo.g + currentPixelFrom.b - currentPixelTo.b);

                            if (distance < closestDistance) {
                                closestDistance = distance;
                                closestPixel = currentPixelTo;
                            }

                        }

                    }
                }

                pixelsResult[row * imgFromWidth + col] = closestPixel;

            }
        }

        UpdateTexture(resultTexture, pixelsResult);
        

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

int TTO(int x, int y) {
    return (x*y + y);
}