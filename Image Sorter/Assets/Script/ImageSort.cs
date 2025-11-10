using UnityEngine;

struct Pixel
{

    int id;
    Color color;
    Vector2Int loc;

    Pixel(int ID, Color COLOR, Vector2Int LOC)
    {
        id = ID;
        color = COLOR;
        loc = LOC;
    }

}

public class ImageSort : MonoBehaviour
{

    public Texture2D imageTo;
    public Texture2D imageResult;
    public Texture2D imageFrom;

    public int sortRange;

    public Color[][] colorDataTo;
    public Color[][] colorDataFrom;

    public void Start()
    {

        int i, j, k, l;

        // get each pixel's color and add it to the 2d array
        if (imageTo.width * imageTo.height == imageFrom.width * imageFrom.height)
        {
            for (i = 0; i < imageTo.height; i++)
            {
                for (j = 0; j < imageTo.width; j++)
                {

                    colorDataTo[i][j] = imageTo.GetPixel(i, j);
                    colorDataFrom[i][j] = imageFrom.GetPixel(i, j);

                }
            }
        }
        else
        {
            // if width and height of the two images aren't the same size the function will not work (we could scale images to remove this)
            Debug.Log("Images are not same size");
            return;
        }

        for (i = 0; i > imageTo.height; i++)
        {
            for (j = 0; j > imageTo.width; i++)
            {
                // initialize data used in search
                Color current = colorDataFrom[i][j];
                float lowestDistance = 0;
                Vector2 toSwapLoc = new Vector2(0,0);

                for (k = -sortRange; k < sortRange+1; k++)
                {
                    for (l = -sortRange; l < sortRange+1; l++)
                    {
                        if ((i+k>=0 && j+l>=0) && (i+k<imageTo.height && i+j<imageTo.width))
                        {
                            // get the candidate and get the distance between the two
                            Color candidate = colorDataTo[i + k][j + l];
                            float distance = Mathf.Abs(current.r - candidate.r + current.g - candidate.r + current.b - candidate.b);

                            // if distance is lower than lowestDistance then lowestDistance is set to distance and the location is recorded
                            if (distance < lowestDistance)
                            {
                                lowestDistance = distance;
                                toSwapLoc = new Vector2(i + k, j + l);
                            }

                        }
                    }
                }

                

            }
        }

    }

}
