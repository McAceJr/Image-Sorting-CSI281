#include <raylib.h>
#include <raygui.h>
#include <cstdint>
#include <iostream>
#include <math.h>
#include <unordered_map>
#include <vector>

// Function Prototypes
bool SimilarColors(const Color& refenceColor, const Color& checkingColor, int variance);
void SortColorIntArrays(std::vector<Color>& colorVector, std::vector<int>& repeatVector);
void SortByRepetition(Color* imageData, int width, int height, int variance);
void GridSort(Color* imageReturn, Image* imageFrom, Image* imageTo, int gridDivision);
void ImageSort(Color* imageReturn, Image* imageFrom, Image* imageTo);

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 1200;

    // Load Texture From Image Has To Happen After InitWindow
    InitWindow(screenWidth, screenHeight, "Pixel Sort");

    SetTargetFPS(60);

    Image imageFrom = LoadImage("Assets/black_to_white.png");
    Image imageTo = LoadImage("Assets/Obamify1.png");
    auto pixelsFrom = (Color*)imageFrom.data;

    const int imgFromWidth = imageFrom.width, imgFromHeight = imageFrom.height;
    Image imageResult = GenImageColor(imgFromWidth, imgFromHeight, WHITE);
    auto pixelsResult = pixelsFrom;
    Texture2D resultTexture = LoadTextureFromImage(imageResult);
    Texture2D fromTexture = LoadTextureFromImage(imageFrom);
    Texture2D toTexture = LoadTextureFromImage(imageTo);

    // Performing the sort
    //int colorVariance = 4; // Between 0 and 255
    //SortByRepetition(pixelsResult, imgFromWidth, imgFromHeight, colorVariance);
    GridSort(pixelsResult, &imageFrom, &imageTo, 1);

    UpdateTexture(resultTexture, pixelsResult);

    float scaleFactor = (float)(screenWidth - 60) / (float)(imgFromWidth * 2);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // drawing logic goes here
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextureEx(fromTexture, Vector2(20, 20), 0, scaleFactor, WHITE);
        DrawTextureEx(toTexture, Vector2(40 + (imgFromWidth * scaleFactor), 20), 0, scaleFactor, WHITE);
        DrawTextureEx(resultTexture, Vector2(40 + (imgFromHeight * scaleFactor) / 2, imgFromHeight * scaleFactor + 40), 0, scaleFactor, WHITE);
        EndDrawing();
    }

    UnloadTexture(fromTexture);
    UnloadTexture(toTexture);
    UnloadTexture(resultTexture);

    CloseWindow();
    return 0;
}

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
void SortByRepetition(Color* imageData, int width, int height, int variance)
{
    // Deifning Vectors
    std::vector<Color> usedColors;
    std::vector<int> colorRepeats;

    //Go through every pixel
    for (int row = 0; row < width; row++)
    {
        for (int col = 0; col < height; col++)
        {
            // Checking the color of the current pixel
            auto testColor = imageData[row * width + col];

            // Going through each saved color and checking if it's similar enough to increase the count
            bool colorAdded = false;
            for (int i = 0; i < usedColors.size(); i++)
            {
                if (SimilarColors(usedColors[i], testColor, variance))
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
            imageData[pixelIndex] = usedColors[i];
            pixelIndex++;
        }
    }
}
void SortValueWithIndex(std::vector<float>& color, std::vector<int>& index)
{
    for (int i = 0; i < (color.size()); i++)
    {
        float currentColorValue = color[i];
        int currentIndexValue = index[i];
        int checkIndex = i - 1;

        while (checkIndex >= 0 && color[checkIndex] > currentColorValue)
        {
            color[checkIndex + 1] = color[checkIndex];
            index[checkIndex + 1] = index[checkIndex];
            checkIndex--;
        }
        color[checkIndex + 1] = currentColorValue;
        index[checkIndex + 1] = currentIndexValue;
    }
}
void GridSort(Color* imageReturn, Image* imageFrom, Image* imageTo, int gridDivision)
{
    int gridWidth = (imageFrom->width > imageTo->width ? imageTo->width : imageFrom->width);
    int gridHeight = (imageFrom->height > imageTo->height ? imageTo->height : imageFrom->height);

    Color* fromData = (Color*)imageFrom->data;
    Color* toData = (Color*)imageTo->data;

    int gridSize = gridWidth / gridDivision;

    // Looping through each grid
    for (int gridY = 0; gridY < gridDivision; gridY++)
    {
        for (int gridX = 0; gridX < gridDivision; gridX++)
        {
            // Vectors for keeping track of values
            std::vector<float> colorFromValues;
            std::vector<int> colorFromIndex;
            std::vector<float> colorToValues;
            std::vector<int> colorToIndex;

            // Looping through each pixel in the grid
            for (int localY = 0; localY < gridSize; localY++)
            {
                for (int localX = 0; localX < gridSize; localX++)
                {
                    int x = gridX * gridSize + localX;
                    int y = (localY * gridHeight) + (gridY * gridHeight * gridSize);
                    int position = x + y;

                    colorFromValues.push_back(0.299f * fromData[position].r + 0.587f * fromData[position].g + 0.114f * fromData[position].b);
                    colorFromIndex.push_back(position);
                    colorToValues.push_back(0.299f * toData[position].r + 0.587f * toData[position].g + 0.114f * toData[position].b);
                    colorToIndex.push_back(position);
                }
            }

            // Sorting Each Array
            SortValueWithIndex(colorFromValues, colorFromIndex);
            SortValueWithIndex(colorToValues, colorToIndex);

            // Assigning the values based on the sorted array
            for (int i = 0; i < colorFromValues.size(); i++)
            {
                imageReturn[colorToIndex[i]] = fromData[colorFromIndex[i]];
            }
        }
    }
}
void ImageSort(Color* imageReturn, Image* imageFrom, Image* imageTo)
{
    int imageWidth = (imageFrom->width > imageTo->width ? imageTo->width : imageFrom->width);
    int imageHeight = (imageFrom->height > imageTo->height ? imageTo->height : imageFrom->height);

    Color* fromData = (Color*)imageFrom->data;
    Color* toData = (Color*)imageTo->data;

    // Vectors for keeping track of values
    std::vector<float> colorFromValues;
    std::vector<int> colorFromIndex;
    std::vector<float> colorToValues;
    std::vector<int> colorToIndex;

    // Looping through each pixel
    for (int localY = 0; localY < imageHeight; localY++)
    {
        for (int localX = 0; localX < imageWidth; localX++)
        {
            int position = localX + imageHeight * localY;

            colorFromValues.push_back(0.299f * fromData[position].r + 0.587f * fromData[position].g + 0.114f * fromData[position].b);
            colorFromIndex.push_back(position);
            colorToValues.push_back(0.299f * toData[position].r + 0.587f * toData[position].g + 0.114f * toData[position].b);
            colorToIndex.push_back(position);
        }
    }

    // Sorting Each Array
    SortValueWithIndex(colorFromValues, colorFromIndex);
    SortValueWithIndex(colorToValues, colorToIndex);

    // Assigning the values based on the sorted array
    for (int i = 0; i < colorFromValues.size(); i++)
    {
        imageReturn[colorToIndex[i]] = fromData[colorFromIndex[i]];
    }
}