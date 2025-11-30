#include <raylib.h>
#include <raygui.h>
#include <cstdint>
#include <iostream>
#include <math.h>
#include <unordered_map>
#include <vector>

// Function Definitions
bool SimilarColors(const Color& refenceColor, const Color& checkingColor, int variance)
{
    if (abs((int)refenceColor.r - (int)checkingColor.r) > variance)
        return false;
    if (abs((int)refenceColor.g - (int)checkingColor.g) > variance)
        return false;
    if (abs((int)refenceColor.b - (int)checkingColor.b) > variance)
        return false;

    return true;
}

void SortColorIntArrays(std::vector<Color>& colorVector, std::vector<int>& repeatVector)
{
    for (int i = 0; i < (repeatVector.size()); i++)
    {
        int currentRepeatValue = repeatVector[i];
        Color currentColorValue = colorVector[i];
        int checkIndex = i - 1;

        while (checkIndex >= 0 && repeatVector[checkIndex] > currentRepeatValue)
        {
            repeatVector[checkIndex + 1] = repeatVector[checkIndex];
            colorVector[checkIndex + 1] = colorVector[checkIndex];
            checkIndex--;
        }
        repeatVector[checkIndex + 1] = currentRepeatValue;
        colorVector[checkIndex + 1] = currentColorValue;
    }
}


int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 1200;

    // Load Texture From Image Has To Happen After InitWindow
    InitWindow(screenWidth, screenHeight, "Pixel Sort");

    SetTargetFPS(60);

    Image imageFrom = LoadImage("Assets/red_to_green.png");
    auto pixelsFrom = (Color*)imageFrom.data;

    const int imgFromWidth = imageFrom.width, imgFromHeight = imageFrom.height;
    Image imageResult = GenImageColor(imgFromWidth, imgFromHeight, WHITE);
    auto pixelsResult = (Color*)imageResult.data;
    Texture2D resultTexture = LoadTextureFromImage(imageResult);
    Texture2D originalTexture = LoadTextureFromImage(imageFrom);

    std::vector<Color> usedColors;
    std::vector<int> colorRepeats;
    int colorVariance = 4; // Between 0 and 255

    //Go through every pixel
    for(int row = 0; row < imgFromWidth; row++)
    {   
        for(int col = 0; col < imgFromHeight; col++)
        {
            // Checking the color of the current pixel
            auto testColor = pixelsFrom[row * imgFromWidth + col];

            // Going through each saved color and checking if it's similar enough to increase the count
            bool colorAdded = false;
            for (int i = 0; i < usedColors.size(); i++)
            {
                if (SimilarColors(usedColors[i], testColor, colorVariance))
                {
                    colorAdded = true;
                    colorRepeats[i]++;
                    break;
                }
            }

            // If the color isn't similar enough, it will be considered a new color abd will be added to the vector
            if (!colorAdded)
            {
                usedColors.push_back(testColor);
                colorRepeats.push_back(1);
            }
        }
    }

    // Sorting the vectors using Insertion Sort
    SortColorIntArrays(usedColors, colorRepeats);

    // Creating a texture of the colors
    int pixelIndex = 0;
    for (int i = 0; i < usedColors.size(); i++)
    {
        // Adding a pixel for each time a color is repeated
        for (int j = 0; j < colorRepeats[i]; j++)
        {
            pixelsResult[pixelIndex] = usedColors[i];
            pixelIndex++;
        }
    }

    UpdateTexture(resultTexture, pixelsResult);

    float scaleFactor = (float)(screenWidth - 60) / (float)(imgFromWidth * 2);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // drawing logic goes here
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextureEx(originalTexture, Vector2(20, 20), 0, scaleFactor, WHITE);
        DrawTextureEx(resultTexture, Vector2(40 + (imgFromWidth * scaleFactor), 20), 0, scaleFactor, WHITE);
        EndDrawing();
    }

    UnloadTexture(originalTexture);
    UnloadTexture(resultTexture);

    CloseWindow();
    return 0;
}