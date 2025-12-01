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
void SortByRepetition(Color* imageData, Image* originalImage, int width, int height, int variance);
void GridSort(Color* imageReturn, Image* imageFrom, Image* imageTo, int gridDivision);
void ImageSort(Color* imageReturn, Image* imageFrom, Image* imageTo);

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 1200;
    const int imageSize = 128;


    // Load Texture From Image Has To Happen After InitWindow
    InitWindow(screenWidth, screenHeight, "Pixel Sort");
    SetTargetFPS(60);

    // Generating base images and textures
    Image imageFrom = GenImageColor(imageSize, imageSize, WHITE);
    Image imageTo = GenImageColor(imageSize, imageSize, WHITE);
    Image imageResult = GenImageColor(imageSize, imageSize, WHITE);
    Color* pixelsResult = (Color*)imageResult.data;

    Texture2D resultTexture = LoadTextureFromImage(imageResult);
    Texture2D fromTexture = LoadTextureFromImage(imageFrom);
    Texture2D toTexture = LoadTextureFromImage(imageTo);

    int sortChoice = 0;
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "Welcome to the Sorting Lab!" << std::endl
        << "Pick which sort you'd like to perform:" << std::endl
        << "1. Sort by Color Repition" << std::endl
        << "2. Image Comparison Sort" << std::endl;
    //  << "3. Sort by Brightness" << std::endl;
    std::cin >> sortChoice;

    if (sortChoice == 1)
    {
        int imageChoice;
        std::string imageAddress = "Assets/";
        std::cout << "Please choose an image to sort by color repition" << std::endl
            << "1. AI Apple" << std::endl
            << "2. Obama" << std::endl
            << "3. Fun Noise" << std::endl
            << "4. Red to Green Gradient" << std::endl
            << "5. Black to White Gradient" << std::endl
            << "6. Shocked Cat" << std::endl
            << "7. Soldier" << std::endl
            << "8. Thinking Monkey" << std::endl
            << "9. Checkerboard" << std::endl;
        std::cin >> imageChoice;

        switch (imageChoice)
        {
        case 1: imageAddress += "AIApple.png"; break;
        case 2: imageAddress += "Obamify1.png"; break;
        case 3: imageAddress += "FunNoise.png"; break;
        case 4: imageAddress += "red_to_green.png"; break;
        case 5: imageAddress += "black_to_white.png"; break;
        case 6: imageAddress += "ShockedCat.png"; break;
        case 7: imageAddress += "Soldier.png"; break;
        case 8: imageAddress += "ThinkingMonkey.png"; break;
        case 9: imageAddress += "TestChecker2.png"; break;
        default: imageAddress += "FunNoise"; break;
        }

        int colorVariance;
        std::cout << "Choose the color variation the sort should allow for (0-255): ";
        std::cin >> colorVariance;

        // Performing the Sort
        imageFrom = LoadImage(imageAddress.c_str());
        SortByRepetition(pixelsResult, &imageFrom, imageSize, imageSize, colorVariance);
    }
    else if (sortChoice == 2)
    {
        int originalImageChoice;
        std::string originalImageAddress = "Assets/";
        std::cout << "Please choose an image to get sorted" << std::endl
            << "1. AI Apple" << std::endl
            << "2. Obama" << std::endl
            << "3. Fun Noise" << std::endl
            << "4. Red to Green Gradient" << std::endl
            << "5. Black to White Gradient" << std::endl
            << "6. Shocked Cat" << std::endl
            << "7. Soldier" << std::endl
            << "8. Thinking Monkey" << std::endl
            << "9. Checkerboard" << std::endl;
        std::cin >> originalImageChoice;

        switch (originalImageChoice)
        {
        case 1: originalImageAddress += "AIApple.png"; break;
        case 2: originalImageAddress += "Obamify1.png"; break;
        case 3: originalImageAddress += "FunNoise.png"; break;
        case 4: originalImageAddress += "red_to_green.png"; break;
        case 5: originalImageAddress += "black_to_white.png"; break;
        case 6: originalImageAddress += "ShockedCat.png"; break;
        case 7: originalImageAddress += "Soldier.png"; break;
        case 8: originalImageAddress += "ThinkingMonkey.png"; break;
        case 9: originalImageAddress += "TestChecker2.png"; break;
        default: originalImageAddress += "FunNoise"; break;
        }

        int baseImageChoice;
        std::string baseImageAddress = "Assets/";
        std::cout << "Please choose an image to be the sort base" << std::endl
            << "1. AI Apple" << std::endl
            << "2. Obama" << std::endl
            << "3. Fun Noise" << std::endl
            << "4. Red to Green Gradient" << std::endl
            << "5. Black to White Gradient" << std::endl
            << "6. Shocked Cat" << std::endl
            << "7. Soldier" << std::endl
            << "8. Thinking Monkey" << std::endl
            << "9. Checkerboard" << std::endl;
        std::cin >> baseImageChoice;

        switch (baseImageChoice)
        {
        case 1: baseImageAddress += "AIApple.png"; break;
        case 2: baseImageAddress += "Obamify1.png"; break;
        case 3: baseImageAddress += "FunNoise.png"; break;
        case 4: baseImageAddress += "red_to_green.png"; break;
        case 5: baseImageAddress += "black_to_white.png"; break;
        case 6: baseImageAddress += "ShockedCat.png"; break;
        case 7: baseImageAddress += "Soldier.png"; break;
        case 8: baseImageAddress += "ThinkingMonkey.png"; break;
        case 9: baseImageAddress += "TestChecker2.png"; break;
        default: baseImageAddress += "Obamify1"; break;
        }

        // Performing the Sort
        imageFrom = LoadImage(originalImageAddress.c_str());
        imageTo = LoadImage(baseImageAddress.c_str());
        ImageSort(pixelsResult, &imageFrom, &imageTo);
    }


    // Updating the Textures
    UpdateTexture(fromTexture, imageFrom.data);
    UpdateTexture(toTexture, imageTo.data);
    UpdateTexture(resultTexture, pixelsResult);

    // Calculating some UI Scaling values
    float scaleFactor = (float)(screenWidth - 60) / (float)(imageSize * 2);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // drawing logic goes here
        BeginDrawing();
        ClearBackground(WHITE);

        // Drawing Images based on the choice
        if (sortChoice == 1)
        {
            DrawTextureEx(fromTexture, Vector2(20, 20), 0, scaleFactor, WHITE);
            DrawTextureEx(resultTexture, Vector2(40 + (imageSize * scaleFactor), 20), 0, scaleFactor, WHITE);
        }
        else if (sortChoice == 2)
        {
            DrawTextureEx(fromTexture, Vector2(20, 20), 0, scaleFactor, WHITE);
            DrawTextureEx(toTexture, Vector2(40 + (imageSize * scaleFactor), 20), 0, scaleFactor, WHITE);
            DrawTextureEx(resultTexture, Vector2(40 + (imageSize * scaleFactor) / 2, imageSize* scaleFactor + 40), 0, scaleFactor, WHITE);
        }

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
void SortByRepetition(Color* imageData, Image* originalImage, int width, int height, int variance)
{
    Color* originalData = (Color*)(originalImage->data);

    // Deifning Vectors
    std::vector<Color> usedColors;
    std::vector<int> colorRepeats;

    //Go through every pixel
    for (int row = 0; row < width; row++)
    {
        for (int col = 0; col < height; col++)
        {
            // Checking the color of the current pixel
            auto testColor = originalData[row * width + col];

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