#include <raylib.h>
#include <raygui.h>
#include <cstdint>
#include <iostream>
#include <map>
#include <math.h>
#include <unordered_map>
#include <vector>

void JaceSort(int IRH, int IRW, Color* pixFrom, Color* pixTo, Color* &pixRes, bool repeat);

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 1200;

    bool repeats = false;

    // Load Texture From Image Has To Happen After InitWindow
    InitWindow(screenWidth, screenHeight, "Pixel Sort");

    SetTargetFPS(60);

    Image imageFrom = LoadImage("Assets/Test4Lines1.png");
    auto pixelsFrom = (Color*)imageFrom.data;
    Image imageTo = LoadImage("Assets/blacktowhite.png");
    auto pixelsTo = (Color*)imageTo.data;

    const int imgFromWidth = imageFrom.width, imgFromHeight = imageFrom.height;
    const int imgToWidth = imageTo.width, imgToHeight = imageTo.height;
    const int imgResultWidth = (imgFromWidth >= imgToWidth) ? imgFromWidth : imgToWidth;
    const int imgResultHeight = (imgFromHeight >= imgToHeight) ? imgFromHeight : imgToHeight;
    Image imageResult = GenImageColor(imgResultWidth, imgResultHeight, WHITE);
    auto pixelsResult = (Color*)imageResult.data;
    auto pixelsResult2 = (Color*)imageResult.data;
    Texture2D resultTexture = LoadTextureFromImage(imageResult);
    Texture2D fromTexture = LoadTextureFromImage(imageFrom);
    Texture2D toTexture = LoadTextureFromImage(imageTo);

    JaceSort(imgResultWidth, imgResultHeight, pixelsFrom, pixelsTo, pixelsResult, repeats);
    UpdateTexture(resultTexture, pixelsResult2);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // drawing logic goes here
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextureEx(fromTexture, Vector2(0, 0), 0, 4.0f, WHITE);
        DrawTextureEx(resultTexture, Vector2(0 + imgFromWidth * 4, 0), 0, 4.0f, WHITE);
        DrawTextureEx(toTexture, Vector2(0, 0 + imgFromHeight * 4), 0, 4.0f, WHITE);
        EndDrawing();
    }

    UnloadTexture(fromTexture);
    UnloadTexture(resultTexture);
    UnloadTexture(toTexture);

    CloseWindow();
    return 0;
}

void JaceSort(int IRH, int IRW, Color* pixFrom, Color* pixTo, Color* &pixRes, bool repeat) {

    std::unordered_map<int, int> usedPositions;

    for(int col = 0; col < IRH; col++) {
        for(int row = 0; row < IRW; row++) {

            float closestDistance = 10000000;
            auto currentPixelFrom = pixFrom[col * IRW + row];
            int position;


            for(int col2 = 0; col2 < IRH; col2++) {
                for(int row2 = 0; row2 < IRW; row2++) {

                    int pos = col2 * IRW + row2;

                    if (usedPositions[pos] >= 1 && !repeat) {

                    }
                    else {
                        auto tr = pixTo[pos].r;
                        auto tg = pixTo[pos].g;
                        auto tb = pixTo[pos].b;
                        auto fr = currentPixelFrom.r;
                        auto fg = currentPixelFrom.g;
                        auto fb = currentPixelFrom.b;

                        /*int distance = abs(sqrt(0.299*(fr*fr)+0.587*(fg*fg)+0.114*(fb*fb))
                            - sqrt(0.299*(tr*tr)+0.587*(tg*tg)+0.114*(tb*tb)));*/

                        float distance = abs((0.299f*fr+0.587f*fg+0.114f*fb)/3.0f - (0.299f*tr+0.587f*tg+0.114f*tb)/3.0f);

                        if (distance < closestDistance) {
                            closestDistance = distance;
                            position = pos;
                        }
                    }

                }
            }

            usedPositions[position]++;

            pixRes[position] = currentPixelFrom;

        }
    }

}