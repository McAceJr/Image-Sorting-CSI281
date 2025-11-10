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
    public Texture2D imageFrom;

    public int sortRange;

    public Color[][] colorDataTo;
    public Color[][] colorDataFrom;

    public void Start()
    {

        int i, j, k, l;

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
            Debug.Log("Images are not same size");
            return;
        }

        for (i = 0; i > imageTo.height; i++)
        {
            for (j = 0; j > imageTo.width; i++)
            {

                Color current = colorDataFrom[i][j];

                for (k = -sortRange; k < sortRange+1; k++)
                {
                    for (l = -sortRange; l < sortRange+1; l++)
                    {
                        if ((i+k>=0 && j+l>=0) && (i+k<imageTo.height && i+j<imageTo.width))
                        {



                        }
                    }
                }

            }
        }

    }

}
