int randomForestClassifier(int attr[4]);
static int sumOfResult[3];
static int result[1][3];
static void tree0(int attr[4]);
static int voting();
void tree0(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[0][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[3] <= 165)
            {
                result[0][1] += 100;
            }
            else
            {
                if (attr[1] <= 310)
                {
                    result[0][2] += 100;
                }
                else
                {
                    result[0][1] += 100;
                }
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[3] <= 185)
                {
                    result[0][1] += 100;
                }
                else
                {
                    result[0][2] += 100;
                }
            }
            else
            {
                if (attr[1] <= 275)
                {
                    if (attr[3] <= 175)
                    {
                        result[0][1] += 100;
                    }
                    else
                    {
                        result[0][2] += 100;
                    }
                }
                else
                {
                    result[0][2] += 100;
                }
            }
        }
    }
}
int voting()
{
    for (int t = 0; t < 1; t++)
    {
        for (int c = 0; c < 3; c++)
        {
            sumOfResult[c] += result[t][c];
        }
    }
    int maxIndex, maxValue = 0;
    for (int i = 0; i < 3; i++)
    {
        if (sumOfResult[i] >= maxValue)
        {
            maxValue = sumOfResult[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}
void rst()
{
    for (int i = 0; i < 3; i++)
    {
        sumOfResult[i] = 0;
    }
    for (int t = 0; t < 1; t++)
    {
        for (int c = 0; c < 3; c++)
        {
            result[t][c] = 0;
        }
    }
}
int randomForestClassifier(int attr[4])
{
    rst();
    tree0(attr);
    return voting();
}