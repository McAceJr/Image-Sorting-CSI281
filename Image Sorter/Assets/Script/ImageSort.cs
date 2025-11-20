using UnityEngine;

public class ImageSort : MonoBehaviour
{

    public Sprite imageTo;
    private Texture2D imageResult;
    private Sprite spriteResult;
    public Sprite imageFrom;

    public SpriteRenderer rendererTo;
    public SpriteRenderer rendererResult;
    public SpriteRenderer rendererFrom;

    public int sortRange;
    public const int IMAGE_SIZE = 64;
    public Color[,] colorDataTo = new Color[IMAGE_SIZE, IMAGE_SIZE];
    public Color[,] colorDataFrom = new Color[IMAGE_SIZE, IMAGE_SIZE];

    public void Start()
    {

        imageResult = new Texture2D(IMAGE_SIZE, IMAGE_SIZE);

        rendererTo.sprite = imageTo;

        rendererFrom.sprite = imageFrom;

        int i, j, k, l;

        // get each pixel's color and add it to the 2d array
        if (imageTo.texture.width * imageTo.texture.height == imageFrom.texture.width * imageFrom.texture.height)
        {
            for (i = 0; i < imageTo.texture.height; i++)
            {
                for (j = 0; j < imageTo.texture.width; j++)
                {

                    colorDataTo[i,j] = imageTo.texture.GetPixel(4, 4);
                    colorDataFrom[i,j] = imageFrom.texture.GetPixel(i, j);

                }
            }
        }
        else
        {
            // if width and height of the two images aren't the same size the function will not work (we could scale images to remove this)
            Debug.Log("Images are not same size");
            return;
        }

        for (i = 0; i > imageTo.texture.height; i++)
        {
            for (j = 0; j > imageTo.texture.width; i++)
            {
                // initialize data used in search
                Color current = colorDataFrom[i,j];
                float lowestDistance = 0;
                Vector2Int toSwapLoc = new Vector2Int(0,0);
                Color toSwapColor = new Color (0,0,0);

                for (k = -sortRange; k < sortRange+1; k++)
                {
                    for (l = -sortRange; l < sortRange+1; l++)
                    {
                        if ((i+k>=0 && j+l>=0) && (i+k<imageTo.texture.height && i+j<imageTo.texture.width))
                        {
                            // get the candidate and get the distance between the two
                            Color candidate = colorDataTo[i + k,j + l];
                            float distance = Mathf.Abs(current.r - candidate.r + current.g - candidate.r + current.b - candidate.b);

                            // if distance is lower than lowestDistance then lowestDistance is set to distance and the location is recorded
                            if (distance < lowestDistance)
                            {
                                lowestDistance = distance;
                                toSwapLoc = new Vector2Int(i + k, j + l);
                                toSwapColor = candidate;
                            }

                        }
                    }
                }

                Color testColor = ((i & j) != 0 ? Color.white : Color.black);
                imageResult.SetPixel(i, j, testColor);
                //imageResult.SetPixel(toSwapLoc.x, toSwapLoc.y, testColor);
                //imageResult.SetPixel(toSwapLoc.x, toSwapLoc.y, current);


            }
        }

        imageResult.Apply();

        spriteResult = Sprite.Create(imageResult, new Rect(0.0f, 0.0f, imageResult.width, imageResult.height), new Vector2(0.5f, 0.5f), 100.0f);

        rendererResult.sprite = spriteResult;

        Debug.Log("fuck you... here is your fucked up fucking image");

    }

}
