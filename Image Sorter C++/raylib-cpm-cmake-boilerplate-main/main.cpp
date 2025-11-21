#include <raylib.h>
#include <raygui.h>
#include <cstdint>
#include <math.h>


int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 1200;

    // Load Texture From Image Has To Happen After InitWindow
    InitWindow(screenWidth, screenHeight, "Pixel Manipulation");

    SetTargetFPS(60);

    Image imageFrom = LoadImage("Assets/Face1.png");
    auto pixelsFrom = (Color*)imageFrom.data;
    Image imageTo = LoadImage("Assets/Face2.png");
    auto pixelsTo = (Color*)imageTo.data;

    const int imgFromWidth = imageFrom.width, imgFromHeight = imageFrom.height;
    const int imgToWidth = imageTo.width, imgToHeight = imageTo.height;
    const int imgResultWidth = (imgFromWidth >= imgToWidth) ? imgFromWidth : imgToWidth;
    const int imgResultHeight = (imgFromHeight >= imgToHeight) ? imgFromHeight : imgToHeight;
    Image imageResult = GenImageColor(imgResultWidth, imgResultHeight, WHITE);
    auto pixelsResult = (Color*)imageResult.data;
    Texture2D resultTexture = LoadTextureFromImage(imageResult);

    int sortRange = 2;

    /*Image img = GenImageColor(imgHeight, imgHeight, WHITE);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    auto pixels = (Color*)img.data;
    Texture tex = LoadTextureFromImage(img);*/

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Go through every pixel
        for(int row = 0; row < imgFromHeight; row++) {
            for(int col = 0; col < imgFromWidth; col++) {

                Color closestPixel;
                float closestDistance = 1000.0f;
                auto currentPixelTo = pixelsTo[row * imgFromWidth + col];
                //Sort Range a 5by5 cube centered around the current pixel
                for (int sortRow = -sortRange; sortRow <= sortRange; sortRow++) {
                    for (int sortCol = -sortRange; sortCol <= sortRange; sortCol++) {

                        if ((row + sortRow >= 0 && row + sortRow < imgResultWidth) || (col + sortCol && col + sortCol < imgResultHeight)) {
                            auto currentPixelFrom = pixelsFrom[(row + sortRow) * imgFromWidth + (col + sortCol)];

                            float distance = abs(currentPixelTo.r - currentPixelFrom.r + currentPixelTo.g - currentPixelFrom.g + currentPixelTo.b - currentPixelFrom.b);

                            if (distance < closestDistance) {
                                closestPixel = currentPixelFrom;
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
        DrawTexture(resultTexture, 0, 0, WHITE);
        EndDrawing();
    }

    UnloadTexture(resultTexture);

    CloseWindow();
    return 0;
}