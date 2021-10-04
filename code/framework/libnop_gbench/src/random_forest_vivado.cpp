#include "random_forest_vivado.h"

namespace VIVADO1
{
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
}  // namespace VIVADO1

namespace VIVADO10
{
static int sumOfResult[3];
static int result[10][3];
static void tree0(int attr[4]);
static void tree1(int attr[4]);
static void tree2(int attr[4]);
static void tree3(int attr[4]);
static void tree4(int attr[4]);
static void tree5(int attr[4]);
static void tree6(int attr[4]);
static void tree7(int attr[4]);
static void tree8(int attr[4]);
static void tree9(int attr[4]);
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
void tree1(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[1][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 485)
            {
                result[1][1] += 100;
            }
            else
            {
                if (attr[1] <= 245)
                {
                    result[1][2] += 100;
                }
                else
                {
                    if (attr[3] <= 155)
                    {
                        result[1][2] += 100;
                    }
                    else
                    {
                        result[1][1] += 100;
                    }
                }
            }
        }
        else
        {
            result[1][2] += 100;
        }
    }
}
void tree2(int attr[4])
{
    if (attr[0] <= 605)
    {
        if (attr[3] <= 80)
        {
            result[2][0] += 100;
        }
        else
        {
            if (attr[3] <= 170)
            {
                result[2][1] += 100;
            }
            else
            {
                if (attr[2] <= 495)
                {
                    if (attr[0] <= 595)
                    {
                        result[2][1] += 100;
                    }
                    else
                    {
                        result[2][2] += 100;
                    }
                }
                else
                {
                    result[2][2] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[3] <= 155)
        {
            result[2][1] += 100;
        }
        else
        {
            result[2][2] += 100;
        }
    }
}
void tree3(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[1] <= 270)
        {
            result[3][1] += 100;
        }
        else
        {
            if (attr[3] <= 105)
            {
                result[3][0] += 100;
            }
            else
            {
                result[3][1] += 100;
            }
        }
    }
    else
    {
        if (attr[0] <= 615)
        {
            if (attr[1] <= 350)
            {
                if (attr[3] <= 170)
                {
                    result[3][1] += 100;
                }
                else
                {
                    if (attr[3] <= 185)
                    {
                        if (attr[1] <= 310)
                        {
                            result[3][2] += 100;
                        }
                        else
                        {
                            result[3][1] += 100;
                        }
                    }
                    else
                    {
                        result[3][2] += 100;
                    }
                }
            }
            else
            {
                result[3][0] += 100;
            }
        }
        else
        {
            if (attr[1] <= 240)
            {
                result[3][1] += 100;
            }
            else
            {
                if (attr[3] <= 175)
                {
                    if (attr[1] <= 290)
                    {
                        if (attr[1] <= 265)
                        {
                            result[3][1] += 100;
                        }
                        else
                        {
                            result[3][2] += 100;
                        }
                    }
                    else
                    {
                        if (attr[0] <= 710)
                        {
                            result[3][1] += 100;
                        }
                        else
                        {
                            result[3][2] += 100;
                        }
                    }
                }
                else
                {
                    result[3][2] += 100;
                }
            }
        }
    }
}
void tree4(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[4][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 505)
            {
                result[4][1] += 100;
            }
            else
            {
                if (attr[3] <= 155)
                {
                    result[4][2] += 100;
                }
                else
                {
                    if (attr[1] <= 285)
                    {
                        result[4][1] += 100;
                    }
                    else
                    {
                        result[4][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 490)
            {
                if (attr[0] <= 595)
                {
                    result[4][1] += 100;
                }
                else
                {
                    result[4][2] += 100;
                }
            }
            else
            {
                result[4][2] += 100;
            }
        }
    }
}
void tree5(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[5][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[0] <= 710)
            {
                if (attr[2] <= 495)
                {
                    result[5][1] += 100;
                }
                else
                {
                    if (attr[1] <= 245)
                    {
                        result[5][2] += 100;
                    }
                    else
                    {
                        result[5][1] += 100;
                    }
                }
            }
            else
            {
                result[5][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 185)
            {
                if (attr[0] <= 595)
                {
                    result[5][1] += 100;
                }
                else
                {
                    result[5][2] += 100;
                }
            }
            else
            {
                result[5][2] += 100;
            }
        }
    }
}
void tree6(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[6][0] += 100;
    }
    else
    {
        if (attr[2] <= 485)
        {
            if (attr[0] <= 505)
            {
                if (attr[1] <= 245)
                {
                    result[6][1] += 100;
                }
                else
                {
                    result[6][2] += 100;
                }
            }
            else
            {
                if (attr[2] <= 475)
                {
                    result[6][1] += 100;
                }
                else
                {
                    if (attr[0] <= 595)
                    {
                        result[6][1] += 100;
                    }
                    else
                    {
                        result[6][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 515)
            {
                if (attr[0] <= 595)
                {
                    result[6][2] += 100;
                }
                else
                {
                    if (attr[0] <= 605)
                    {
                        result[6][1] += 100;
                    }
                    else
                    {
                        if (attr[2] <= 500)
                        {
                            if (attr[3] <= 165)
                            {
                                result[6][1] += 100;
                            }
                            else
                            {
                                result[6][2] += 100;
                            }
                        }
                        else
                        {
                            result[6][2] += 100;
                        }
                    }
                }
            }
            else
            {
                result[6][2] += 100;
            }
        }
    }
}
void tree7(int attr[4])
{
    if (attr[2] <= 475)
    {
        if (attr[2] <= 235)
        {
            result[7][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[7][1] += 100;
            }
            else
            {
                result[7][2] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[0] <= 620)
            {
                result[7][2] += 100;
            }
            else
            {
                result[7][1] += 100;
            }
        }
        else
        {
            result[7][2] += 100;
        }
    }
}
void tree8(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[8][0] += 100;
    }
    else
    {
        if (attr[0] <= 575)
        {
            result[8][1] += 100;
        }
        else
        {
            if (attr[2] <= 495)
            {
                if (attr[2] <= 485)
                {
                    result[8][1] += 100;
                }
                else
                {
                    if (attr[0] <= 660)
                    {
                        if (attr[3] <= 165)
                        {
                            result[8][1] += 100;
                        }
                        else
                        {
                            result[8][2] += 100;
                        }
                    }
                    else
                    {
                        result[8][1] += 100;
                    }
                }
            }
            else
            {
                if (attr[0] <= 610)
                {
                    if (attr[0] <= 590)
                    {
                        result[8][2] += 100;
                    }
                    else
                    {
                        if (attr[3] <= 155)
                        {
                            result[8][2] += 100;
                        }
                        else
                        {
                            result[8][1] += 100;
                        }
                    }
                }
                else
                {
                    if (attr[3] <= 175)
                    {
                        if (attr[1] <= 290)
                        {
                            result[8][2] += 100;
                        }
                        else
                        {
                            result[8][1] += 100;
                        }
                    }
                    else
                    {
                        result[8][2] += 100;
                    }
                }
            }
        }
    }
}
void tree9(int attr[4])
{
    if (attr[2] <= 495)
    {
        if (attr[2] <= 235)
        {
            result[9][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[9][1] += 100;
            }
            else
            {
                if (attr[1] <= 295)
                {
                    result[9][2] += 100;
                }
                else
                {
                    result[9][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[0] <= 610)
        {
            if (attr[1] <= 260)
            {
                result[9][2] += 100;
            }
            else
            {
                if (attr[0] <= 590)
                {
                    result[9][2] += 100;
                }
                else
                {
                    result[9][1] += 100;
                }
            }
        }
        else
        {
            result[9][2] += 100;
        }
    }
}
int voting()
{
    for (int t = 0; t < 10; t++)
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
    for (int t = 0; t < 10; t++)
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
    tree1(attr);
    tree2(attr);
    tree3(attr);
    tree4(attr);
    tree5(attr);
    tree6(attr);
    tree7(attr);
    tree8(attr);
    tree9(attr);
    return voting();
}
}  // namespace VIVADO10

namespace VIVADO20
{
static int sumOfResult[3];
static int result[20][3];
static void tree0(int attr[4]);
static void tree1(int attr[4]);
static void tree2(int attr[4]);
static void tree3(int attr[4]);
static void tree4(int attr[4]);
static void tree5(int attr[4]);
static void tree6(int attr[4]);
static void tree7(int attr[4]);
static void tree8(int attr[4]);
static void tree9(int attr[4]);
static void tree10(int attr[4]);
static void tree11(int attr[4]);
static void tree12(int attr[4]);
static void tree13(int attr[4]);
static void tree14(int attr[4]);
static void tree15(int attr[4]);
static void tree16(int attr[4]);
static void tree17(int attr[4]);
static void tree18(int attr[4]);
static void tree19(int attr[4]);
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
void tree1(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[1][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 485)
            {
                result[1][1] += 100;
            }
            else
            {
                if (attr[1] <= 245)
                {
                    result[1][2] += 100;
                }
                else
                {
                    if (attr[3] <= 155)
                    {
                        result[1][2] += 100;
                    }
                    else
                    {
                        result[1][1] += 100;
                    }
                }
            }
        }
        else
        {
            result[1][2] += 100;
        }
    }
}
void tree2(int attr[4])
{
    if (attr[0] <= 605)
    {
        if (attr[3] <= 80)
        {
            result[2][0] += 100;
        }
        else
        {
            if (attr[3] <= 170)
            {
                result[2][1] += 100;
            }
            else
            {
                if (attr[2] <= 495)
                {
                    if (attr[0] <= 595)
                    {
                        result[2][1] += 100;
                    }
                    else
                    {
                        result[2][2] += 100;
                    }
                }
                else
                {
                    result[2][2] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[3] <= 155)
        {
            result[2][1] += 100;
        }
        else
        {
            result[2][2] += 100;
        }
    }
}
void tree3(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[1] <= 270)
        {
            result[3][1] += 100;
        }
        else
        {
            if (attr[3] <= 105)
            {
                result[3][0] += 100;
            }
            else
            {
                result[3][1] += 100;
            }
        }
    }
    else
    {
        if (attr[0] <= 615)
        {
            if (attr[1] <= 350)
            {
                if (attr[3] <= 170)
                {
                    result[3][1] += 100;
                }
                else
                {
                    if (attr[3] <= 185)
                    {
                        if (attr[1] <= 310)
                        {
                            result[3][2] += 100;
                        }
                        else
                        {
                            result[3][1] += 100;
                        }
                    }
                    else
                    {
                        result[3][2] += 100;
                    }
                }
            }
            else
            {
                result[3][0] += 100;
            }
        }
        else
        {
            if (attr[1] <= 240)
            {
                result[3][1] += 100;
            }
            else
            {
                if (attr[3] <= 175)
                {
                    if (attr[1] <= 290)
                    {
                        if (attr[1] <= 265)
                        {
                            result[3][1] += 100;
                        }
                        else
                        {
                            result[3][2] += 100;
                        }
                    }
                    else
                    {
                        if (attr[0] <= 710)
                        {
                            result[3][1] += 100;
                        }
                        else
                        {
                            result[3][2] += 100;
                        }
                    }
                }
                else
                {
                    result[3][2] += 100;
                }
            }
        }
    }
}
void tree4(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[4][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 505)
            {
                result[4][1] += 100;
            }
            else
            {
                if (attr[3] <= 155)
                {
                    result[4][2] += 100;
                }
                else
                {
                    if (attr[1] <= 285)
                    {
                        result[4][1] += 100;
                    }
                    else
                    {
                        result[4][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 490)
            {
                if (attr[0] <= 595)
                {
                    result[4][1] += 100;
                }
                else
                {
                    result[4][2] += 100;
                }
            }
            else
            {
                result[4][2] += 100;
            }
        }
    }
}
void tree5(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[5][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[0] <= 710)
            {
                if (attr[2] <= 495)
                {
                    result[5][1] += 100;
                }
                else
                {
                    if (attr[1] <= 245)
                    {
                        result[5][2] += 100;
                    }
                    else
                    {
                        result[5][1] += 100;
                    }
                }
            }
            else
            {
                result[5][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 185)
            {
                if (attr[0] <= 595)
                {
                    result[5][1] += 100;
                }
                else
                {
                    result[5][2] += 100;
                }
            }
            else
            {
                result[5][2] += 100;
            }
        }
    }
}
void tree6(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[6][0] += 100;
    }
    else
    {
        if (attr[2] <= 485)
        {
            if (attr[0] <= 505)
            {
                if (attr[1] <= 245)
                {
                    result[6][1] += 100;
                }
                else
                {
                    result[6][2] += 100;
                }
            }
            else
            {
                if (attr[2] <= 475)
                {
                    result[6][1] += 100;
                }
                else
                {
                    if (attr[0] <= 595)
                    {
                        result[6][1] += 100;
                    }
                    else
                    {
                        result[6][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 515)
            {
                if (attr[0] <= 595)
                {
                    result[6][2] += 100;
                }
                else
                {
                    if (attr[0] <= 605)
                    {
                        result[6][1] += 100;
                    }
                    else
                    {
                        if (attr[2] <= 500)
                        {
                            if (attr[3] <= 165)
                            {
                                result[6][1] += 100;
                            }
                            else
                            {
                                result[6][2] += 100;
                            }
                        }
                        else
                        {
                            result[6][2] += 100;
                        }
                    }
                }
            }
            else
            {
                result[6][2] += 100;
            }
        }
    }
}
void tree7(int attr[4])
{
    if (attr[2] <= 475)
    {
        if (attr[2] <= 235)
        {
            result[7][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[7][1] += 100;
            }
            else
            {
                result[7][2] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[0] <= 620)
            {
                result[7][2] += 100;
            }
            else
            {
                result[7][1] += 100;
            }
        }
        else
        {
            result[7][2] += 100;
        }
    }
}
void tree8(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[8][0] += 100;
    }
    else
    {
        if (attr[0] <= 575)
        {
            result[8][1] += 100;
        }
        else
        {
            if (attr[2] <= 495)
            {
                if (attr[2] <= 485)
                {
                    result[8][1] += 100;
                }
                else
                {
                    if (attr[0] <= 660)
                    {
                        if (attr[3] <= 165)
                        {
                            result[8][1] += 100;
                        }
                        else
                        {
                            result[8][2] += 100;
                        }
                    }
                    else
                    {
                        result[8][1] += 100;
                    }
                }
            }
            else
            {
                if (attr[0] <= 610)
                {
                    if (attr[0] <= 590)
                    {
                        result[8][2] += 100;
                    }
                    else
                    {
                        if (attr[3] <= 155)
                        {
                            result[8][2] += 100;
                        }
                        else
                        {
                            result[8][1] += 100;
                        }
                    }
                }
                else
                {
                    if (attr[3] <= 175)
                    {
                        if (attr[1] <= 290)
                        {
                            result[8][2] += 100;
                        }
                        else
                        {
                            result[8][1] += 100;
                        }
                    }
                    else
                    {
                        result[8][2] += 100;
                    }
                }
            }
        }
    }
}
void tree9(int attr[4])
{
    if (attr[2] <= 495)
    {
        if (attr[2] <= 235)
        {
            result[9][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[9][1] += 100;
            }
            else
            {
                if (attr[1] <= 295)
                {
                    result[9][2] += 100;
                }
                else
                {
                    result[9][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[0] <= 610)
        {
            if (attr[1] <= 260)
            {
                result[9][2] += 100;
            }
            else
            {
                if (attr[0] <= 590)
                {
                    result[9][2] += 100;
                }
                else
                {
                    result[9][1] += 100;
                }
            }
        }
        else
        {
            result[9][2] += 100;
        }
    }
}
void tree10(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[10][0] += 100;
    }
    else
    {
        if (attr[2] <= 470)
        {
            result[10][1] += 100;
        }
        else
        {
            result[10][2] += 100;
        }
    }
}
void tree11(int attr[4])
{
    if (attr[2] <= 250)
    {
        result[11][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 545)
            {
                if (attr[1] <= 255)
                {
                    if (attr[3] <= 160)
                    {
                        result[11][1] += 100;
                    }
                    else
                    {
                        result[11][2] += 100;
                    }
                }
                else
                {
                    result[11][1] += 100;
                }
            }
            else
            {
                result[11][2] += 100;
            }
        }
        else
        {
            result[11][2] += 100;
        }
    }
}
void tree12(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[12][0] += 100;
    }
    else
    {
        if (attr[0] <= 605)
        {
            if (attr[2] <= 490)
            {
                result[12][1] += 100;
            }
            else
            {
                if (attr[0] <= 595)
                {
                    result[12][2] += 100;
                }
                else
                {
                    if (attr[3] <= 155)
                    {
                        result[12][2] += 100;
                    }
                    else
                    {
                        result[12][1] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                result[12][1] += 100;
            }
            else
            {
                result[12][2] += 100;
            }
        }
    }
}
void tree13(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[3] <= 80)
        {
            result[13][0] += 100;
        }
        else
        {
            if (attr[3] <= 160)
            {
                result[13][1] += 100;
            }
            else
            {
                result[13][2] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[2] <= 250)
            {
                result[13][0] += 100;
            }
            else
            {
                result[13][1] += 100;
            }
        }
        else
        {
            if (attr[2] <= 515)
            {
                if (attr[3] <= 180)
                {
                    if (attr[1] <= 245)
                    {
                        result[13][2] += 100;
                    }
                    else
                    {
                        result[13][1] += 100;
                    }
                }
                else
                {
                    result[13][2] += 100;
                }
            }
            else
            {
                result[13][2] += 100;
            }
        }
    }
}
void tree14(int attr[4])
{
    if (attr[2] <= 475)
    {
        if (attr[3] <= 80)
        {
            result[14][0] += 100;
        }
        else
        {
            if (attr[2] <= 445)
            {
                result[14][1] += 100;
            }
            else
            {
                if (attr[3] <= 165)
                {
                    result[14][1] += 100;
                }
                else
                {
                    result[14][2] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[0] <= 615)
            {
                result[14][2] += 100;
            }
            else
            {
                if (attr[0] <= 695)
                {
                    result[14][1] += 100;
                }
                else
                {
                    result[14][2] += 100;
                }
            }
        }
        else
        {
            result[14][2] += 100;
        }
    }
}
void tree15(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[2] <= 235)
        {
            result[15][0] += 100;
        }
        else
        {
            if (attr[0] <= 495)
            {
                result[15][2] += 100;
            }
            else
            {
                result[15][1] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 480)
        {
            if (attr[3] <= 70)
            {
                result[15][0] += 100;
            }
            else
            {
                result[15][1] += 100;
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[0] <= 620)
                {
                    result[15][2] += 100;
                }
                else
                {
                    result[15][1] += 100;
                }
            }
            else
            {
                result[15][2] += 100;
            }
        }
    }
}
void tree16(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[16][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[2] <= 485)
            {
                result[16][1] += 100;
            }
            else
            {
                if (attr[0] <= 620)
                {
                    result[16][2] += 100;
                }
                else
                {
                    result[16][1] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 615)
                {
                    result[16][1] += 100;
                }
                else
                {
                    if (attr[2] <= 505)
                    {
                        result[16][1] += 100;
                    }
                    else
                    {
                        result[16][2] += 100;
                    }
                }
            }
            else
            {
                result[16][2] += 100;
            }
        }
    }
}
void tree17(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[3] <= 80)
        {
            result[17][0] += 100;
        }
        else
        {
            if (attr[3] <= 160)
            {
                result[17][1] += 100;
            }
            else
            {
                result[17][2] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[3] <= 70)
            {
                result[17][0] += 100;
            }
            else
            {
                if (attr[1] <= 275)
                {
                    if (attr[0] <= 625)
                    {
                        if (attr[3] <= 175)
                        {
                            result[17][1] += 100;
                        }
                        else
                        {
                            result[17][2] += 100;
                        }
                    }
                    else
                    {
                        if (attr[1] <= 240)
                        {
                            result[17][1] += 100;
                        }
                        else
                        {
                            if (attr[3] <= 165)
                            {
                                result[17][1] += 100;
                            }
                            else
                            {
                                result[17][2] += 100;
                            }
                        }
                    }
                }
                else
                {
                    result[17][1] += 100;
                }
            }
        }
        else
        {
            if (attr[1] <= 275)
            {
                result[17][1] += 100;
            }
            else
            {
                result[17][2] += 100;
            }
        }
    }
}
void tree18(int attr[4])
{
    if (attr[0] <= 575)
    {
        if (attr[2] <= 235)
        {
            result[18][0] += 100;
        }
        else
        {
            if (attr[2] <= 435)
            {
                result[18][1] += 100;
            }
            else
            {
                if (attr[1] <= 275)
                {
                    result[18][2] += 100;
                }
                else
                {
                    result[18][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[0] <= 705)
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 615)
                {
                    if (attr[3] <= 155)
                    {
                        if (attr[2] <= 310)
                        {
                            result[18][0] += 100;
                        }
                        else
                        {
                            result[18][2] += 100;
                        }
                    }
                    else
                    {
                        result[18][1] += 100;
                    }
                }
                else
                {
                    result[18][1] += 100;
                }
            }
            else
            {
                if (attr[1] <= 315)
                {
                    result[18][2] += 100;
                }
                else
                {
                    if (attr[0] <= 620)
                    {
                        result[18][1] += 100;
                    }
                    else
                    {
                        result[18][2] += 100;
                    }
                }
            }
        }
        else
        {
            result[18][2] += 100;
        }
    }
}
void tree19(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[19][0] += 100;
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[2] <= 480)
            {
                if (attr[0] <= 495)
                {
                    if (attr[3] <= 135)
                    {
                        result[19][1] += 100;
                    }
                    else
                    {
                        result[19][2] += 100;
                    }
                }
                else
                {
                    result[19][1] += 100;
                }
            }
            else
            {
                if (attr[3] <= 175)
                {
                    if (attr[1] <= 235)
                    {
                        result[19][2] += 100;
                    }
                    else
                    {
                        result[19][1] += 100;
                    }
                }
                else
                {
                    result[19][2] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 170)
            {
                if (attr[1] <= 275)
                {
                    result[19][1] += 100;
                }
                else
                {
                    result[19][2] += 100;
                }
            }
            else
            {
                result[19][2] += 100;
            }
        }
    }
}
int voting()
{
    for (int t = 0; t < 20; t++)
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
    for (int t = 0; t < 20; t++)
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
    tree1(attr);
    tree2(attr);
    tree3(attr);
    tree4(attr);
    tree5(attr);
    tree6(attr);
    tree7(attr);
    tree8(attr);
    tree9(attr);
    tree10(attr);
    tree11(attr);
    tree12(attr);
    tree13(attr);
    tree14(attr);
    tree15(attr);
    tree16(attr);
    tree17(attr);
    tree18(attr);
    tree19(attr);
    return voting();
}
}  // namespace VIVADO20

namespace VIVADO50
{
static int sumOfResult[3];
static int result[50][3];
static void tree0(int attr[4]);
static void tree1(int attr[4]);
static void tree2(int attr[4]);
static void tree3(int attr[4]);
static void tree4(int attr[4]);
static void tree5(int attr[4]);
static void tree6(int attr[4]);
static void tree7(int attr[4]);
static void tree8(int attr[4]);
static void tree9(int attr[4]);
static void tree10(int attr[4]);
static void tree11(int attr[4]);
static void tree12(int attr[4]);
static void tree13(int attr[4]);
static void tree14(int attr[4]);
static void tree15(int attr[4]);
static void tree16(int attr[4]);
static void tree17(int attr[4]);
static void tree18(int attr[4]);
static void tree19(int attr[4]);
static void tree20(int attr[4]);
static void tree21(int attr[4]);
static void tree22(int attr[4]);
static void tree23(int attr[4]);
static void tree24(int attr[4]);
static void tree25(int attr[4]);
static void tree26(int attr[4]);
static void tree27(int attr[4]);
static void tree28(int attr[4]);
static void tree29(int attr[4]);
static void tree30(int attr[4]);
static void tree31(int attr[4]);
static void tree32(int attr[4]);
static void tree33(int attr[4]);
static void tree34(int attr[4]);
static void tree35(int attr[4]);
static void tree36(int attr[4]);
static void tree37(int attr[4]);
static void tree38(int attr[4]);
static void tree39(int attr[4]);
static void tree40(int attr[4]);
static void tree41(int attr[4]);
static void tree42(int attr[4]);
static void tree43(int attr[4]);
static void tree44(int attr[4]);
static void tree45(int attr[4]);
static void tree46(int attr[4]);
static void tree47(int attr[4]);
static void tree48(int attr[4]);
static void tree49(int attr[4]);
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
void tree1(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[1][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 485)
            {
                result[1][1] += 100;
            }
            else
            {
                if (attr[1] <= 245)
                {
                    result[1][2] += 100;
                }
                else
                {
                    if (attr[3] <= 155)
                    {
                        result[1][2] += 100;
                    }
                    else
                    {
                        result[1][1] += 100;
                    }
                }
            }
        }
        else
        {
            result[1][2] += 100;
        }
    }
}
void tree2(int attr[4])
{
    if (attr[0] <= 605)
    {
        if (attr[3] <= 80)
        {
            result[2][0] += 100;
        }
        else
        {
            if (attr[3] <= 170)
            {
                result[2][1] += 100;
            }
            else
            {
                if (attr[2] <= 495)
                {
                    if (attr[0] <= 595)
                    {
                        result[2][1] += 100;
                    }
                    else
                    {
                        result[2][2] += 100;
                    }
                }
                else
                {
                    result[2][2] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[3] <= 155)
        {
            result[2][1] += 100;
        }
        else
        {
            result[2][2] += 100;
        }
    }
}
void tree3(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[1] <= 270)
        {
            result[3][1] += 100;
        }
        else
        {
            if (attr[3] <= 105)
            {
                result[3][0] += 100;
            }
            else
            {
                result[3][1] += 100;
            }
        }
    }
    else
    {
        if (attr[0] <= 615)
        {
            if (attr[1] <= 350)
            {
                if (attr[3] <= 170)
                {
                    result[3][1] += 100;
                }
                else
                {
                    if (attr[3] <= 185)
                    {
                        if (attr[1] <= 310)
                        {
                            result[3][2] += 100;
                        }
                        else
                        {
                            result[3][1] += 100;
                        }
                    }
                    else
                    {
                        result[3][2] += 100;
                    }
                }
            }
            else
            {
                result[3][0] += 100;
            }
        }
        else
        {
            if (attr[1] <= 240)
            {
                result[3][1] += 100;
            }
            else
            {
                if (attr[3] <= 175)
                {
                    if (attr[1] <= 290)
                    {
                        if (attr[1] <= 265)
                        {
                            result[3][1] += 100;
                        }
                        else
                        {
                            result[3][2] += 100;
                        }
                    }
                    else
                    {
                        if (attr[0] <= 710)
                        {
                            result[3][1] += 100;
                        }
                        else
                        {
                            result[3][2] += 100;
                        }
                    }
                }
                else
                {
                    result[3][2] += 100;
                }
            }
        }
    }
}
void tree4(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[4][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 505)
            {
                result[4][1] += 100;
            }
            else
            {
                if (attr[3] <= 155)
                {
                    result[4][2] += 100;
                }
                else
                {
                    if (attr[1] <= 285)
                    {
                        result[4][1] += 100;
                    }
                    else
                    {
                        result[4][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 490)
            {
                if (attr[0] <= 595)
                {
                    result[4][1] += 100;
                }
                else
                {
                    result[4][2] += 100;
                }
            }
            else
            {
                result[4][2] += 100;
            }
        }
    }
}
void tree5(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[5][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[0] <= 710)
            {
                if (attr[2] <= 495)
                {
                    result[5][1] += 100;
                }
                else
                {
                    if (attr[1] <= 245)
                    {
                        result[5][2] += 100;
                    }
                    else
                    {
                        result[5][1] += 100;
                    }
                }
            }
            else
            {
                result[5][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 185)
            {
                if (attr[0] <= 595)
                {
                    result[5][1] += 100;
                }
                else
                {
                    result[5][2] += 100;
                }
            }
            else
            {
                result[5][2] += 100;
            }
        }
    }
}
void tree6(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[6][0] += 100;
    }
    else
    {
        if (attr[2] <= 485)
        {
            if (attr[0] <= 505)
            {
                if (attr[1] <= 245)
                {
                    result[6][1] += 100;
                }
                else
                {
                    result[6][2] += 100;
                }
            }
            else
            {
                if (attr[2] <= 475)
                {
                    result[6][1] += 100;
                }
                else
                {
                    if (attr[0] <= 595)
                    {
                        result[6][1] += 100;
                    }
                    else
                    {
                        result[6][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 515)
            {
                if (attr[0] <= 595)
                {
                    result[6][2] += 100;
                }
                else
                {
                    if (attr[0] <= 605)
                    {
                        result[6][1] += 100;
                    }
                    else
                    {
                        if (attr[2] <= 500)
                        {
                            if (attr[3] <= 165)
                            {
                                result[6][1] += 100;
                            }
                            else
                            {
                                result[6][2] += 100;
                            }
                        }
                        else
                        {
                            result[6][2] += 100;
                        }
                    }
                }
            }
            else
            {
                result[6][2] += 100;
            }
        }
    }
}
void tree7(int attr[4])
{
    if (attr[2] <= 475)
    {
        if (attr[2] <= 235)
        {
            result[7][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[7][1] += 100;
            }
            else
            {
                result[7][2] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[0] <= 620)
            {
                result[7][2] += 100;
            }
            else
            {
                result[7][1] += 100;
            }
        }
        else
        {
            result[7][2] += 100;
        }
    }
}
void tree8(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[8][0] += 100;
    }
    else
    {
        if (attr[0] <= 575)
        {
            result[8][1] += 100;
        }
        else
        {
            if (attr[2] <= 495)
            {
                if (attr[2] <= 485)
                {
                    result[8][1] += 100;
                }
                else
                {
                    if (attr[0] <= 660)
                    {
                        if (attr[3] <= 165)
                        {
                            result[8][1] += 100;
                        }
                        else
                        {
                            result[8][2] += 100;
                        }
                    }
                    else
                    {
                        result[8][1] += 100;
                    }
                }
            }
            else
            {
                if (attr[0] <= 610)
                {
                    if (attr[0] <= 590)
                    {
                        result[8][2] += 100;
                    }
                    else
                    {
                        if (attr[3] <= 155)
                        {
                            result[8][2] += 100;
                        }
                        else
                        {
                            result[8][1] += 100;
                        }
                    }
                }
                else
                {
                    if (attr[3] <= 175)
                    {
                        if (attr[1] <= 290)
                        {
                            result[8][2] += 100;
                        }
                        else
                        {
                            result[8][1] += 100;
                        }
                    }
                    else
                    {
                        result[8][2] += 100;
                    }
                }
            }
        }
    }
}
void tree9(int attr[4])
{
    if (attr[2] <= 495)
    {
        if (attr[2] <= 235)
        {
            result[9][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[9][1] += 100;
            }
            else
            {
                if (attr[1] <= 295)
                {
                    result[9][2] += 100;
                }
                else
                {
                    result[9][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[0] <= 610)
        {
            if (attr[1] <= 260)
            {
                result[9][2] += 100;
            }
            else
            {
                if (attr[0] <= 590)
                {
                    result[9][2] += 100;
                }
                else
                {
                    result[9][1] += 100;
                }
            }
        }
        else
        {
            result[9][2] += 100;
        }
    }
}
void tree10(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[10][0] += 100;
    }
    else
    {
        if (attr[2] <= 470)
        {
            result[10][1] += 100;
        }
        else
        {
            result[10][2] += 100;
        }
    }
}
void tree11(int attr[4])
{
    if (attr[2] <= 250)
    {
        result[11][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 545)
            {
                if (attr[1] <= 255)
                {
                    if (attr[3] <= 160)
                    {
                        result[11][1] += 100;
                    }
                    else
                    {
                        result[11][2] += 100;
                    }
                }
                else
                {
                    result[11][1] += 100;
                }
            }
            else
            {
                result[11][2] += 100;
            }
        }
        else
        {
            result[11][2] += 100;
        }
    }
}
void tree12(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[12][0] += 100;
    }
    else
    {
        if (attr[0] <= 605)
        {
            if (attr[2] <= 490)
            {
                result[12][1] += 100;
            }
            else
            {
                if (attr[0] <= 595)
                {
                    result[12][2] += 100;
                }
                else
                {
                    if (attr[3] <= 155)
                    {
                        result[12][2] += 100;
                    }
                    else
                    {
                        result[12][1] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                result[12][1] += 100;
            }
            else
            {
                result[12][2] += 100;
            }
        }
    }
}
void tree13(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[3] <= 80)
        {
            result[13][0] += 100;
        }
        else
        {
            if (attr[3] <= 160)
            {
                result[13][1] += 100;
            }
            else
            {
                result[13][2] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[2] <= 250)
            {
                result[13][0] += 100;
            }
            else
            {
                result[13][1] += 100;
            }
        }
        else
        {
            if (attr[2] <= 515)
            {
                if (attr[3] <= 180)
                {
                    if (attr[1] <= 245)
                    {
                        result[13][2] += 100;
                    }
                    else
                    {
                        result[13][1] += 100;
                    }
                }
                else
                {
                    result[13][2] += 100;
                }
            }
            else
            {
                result[13][2] += 100;
            }
        }
    }
}
void tree14(int attr[4])
{
    if (attr[2] <= 475)
    {
        if (attr[3] <= 80)
        {
            result[14][0] += 100;
        }
        else
        {
            if (attr[2] <= 445)
            {
                result[14][1] += 100;
            }
            else
            {
                if (attr[3] <= 165)
                {
                    result[14][1] += 100;
                }
                else
                {
                    result[14][2] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[0] <= 615)
            {
                result[14][2] += 100;
            }
            else
            {
                if (attr[0] <= 695)
                {
                    result[14][1] += 100;
                }
                else
                {
                    result[14][2] += 100;
                }
            }
        }
        else
        {
            result[14][2] += 100;
        }
    }
}
void tree15(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[2] <= 235)
        {
            result[15][0] += 100;
        }
        else
        {
            if (attr[0] <= 495)
            {
                result[15][2] += 100;
            }
            else
            {
                result[15][1] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 480)
        {
            if (attr[3] <= 70)
            {
                result[15][0] += 100;
            }
            else
            {
                result[15][1] += 100;
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[0] <= 620)
                {
                    result[15][2] += 100;
                }
                else
                {
                    result[15][1] += 100;
                }
            }
            else
            {
                result[15][2] += 100;
            }
        }
    }
}
void tree16(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[16][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[2] <= 485)
            {
                result[16][1] += 100;
            }
            else
            {
                if (attr[0] <= 620)
                {
                    result[16][2] += 100;
                }
                else
                {
                    result[16][1] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 615)
                {
                    result[16][1] += 100;
                }
                else
                {
                    if (attr[2] <= 505)
                    {
                        result[16][1] += 100;
                    }
                    else
                    {
                        result[16][2] += 100;
                    }
                }
            }
            else
            {
                result[16][2] += 100;
            }
        }
    }
}
void tree17(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[3] <= 80)
        {
            result[17][0] += 100;
        }
        else
        {
            if (attr[3] <= 160)
            {
                result[17][1] += 100;
            }
            else
            {
                result[17][2] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[3] <= 70)
            {
                result[17][0] += 100;
            }
            else
            {
                if (attr[1] <= 275)
                {
                    if (attr[0] <= 625)
                    {
                        if (attr[3] <= 175)
                        {
                            result[17][1] += 100;
                        }
                        else
                        {
                            result[17][2] += 100;
                        }
                    }
                    else
                    {
                        if (attr[1] <= 240)
                        {
                            result[17][1] += 100;
                        }
                        else
                        {
                            if (attr[3] <= 165)
                            {
                                result[17][1] += 100;
                            }
                            else
                            {
                                result[17][2] += 100;
                            }
                        }
                    }
                }
                else
                {
                    result[17][1] += 100;
                }
            }
        }
        else
        {
            if (attr[1] <= 275)
            {
                result[17][1] += 100;
            }
            else
            {
                result[17][2] += 100;
            }
        }
    }
}
void tree18(int attr[4])
{
    if (attr[0] <= 575)
    {
        if (attr[2] <= 235)
        {
            result[18][0] += 100;
        }
        else
        {
            if (attr[2] <= 435)
            {
                result[18][1] += 100;
            }
            else
            {
                if (attr[1] <= 275)
                {
                    result[18][2] += 100;
                }
                else
                {
                    result[18][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[0] <= 705)
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 615)
                {
                    if (attr[3] <= 155)
                    {
                        if (attr[2] <= 310)
                        {
                            result[18][0] += 100;
                        }
                        else
                        {
                            result[18][2] += 100;
                        }
                    }
                    else
                    {
                        result[18][1] += 100;
                    }
                }
                else
                {
                    result[18][1] += 100;
                }
            }
            else
            {
                if (attr[1] <= 315)
                {
                    result[18][2] += 100;
                }
                else
                {
                    if (attr[0] <= 620)
                    {
                        result[18][1] += 100;
                    }
                    else
                    {
                        result[18][2] += 100;
                    }
                }
            }
        }
        else
        {
            result[18][2] += 100;
        }
    }
}
void tree19(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[19][0] += 100;
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[2] <= 480)
            {
                if (attr[0] <= 495)
                {
                    if (attr[3] <= 135)
                    {
                        result[19][1] += 100;
                    }
                    else
                    {
                        result[19][2] += 100;
                    }
                }
                else
                {
                    result[19][1] += 100;
                }
            }
            else
            {
                if (attr[3] <= 175)
                {
                    if (attr[1] <= 235)
                    {
                        result[19][2] += 100;
                    }
                    else
                    {
                        result[19][1] += 100;
                    }
                }
                else
                {
                    result[19][2] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 170)
            {
                if (attr[1] <= 275)
                {
                    result[19][1] += 100;
                }
                else
                {
                    result[19][2] += 100;
                }
            }
            else
            {
                result[19][2] += 100;
            }
        }
    }
}
void tree20(int attr[4])
{
    if (attr[2] <= 260)
    {
        result[20][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[3] <= 165)
            {
                result[20][1] += 100;
            }
            else
            {
                if (attr[0] <= 595)
                {
                    result[20][1] += 100;
                }
                else
                {
                    result[20][2] += 100;
                }
            }
        }
        else
        {
            if (attr[0] <= 610)
            {
                if (attr[0] <= 595)
                {
                    result[20][2] += 100;
                }
                else
                {
                    if (attr[2] <= 505)
                    {
                        result[20][2] += 100;
                    }
                    else
                    {
                        result[20][1] += 100;
                    }
                }
            }
            else
            {
                result[20][2] += 100;
            }
        }
    }
}
void tree21(int attr[4])
{
    if (attr[2] <= 485)
    {
        if (attr[3] <= 80)
        {
            result[21][0] += 100;
        }
        else
        {
            result[21][1] += 100;
        }
    }
    else
    {
        if (attr[0] <= 660)
        {
            result[21][2] += 100;
        }
        else
        {
            if (attr[3] <= 175)
            {
                result[21][1] += 100;
            }
            else
            {
                result[21][2] += 100;
            }
        }
    }
}
void tree22(int attr[4])
{
    if (attr[2] <= 495)
    {
        if (attr[3] <= 80)
        {
            result[22][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[22][1] += 100;
            }
            else
            {
                if (attr[3] <= 175)
                {
                    result[22][2] += 100;
                }
                else
                {
                    if (attr[2] <= 485)
                    {
                        if (attr[0] <= 595)
                        {
                            result[22][1] += 100;
                        }
                        else
                        {
                            result[22][2] += 100;
                        }
                    }
                    else
                    {
                        result[22][2] += 100;
                    }
                }
            }
        }
    }
    else
    {
        result[22][2] += 100;
    }
}
void tree23(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[23][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[0] <= 695)
            {
                if (attr[2] <= 485)
                {
                    if (attr[0] <= 500)
                    {
                        result[23][2] += 100;
                    }
                    else
                    {
                        result[23][1] += 100;
                    }
                }
                else
                {
                    if (attr[0] <= 635)
                    {
                        result[23][2] += 100;
                    }
                    else
                    {
                        result[23][1] += 100;
                    }
                }
            }
            else
            {
                result[23][2] += 100;
            }
        }
        else
        {
            if (attr[0] <= 595)
            {
                if (attr[2] <= 490)
                {
                    result[23][1] += 100;
                }
                else
                {
                    result[23][2] += 100;
                }
            }
            else
            {
                result[23][2] += 100;
            }
        }
    }
}
void tree24(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[24][0] += 100;
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[3] <= 160)
            {
                result[24][1] += 100;
            }
            else
            {
                if (attr[0] <= 640)
                {
                    result[24][2] += 100;
                }
                else
                {
                    result[24][1] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 170)
            {
                if (attr[3] <= 155)
                {
                    result[24][2] += 100;
                }
                else
                {
                    result[24][1] += 100;
                }
            }
            else
            {
                result[24][2] += 100;
            }
        }
    }
}
void tree25(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[25][0] += 100;
    }
    else
    {
        if (attr[3] <= 165)
        {
            if (attr[2] <= 495)
            {
                result[25][1] += 100;
            }
            else
            {
                result[25][2] += 100;
            }
        }
        else
        {
            result[25][2] += 100;
        }
    }
}
void tree26(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[26][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[3] <= 145)
            {
                result[26][1] += 100;
            }
            else
            {
                if (attr[2] <= 505)
                {
                    if (attr[0] <= 540)
                    {
                        result[26][2] += 100;
                    }
                    else
                    {
                        result[26][1] += 100;
                    }
                }
                else
                {
                    result[26][2] += 100;
                }
            }
        }
        else
        {
            if (attr[2] <= 485)
            {
                if (attr[0] <= 595)
                {
                    result[26][1] += 100;
                }
                else
                {
                    result[26][2] += 100;
                }
            }
            else
            {
                result[26][2] += 100;
            }
        }
    }
}
void tree27(int attr[4])
{
    if (attr[2] <= 485)
    {
        if (attr[2] <= 235)
        {
            result[27][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[27][1] += 100;
            }
            else
            {
                if (attr[0] <= 540)
                {
                    result[27][2] += 100;
                }
                else
                {
                    result[27][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[1] <= 255)
        {
            if (attr[3] <= 170)
            {
                result[27][1] += 100;
            }
            else
            {
                result[27][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 695)
                {
                    result[27][1] += 100;
                }
                else
                {
                    result[27][2] += 100;
                }
            }
            else
            {
                result[27][2] += 100;
            }
        }
    }
}
void tree28(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[28][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[1] <= 225)
            {
                if (attr[0] <= 550)
                {
                    result[28][1] += 100;
                }
                else
                {
                    result[28][2] += 100;
                }
            }
            else
            {
                if (attr[3] <= 155)
                {
                    result[28][1] += 100;
                }
                else
                {
                    if (attr[0] <= 695)
                    {
                        result[28][1] += 100;
                    }
                    else
                    {
                        result[28][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 485)
            {
                if (attr[1] <= 310)
                {
                    result[28][2] += 100;
                }
                else
                {
                    result[28][1] += 100;
                }
            }
            else
            {
                result[28][2] += 100;
            }
        }
    }
}
void tree29(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[29][0] += 100;
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[2] <= 485)
            {
                if (attr[0] <= 500)
                {
                    result[29][2] += 100;
                }
                else
                {
                    if (attr[2] <= 475)
                    {
                        result[29][1] += 100;
                    }
                    else
                    {
                        if (attr[1] <= 310)
                        {
                            result[29][2] += 100;
                        }
                        else
                        {
                            result[29][1] += 100;
                        }
                    }
                }
            }
            else
            {
                if (attr[0] <= 650)
                {
                    if (attr[2] <= 495)
                    {
                        if (attr[0] <= 620)
                        {
                            result[29][2] += 100;
                        }
                        else
                        {
                            result[29][1] += 100;
                        }
                    }
                    else
                    {
                        result[29][2] += 100;
                    }
                }
                else
                {
                    result[29][1] += 100;
                }
            }
        }
        else
        {
            if (attr[0] <= 610)
            {
                if (attr[0] <= 590)
                {
                    result[29][2] += 100;
                }
                else
                {
                    result[29][1] += 100;
                }
            }
            else
            {
                result[29][2] += 100;
            }
        }
    }
}
void tree30(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[30][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 505)
            {
                result[30][1] += 100;
            }
            else
            {
                result[30][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 185)
            {
                if (attr[2] <= 485)
                {
                    result[30][1] += 100;
                }
                else
                {
                    result[30][2] += 100;
                }
            }
            else
            {
                result[30][2] += 100;
            }
        }
    }
}
void tree31(int attr[4])
{
    if (attr[2] <= 250)
    {
        result[31][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 495)
            {
                if (attr[3] <= 165)
                {
                    result[31][1] += 100;
                }
                else
                {
                    result[31][2] += 100;
                }
            }
            else
            {
                if (attr[3] <= 155)
                {
                    result[31][2] += 100;
                }
                else
                {
                    if (attr[0] <= 695)
                    {
                        result[31][1] += 100;
                    }
                    else
                    {
                        result[31][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[1] <= 315)
            {
                result[31][2] += 100;
            }
            else
            {
                if (attr[2] <= 495)
                {
                    result[31][1] += 100;
                }
                else
                {
                    result[31][2] += 100;
                }
            }
        }
    }
}
void tree32(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[32][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 495)
            {
                if (attr[3] <= 165)
                {
                    result[32][1] += 100;
                }
                else
                {
                    result[32][2] += 100;
                }
            }
            else
            {
                if (attr[1] <= 245)
                {
                    result[32][2] += 100;
                }
                else
                {
                    if (attr[2] <= 505)
                    {
                        result[32][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 615)
                        {
                            result[32][1] += 100;
                        }
                        else
                        {
                            result[32][2] += 100;
                        }
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 185)
            {
                if (attr[1] <= 315)
                {
                    result[32][2] += 100;
                }
                else
                {
                    result[32][1] += 100;
                }
            }
            else
            {
                result[32][2] += 100;
            }
        }
    }
}
void tree33(int attr[4])
{
    if (attr[0] <= 595)
    {
        if (attr[1] <= 305)
        {
            if (attr[0] <= 485)
            {
                result[33][0] += 100;
            }
            else
            {
                if (attr[3] <= 60)
                {
                    result[33][0] += 100;
                }
                else
                {
                    if (attr[2] <= 475)
                    {
                        if (attr[0] <= 495)
                        {
                            if (attr[3] <= 135)
                            {
                                result[33][1] += 100;
                            }
                            else
                            {
                                result[33][2] += 100;
                            }
                        }
                        else
                        {
                            result[33][1] += 100;
                        }
                    }
                    else
                    {
                        result[33][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 120)
            {
                result[33][0] += 100;
            }
            else
            {
                result[33][1] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 475)
        {
            result[33][1] += 100;
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[1] <= 245)
                {
                    result[33][2] += 100;
                }
                else
                {
                    if (attr[1] <= 275)
                    {
                        result[33][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 650)
                        {
                            result[33][2] += 100;
                        }
                        else
                        {
                            result[33][1] += 100;
                        }
                    }
                }
            }
            else
            {
                result[33][2] += 100;
            }
        }
    }
}
void tree34(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[34][0] += 100;
    }
    else
    {
        if (attr[3] <= 165)
        {
            if (attr[3] <= 145)
            {
                result[34][1] += 100;
            }
            else
            {
                if (attr[0] <= 610)
                {
                    if (attr[0] <= 570)
                    {
                        result[34][1] += 100;
                    }
                    else
                    {
                        if (attr[2] <= 505)
                        {
                            result[34][2] += 100;
                        }
                        else
                        {
                            result[34][1] += 100;
                        }
                    }
                }
                else
                {
                    if (attr[1] <= 265)
                    {
                        result[34][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 660)
                        {
                            result[34][2] += 100;
                        }
                        else
                        {
                            result[34][1] += 100;
                        }
                    }
                }
            }
        }
        else
        {
            result[34][2] += 100;
        }
    }
}
void tree35(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[35][0] += 100;
    }
    else
    {
        if (attr[3] <= 165)
        {
            if (attr[2] <= 545)
            {
                if (attr[3] <= 145)
                {
                    result[35][1] += 100;
                }
                else
                {
                    if (attr[2] <= 500)
                    {
                        result[35][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 615)
                        {
                            result[35][1] += 100;
                        }
                        else
                        {
                            result[35][2] += 100;
                        }
                    }
                }
            }
            else
            {
                result[35][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 185)
            {
                if (attr[1] <= 315)
                {
                    result[35][2] += 100;
                }
                else
                {
                    if (attr[2] <= 540)
                    {
                        result[35][1] += 100;
                    }
                    else
                    {
                        result[35][2] += 100;
                    }
                }
            }
            else
            {
                result[35][2] += 100;
            }
        }
    }
}
void tree36(int attr[4])
{
    if (attr[3] <= 175)
    {
        if (attr[3] <= 70)
        {
            result[36][0] += 100;
        }
        else
        {
            if (attr[0] <= 500)
            {
                result[36][2] += 100;
            }
            else
            {
                if (attr[1] <= 225)
                {
                    result[36][2] += 100;
                }
                else
                {
                    if (attr[2] <= 505)
                    {
                        result[36][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 615)
                        {
                            result[36][1] += 100;
                        }
                        else
                        {
                            result[36][2] += 100;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (attr[1] <= 315)
        {
            result[36][2] += 100;
        }
        else
        {
            if (attr[0] <= 605)
            {
                result[36][1] += 100;
            }
            else
            {
                result[36][2] += 100;
            }
        }
    }
}
void tree37(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[37][0] += 100;
    }
    else
    {
        if (attr[0] <= 605)
        {
            if (attr[2] <= 435)
            {
                result[37][1] += 100;
            }
            else
            {
                if (attr[0] <= 585)
                {
                    if (attr[2] <= 480)
                    {
                        if (attr[1] <= 265)
                        {
                            result[37][2] += 100;
                        }
                        else
                        {
                            result[37][1] += 100;
                        }
                    }
                    else
                    {
                        result[37][2] += 100;
                    }
                }
                else
                {
                    if (attr[1] <= 245)
                    {
                        result[37][2] += 100;
                    }
                    else
                    {
                        if (attr[3] <= 170)
                        {
                            result[37][1] += 100;
                        }
                        else
                        {
                            if (attr[0] <= 595)
                            {
                                result[37][1] += 100;
                            }
                            else
                            {
                                result[37][2] += 100;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[2] <= 505)
                {
                    result[37][1] += 100;
                }
                else
                {
                    result[37][2] += 100;
                }
            }
            else
            {
                result[37][2] += 100;
            }
        }
    }
}
void tree38(int attr[4])
{
    if (attr[3] <= 155)
    {
        if (attr[2] <= 235)
        {
            result[38][0] += 100;
        }
        else
        {
            result[38][1] += 100;
        }
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[1] <= 285)
            {
                result[38][1] += 100;
            }
            else
            {
                if (attr[3] <= 165)
                {
                    result[38][2] += 100;
                }
                else
                {
                    result[38][1] += 100;
                }
            }
        }
        else
        {
            if (attr[2] <= 485)
            {
                if (attr[1] <= 310)
                {
                    result[38][2] += 100;
                }
                else
                {
                    result[38][1] += 100;
                }
            }
            else
            {
                result[38][2] += 100;
            }
        }
    }
}
void tree39(int attr[4])
{
    if (attr[2] <= 250)
    {
        result[39][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            result[39][1] += 100;
        }
        else
        {
            if (attr[3] <= 170)
            {
                if (attr[1] <= 275)
                {
                    if (attr[2] <= 505)
                    {
                        result[39][2] += 100;
                    }
                    else
                    {
                        result[39][1] += 100;
                    }
                }
                else
                {
                    result[39][2] += 100;
                }
            }
            else
            {
                result[39][2] += 100;
            }
        }
    }
}
void tree40(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[40][0] += 100;
    }
    else
    {
        if (attr[3] <= 155)
        {
            result[40][1] += 100;
        }
        else
        {
            if (attr[2] <= 465)
            {
                result[40][1] += 100;
            }
            else
            {
                if (attr[0] <= 605)
                {
                    if (attr[2] <= 505)
                    {
                        result[40][2] += 100;
                    }
                    else
                    {
                        if (attr[3] <= 170)
                        {
                            result[40][1] += 100;
                        }
                        else
                        {
                            result[40][2] += 100;
                        }
                    }
                }
                else
                {
                    result[40][2] += 100;
                }
            }
        }
    }
}
void tree41(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[41][0] += 100;
    }
    else
    {
        if (attr[2] <= 480)
        {
            if (attr[2] <= 445)
            {
                result[41][1] += 100;
            }
            else
            {
                if (attr[0] <= 550)
                {
                    result[41][2] += 100;
                }
                else
                {
                    result[41][1] += 100;
                }
            }
        }
        else
        {
            if (attr[1] <= 275)
            {
                if (attr[1] <= 235)
                {
                    result[41][2] += 100;
                }
                else
                {
                    if (attr[3] <= 170)
                    {
                        result[41][1] += 100;
                    }
                    else
                    {
                        result[41][2] += 100;
                    }
                }
            }
            else
            {
                result[41][2] += 100;
            }
        }
    }
}
void tree42(int attr[4])
{
    if (attr[3] <= 155)
    {
        if (attr[3] <= 75)
        {
            result[42][0] += 100;
        }
        else
        {
            if (attr[3] <= 145)
            {
                result[42][1] += 100;
            }
            else
            {
                if (attr[1] <= 290)
                {
                    if (attr[1] <= 250)
                    {
                        result[42][1] += 100;
                    }
                    else
                    {
                        result[42][2] += 100;
                    }
                }
                else
                {
                    result[42][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[3] <= 165)
        {
            if (attr[0] <= 660)
            {
                result[42][1] += 100;
            }
            else
            {
                result[42][2] += 100;
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[0] <= 650)
                {
                    if (attr[1] <= 310)
                    {
                        result[42][2] += 100;
                    }
                    else
                    {
                        result[42][1] += 100;
                    }
                }
                else
                {
                    result[42][1] += 100;
                }
            }
            else
            {
                result[42][2] += 100;
            }
        }
    }
}
void tree43(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[43][0] += 100;
    }
    else
    {
        if (attr[2] <= 475)
        {
            if (attr[3] <= 165)
            {
                result[43][1] += 100;
            }
            else
            {
                result[43][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[3] <= 155)
                {
                    if (attr[1] <= 265)
                    {
                        result[43][1] += 100;
                    }
                    else
                    {
                        result[43][2] += 100;
                    }
                }
                else
                {
                    result[43][1] += 100;
                }
            }
            else
            {
                if (attr[2] <= 485)
                {
                    if (attr[0] <= 595)
                    {
                        result[43][1] += 100;
                    }
                    else
                    {
                        result[43][2] += 100;
                    }
                }
                else
                {
                    result[43][2] += 100;
                }
            }
        }
    }
}
void tree44(int attr[4])
{
    if (attr[0] <= 555)
    {
        if (attr[2] <= 235)
        {
            result[44][0] += 100;
        }
        else
        {
            if (attr[0] <= 495)
            {
                result[44][2] += 100;
            }
            else
            {
                result[44][1] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[1] <= 360)
            {
                if (attr[0] <= 605)
                {
                    result[44][1] += 100;
                }
                else
                {
                    if (attr[3] <= 165)
                    {
                        result[44][1] += 100;
                    }
                    else
                    {
                        result[44][2] += 100;
                    }
                }
            }
            else
            {
                result[44][0] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[3] <= 165)
                {
                    result[44][2] += 100;
                }
                else
                {
                    result[44][1] += 100;
                }
            }
            else
            {
                result[44][2] += 100;
            }
        }
    }
}
void tree45(int attr[4])
{
    if (attr[2] <= 485)
    {
        if (attr[3] <= 75)
        {
            result[45][0] += 100;
        }
        else
        {
            if (attr[1] <= 260)
            {
                if (attr[2] <= 420)
                {
                    result[45][1] += 100;
                }
                else
                {
                    if (attr[0] <= 555)
                    {
                        result[45][2] += 100;
                    }
                    else
                    {
                        result[45][1] += 100;
                    }
                }
            }
            else
            {
                result[45][1] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 515)
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 650)
                {
                    if (attr[1] <= 245)
                    {
                        result[45][2] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 615)
                        {
                            result[45][1] += 100;
                        }
                        else
                        {
                            result[45][2] += 100;
                        }
                    }
                }
                else
                {
                    result[45][1] += 100;
                }
            }
            else
            {
                result[45][2] += 100;
            }
        }
        else
        {
            result[45][2] += 100;
        }
    }
}
void tree46(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[46][0] += 100;
    }
    else
    {
        if (attr[2] <= 480)
        {
            if (attr[0] <= 500)
            {
                if (attr[1] <= 245)
                {
                    result[46][1] += 100;
                }
                else
                {
                    result[46][2] += 100;
                }
            }
            else
            {
                result[46][1] += 100;
            }
        }
        else
        {
            if (attr[2] <= 515)
            {
                if (attr[3] <= 175)
                {
                    if (attr[0] <= 650)
                    {
                        if (attr[2] <= 505)
                        {
                            result[46][2] += 100;
                        }
                        else
                        {
                            if (attr[0] <= 615)
                            {
                                result[46][1] += 100;
                            }
                            else
                            {
                                result[46][2] += 100;
                            }
                        }
                    }
                    else
                    {
                        result[46][1] += 100;
                    }
                }
                else
                {
                    result[46][2] += 100;
                }
            }
            else
            {
                result[46][2] += 100;
            }
        }
    }
}
void tree47(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[47][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[3] <= 165)
            {
                result[47][1] += 100;
            }
            else
            {
                if (attr[0] <= 595)
                {
                    if (attr[2] <= 465)
                    {
                        result[47][2] += 100;
                    }
                    else
                    {
                        result[47][1] += 100;
                    }
                }
                else
                {
                    result[47][2] += 100;
                }
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[0] <= 635)
                {
                    result[47][2] += 100;
                }
                else
                {
                    result[47][1] += 100;
                }
            }
            else
            {
                result[47][2] += 100;
            }
        }
    }
}
void tree48(int attr[4])
{
    if (attr[3] <= 165)
    {
        if (attr[3] <= 75)
        {
            result[48][0] += 100;
        }
        else
        {
            if (attr[1] <= 225)
            {
                if (attr[0] <= 610)
                {
                    result[48][2] += 100;
                }
                else
                {
                    result[48][1] += 100;
                }
            }
            else
            {
                if (attr[0] <= 620)
                {
                    result[48][1] += 100;
                }
                else
                {
                    if (attr[1] <= 285)
                    {
                        if (attr[3] <= 140)
                        {
                            result[48][1] += 100;
                        }
                        else
                        {
                            if (attr[1] <= 265)
                            {
                                result[48][1] += 100;
                            }
                            else
                            {
                                result[48][2] += 100;
                            }
                        }
                    }
                    else
                    {
                        result[48][1] += 100;
                    }
                }
            }
        }
    }
    else
    {
        if (attr[0] <= 595)
        {
            if (attr[1] <= 295)
            {
                result[48][2] += 100;
            }
            else
            {
                result[48][1] += 100;
            }
        }
        else
        {
            result[48][2] += 100;
        }
    }
}
void tree49(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[49][0] += 100;
    }
    else
    {
        if (attr[0] <= 565)
        {
            if (attr[3] <= 160)
            {
                result[49][1] += 100;
            }
            else
            {
                result[49][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[1] <= 285)
                {
                    if (attr[1] <= 270)
                    {
                        result[49][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 600)
                        {
                            result[49][1] += 100;
                        }
                        else
                        {
                            result[49][2] += 100;
                        }
                    }
                }
                else
                {
                    result[49][1] += 100;
                }
            }
            else
            {
                result[49][2] += 100;
            }
        }
    }
}
int voting()
{
    for (int t = 0; t < 50; t++)
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
    for (int t = 0; t < 50; t++)
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
    tree1(attr);
    tree2(attr);
    tree3(attr);
    tree4(attr);
    tree5(attr);
    tree6(attr);
    tree7(attr);
    tree8(attr);
    tree9(attr);
    tree10(attr);
    tree11(attr);
    tree12(attr);
    tree13(attr);
    tree14(attr);
    tree15(attr);
    tree16(attr);
    tree17(attr);
    tree18(attr);
    tree19(attr);
    tree20(attr);
    tree21(attr);
    tree22(attr);
    tree23(attr);
    tree24(attr);
    tree25(attr);
    tree26(attr);
    tree27(attr);
    tree28(attr);
    tree29(attr);
    tree30(attr);
    tree31(attr);
    tree32(attr);
    tree33(attr);
    tree34(attr);
    tree35(attr);
    tree36(attr);
    tree37(attr);
    tree38(attr);
    tree39(attr);
    tree40(attr);
    tree41(attr);
    tree42(attr);
    tree43(attr);
    tree44(attr);
    tree45(attr);
    tree46(attr);
    tree47(attr);
    tree48(attr);
    tree49(attr);
    return voting();
}
}  // namespace VIVADO50

namespace VIVADO100
{
static int sumOfResult[3];
static int result[100][3];
static void tree0(int attr[4]);
static void tree1(int attr[4]);
static void tree2(int attr[4]);
static void tree3(int attr[4]);
static void tree4(int attr[4]);
static void tree5(int attr[4]);
static void tree6(int attr[4]);
static void tree7(int attr[4]);
static void tree8(int attr[4]);
static void tree9(int attr[4]);
static void tree10(int attr[4]);
static void tree11(int attr[4]);
static void tree12(int attr[4]);
static void tree13(int attr[4]);
static void tree14(int attr[4]);
static void tree15(int attr[4]);
static void tree16(int attr[4]);
static void tree17(int attr[4]);
static void tree18(int attr[4]);
static void tree19(int attr[4]);
static void tree20(int attr[4]);
static void tree21(int attr[4]);
static void tree22(int attr[4]);
static void tree23(int attr[4]);
static void tree24(int attr[4]);
static void tree25(int attr[4]);
static void tree26(int attr[4]);
static void tree27(int attr[4]);
static void tree28(int attr[4]);
static void tree29(int attr[4]);
static void tree30(int attr[4]);
static void tree31(int attr[4]);
static void tree32(int attr[4]);
static void tree33(int attr[4]);
static void tree34(int attr[4]);
static void tree35(int attr[4]);
static void tree36(int attr[4]);
static void tree37(int attr[4]);
static void tree38(int attr[4]);
static void tree39(int attr[4]);
static void tree40(int attr[4]);
static void tree41(int attr[4]);
static void tree42(int attr[4]);
static void tree43(int attr[4]);
static void tree44(int attr[4]);
static void tree45(int attr[4]);
static void tree46(int attr[4]);
static void tree47(int attr[4]);
static void tree48(int attr[4]);
static void tree49(int attr[4]);
static void tree50(int attr[4]);
static void tree51(int attr[4]);
static void tree52(int attr[4]);
static void tree53(int attr[4]);
static void tree54(int attr[4]);
static void tree55(int attr[4]);
static void tree56(int attr[4]);
static void tree57(int attr[4]);
static void tree58(int attr[4]);
static void tree59(int attr[4]);
static void tree60(int attr[4]);
static void tree61(int attr[4]);
static void tree62(int attr[4]);
static void tree63(int attr[4]);
static void tree64(int attr[4]);
static void tree65(int attr[4]);
static void tree66(int attr[4]);
static void tree67(int attr[4]);
static void tree68(int attr[4]);
static void tree69(int attr[4]);
static void tree70(int attr[4]);
static void tree71(int attr[4]);
static void tree72(int attr[4]);
static void tree73(int attr[4]);
static void tree74(int attr[4]);
static void tree75(int attr[4]);
static void tree76(int attr[4]);
static void tree77(int attr[4]);
static void tree78(int attr[4]);
static void tree79(int attr[4]);
static void tree80(int attr[4]);
static void tree81(int attr[4]);
static void tree82(int attr[4]);
static void tree83(int attr[4]);
static void tree84(int attr[4]);
static void tree85(int attr[4]);
static void tree86(int attr[4]);
static void tree87(int attr[4]);
static void tree88(int attr[4]);
static void tree89(int attr[4]);
static void tree90(int attr[4]);
static void tree91(int attr[4]);
static void tree92(int attr[4]);
static void tree93(int attr[4]);
static void tree94(int attr[4]);
static void tree95(int attr[4]);
static void tree96(int attr[4]);
static void tree97(int attr[4]);
static void tree98(int attr[4]);
static void tree99(int attr[4]);
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
void tree1(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[1][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 485)
            {
                result[1][1] += 100;
            }
            else
            {
                if (attr[1] <= 245)
                {
                    result[1][2] += 100;
                }
                else
                {
                    if (attr[3] <= 155)
                    {
                        result[1][2] += 100;
                    }
                    else
                    {
                        result[1][1] += 100;
                    }
                }
            }
        }
        else
        {
            result[1][2] += 100;
        }
    }
}
void tree2(int attr[4])
{
    if (attr[0] <= 605)
    {
        if (attr[3] <= 80)
        {
            result[2][0] += 100;
        }
        else
        {
            if (attr[3] <= 170)
            {
                result[2][1] += 100;
            }
            else
            {
                if (attr[2] <= 495)
                {
                    if (attr[0] <= 595)
                    {
                        result[2][1] += 100;
                    }
                    else
                    {
                        result[2][2] += 100;
                    }
                }
                else
                {
                    result[2][2] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[3] <= 155)
        {
            result[2][1] += 100;
        }
        else
        {
            result[2][2] += 100;
        }
    }
}
void tree3(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[1] <= 270)
        {
            result[3][1] += 100;
        }
        else
        {
            if (attr[3] <= 105)
            {
                result[3][0] += 100;
            }
            else
            {
                result[3][1] += 100;
            }
        }
    }
    else
    {
        if (attr[0] <= 615)
        {
            if (attr[1] <= 350)
            {
                if (attr[3] <= 170)
                {
                    result[3][1] += 100;
                }
                else
                {
                    if (attr[3] <= 185)
                    {
                        if (attr[1] <= 310)
                        {
                            result[3][2] += 100;
                        }
                        else
                        {
                            result[3][1] += 100;
                        }
                    }
                    else
                    {
                        result[3][2] += 100;
                    }
                }
            }
            else
            {
                result[3][0] += 100;
            }
        }
        else
        {
            if (attr[1] <= 240)
            {
                result[3][1] += 100;
            }
            else
            {
                if (attr[3] <= 175)
                {
                    if (attr[1] <= 290)
                    {
                        if (attr[1] <= 265)
                        {
                            result[3][1] += 100;
                        }
                        else
                        {
                            result[3][2] += 100;
                        }
                    }
                    else
                    {
                        if (attr[0] <= 710)
                        {
                            result[3][1] += 100;
                        }
                        else
                        {
                            result[3][2] += 100;
                        }
                    }
                }
                else
                {
                    result[3][2] += 100;
                }
            }
        }
    }
}
void tree4(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[4][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 505)
            {
                result[4][1] += 100;
            }
            else
            {
                if (attr[3] <= 155)
                {
                    result[4][2] += 100;
                }
                else
                {
                    if (attr[1] <= 285)
                    {
                        result[4][1] += 100;
                    }
                    else
                    {
                        result[4][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 490)
            {
                if (attr[0] <= 595)
                {
                    result[4][1] += 100;
                }
                else
                {
                    result[4][2] += 100;
                }
            }
            else
            {
                result[4][2] += 100;
            }
        }
    }
}
void tree5(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[5][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[0] <= 710)
            {
                if (attr[2] <= 495)
                {
                    result[5][1] += 100;
                }
                else
                {
                    if (attr[1] <= 245)
                    {
                        result[5][2] += 100;
                    }
                    else
                    {
                        result[5][1] += 100;
                    }
                }
            }
            else
            {
                result[5][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 185)
            {
                if (attr[0] <= 595)
                {
                    result[5][1] += 100;
                }
                else
                {
                    result[5][2] += 100;
                }
            }
            else
            {
                result[5][2] += 100;
            }
        }
    }
}
void tree6(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[6][0] += 100;
    }
    else
    {
        if (attr[2] <= 485)
        {
            if (attr[0] <= 505)
            {
                if (attr[1] <= 245)
                {
                    result[6][1] += 100;
                }
                else
                {
                    result[6][2] += 100;
                }
            }
            else
            {
                if (attr[2] <= 475)
                {
                    result[6][1] += 100;
                }
                else
                {
                    if (attr[0] <= 595)
                    {
                        result[6][1] += 100;
                    }
                    else
                    {
                        result[6][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 515)
            {
                if (attr[0] <= 595)
                {
                    result[6][2] += 100;
                }
                else
                {
                    if (attr[0] <= 605)
                    {
                        result[6][1] += 100;
                    }
                    else
                    {
                        if (attr[2] <= 500)
                        {
                            if (attr[3] <= 165)
                            {
                                result[6][1] += 100;
                            }
                            else
                            {
                                result[6][2] += 100;
                            }
                        }
                        else
                        {
                            result[6][2] += 100;
                        }
                    }
                }
            }
            else
            {
                result[6][2] += 100;
            }
        }
    }
}
void tree7(int attr[4])
{
    if (attr[2] <= 475)
    {
        if (attr[2] <= 235)
        {
            result[7][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[7][1] += 100;
            }
            else
            {
                result[7][2] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[0] <= 620)
            {
                result[7][2] += 100;
            }
            else
            {
                result[7][1] += 100;
            }
        }
        else
        {
            result[7][2] += 100;
        }
    }
}
void tree8(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[8][0] += 100;
    }
    else
    {
        if (attr[0] <= 575)
        {
            result[8][1] += 100;
        }
        else
        {
            if (attr[2] <= 495)
            {
                if (attr[2] <= 485)
                {
                    result[8][1] += 100;
                }
                else
                {
                    if (attr[0] <= 660)
                    {
                        if (attr[3] <= 165)
                        {
                            result[8][1] += 100;
                        }
                        else
                        {
                            result[8][2] += 100;
                        }
                    }
                    else
                    {
                        result[8][1] += 100;
                    }
                }
            }
            else
            {
                if (attr[0] <= 610)
                {
                    if (attr[0] <= 590)
                    {
                        result[8][2] += 100;
                    }
                    else
                    {
                        if (attr[3] <= 155)
                        {
                            result[8][2] += 100;
                        }
                        else
                        {
                            result[8][1] += 100;
                        }
                    }
                }
                else
                {
                    if (attr[3] <= 175)
                    {
                        if (attr[1] <= 290)
                        {
                            result[8][2] += 100;
                        }
                        else
                        {
                            result[8][1] += 100;
                        }
                    }
                    else
                    {
                        result[8][2] += 100;
                    }
                }
            }
        }
    }
}
void tree9(int attr[4])
{
    if (attr[2] <= 495)
    {
        if (attr[2] <= 235)
        {
            result[9][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[9][1] += 100;
            }
            else
            {
                if (attr[1] <= 295)
                {
                    result[9][2] += 100;
                }
                else
                {
                    result[9][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[0] <= 610)
        {
            if (attr[1] <= 260)
            {
                result[9][2] += 100;
            }
            else
            {
                if (attr[0] <= 590)
                {
                    result[9][2] += 100;
                }
                else
                {
                    result[9][1] += 100;
                }
            }
        }
        else
        {
            result[9][2] += 100;
        }
    }
}
void tree10(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[10][0] += 100;
    }
    else
    {
        if (attr[2] <= 470)
        {
            result[10][1] += 100;
        }
        else
        {
            result[10][2] += 100;
        }
    }
}
void tree11(int attr[4])
{
    if (attr[2] <= 250)
    {
        result[11][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 545)
            {
                if (attr[1] <= 255)
                {
                    if (attr[3] <= 160)
                    {
                        result[11][1] += 100;
                    }
                    else
                    {
                        result[11][2] += 100;
                    }
                }
                else
                {
                    result[11][1] += 100;
                }
            }
            else
            {
                result[11][2] += 100;
            }
        }
        else
        {
            result[11][2] += 100;
        }
    }
}
void tree12(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[12][0] += 100;
    }
    else
    {
        if (attr[0] <= 605)
        {
            if (attr[2] <= 490)
            {
                result[12][1] += 100;
            }
            else
            {
                if (attr[0] <= 595)
                {
                    result[12][2] += 100;
                }
                else
                {
                    if (attr[3] <= 155)
                    {
                        result[12][2] += 100;
                    }
                    else
                    {
                        result[12][1] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                result[12][1] += 100;
            }
            else
            {
                result[12][2] += 100;
            }
        }
    }
}
void tree13(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[3] <= 80)
        {
            result[13][0] += 100;
        }
        else
        {
            if (attr[3] <= 160)
            {
                result[13][1] += 100;
            }
            else
            {
                result[13][2] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[2] <= 250)
            {
                result[13][0] += 100;
            }
            else
            {
                result[13][1] += 100;
            }
        }
        else
        {
            if (attr[2] <= 515)
            {
                if (attr[3] <= 180)
                {
                    if (attr[1] <= 245)
                    {
                        result[13][2] += 100;
                    }
                    else
                    {
                        result[13][1] += 100;
                    }
                }
                else
                {
                    result[13][2] += 100;
                }
            }
            else
            {
                result[13][2] += 100;
            }
        }
    }
}
void tree14(int attr[4])
{
    if (attr[2] <= 475)
    {
        if (attr[3] <= 80)
        {
            result[14][0] += 100;
        }
        else
        {
            if (attr[2] <= 445)
            {
                result[14][1] += 100;
            }
            else
            {
                if (attr[3] <= 165)
                {
                    result[14][1] += 100;
                }
                else
                {
                    result[14][2] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[0] <= 615)
            {
                result[14][2] += 100;
            }
            else
            {
                if (attr[0] <= 695)
                {
                    result[14][1] += 100;
                }
                else
                {
                    result[14][2] += 100;
                }
            }
        }
        else
        {
            result[14][2] += 100;
        }
    }
}
void tree15(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[2] <= 235)
        {
            result[15][0] += 100;
        }
        else
        {
            if (attr[0] <= 495)
            {
                result[15][2] += 100;
            }
            else
            {
                result[15][1] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 480)
        {
            if (attr[3] <= 70)
            {
                result[15][0] += 100;
            }
            else
            {
                result[15][1] += 100;
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[0] <= 620)
                {
                    result[15][2] += 100;
                }
                else
                {
                    result[15][1] += 100;
                }
            }
            else
            {
                result[15][2] += 100;
            }
        }
    }
}
void tree16(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[16][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[2] <= 485)
            {
                result[16][1] += 100;
            }
            else
            {
                if (attr[0] <= 620)
                {
                    result[16][2] += 100;
                }
                else
                {
                    result[16][1] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 615)
                {
                    result[16][1] += 100;
                }
                else
                {
                    if (attr[2] <= 505)
                    {
                        result[16][1] += 100;
                    }
                    else
                    {
                        result[16][2] += 100;
                    }
                }
            }
            else
            {
                result[16][2] += 100;
            }
        }
    }
}
void tree17(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[3] <= 80)
        {
            result[17][0] += 100;
        }
        else
        {
            if (attr[3] <= 160)
            {
                result[17][1] += 100;
            }
            else
            {
                result[17][2] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[3] <= 70)
            {
                result[17][0] += 100;
            }
            else
            {
                if (attr[1] <= 275)
                {
                    if (attr[0] <= 625)
                    {
                        if (attr[3] <= 175)
                        {
                            result[17][1] += 100;
                        }
                        else
                        {
                            result[17][2] += 100;
                        }
                    }
                    else
                    {
                        if (attr[1] <= 240)
                        {
                            result[17][1] += 100;
                        }
                        else
                        {
                            if (attr[3] <= 165)
                            {
                                result[17][1] += 100;
                            }
                            else
                            {
                                result[17][2] += 100;
                            }
                        }
                    }
                }
                else
                {
                    result[17][1] += 100;
                }
            }
        }
        else
        {
            if (attr[1] <= 275)
            {
                result[17][1] += 100;
            }
            else
            {
                result[17][2] += 100;
            }
        }
    }
}
void tree18(int attr[4])
{
    if (attr[0] <= 575)
    {
        if (attr[2] <= 235)
        {
            result[18][0] += 100;
        }
        else
        {
            if (attr[2] <= 435)
            {
                result[18][1] += 100;
            }
            else
            {
                if (attr[1] <= 275)
                {
                    result[18][2] += 100;
                }
                else
                {
                    result[18][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[0] <= 705)
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 615)
                {
                    if (attr[3] <= 155)
                    {
                        if (attr[2] <= 310)
                        {
                            result[18][0] += 100;
                        }
                        else
                        {
                            result[18][2] += 100;
                        }
                    }
                    else
                    {
                        result[18][1] += 100;
                    }
                }
                else
                {
                    result[18][1] += 100;
                }
            }
            else
            {
                if (attr[1] <= 315)
                {
                    result[18][2] += 100;
                }
                else
                {
                    if (attr[0] <= 620)
                    {
                        result[18][1] += 100;
                    }
                    else
                    {
                        result[18][2] += 100;
                    }
                }
            }
        }
        else
        {
            result[18][2] += 100;
        }
    }
}
void tree19(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[19][0] += 100;
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[2] <= 480)
            {
                if (attr[0] <= 495)
                {
                    if (attr[3] <= 135)
                    {
                        result[19][1] += 100;
                    }
                    else
                    {
                        result[19][2] += 100;
                    }
                }
                else
                {
                    result[19][1] += 100;
                }
            }
            else
            {
                if (attr[3] <= 175)
                {
                    if (attr[1] <= 235)
                    {
                        result[19][2] += 100;
                    }
                    else
                    {
                        result[19][1] += 100;
                    }
                }
                else
                {
                    result[19][2] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 170)
            {
                if (attr[1] <= 275)
                {
                    result[19][1] += 100;
                }
                else
                {
                    result[19][2] += 100;
                }
            }
            else
            {
                result[19][2] += 100;
            }
        }
    }
}
void tree20(int attr[4])
{
    if (attr[2] <= 260)
    {
        result[20][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[3] <= 165)
            {
                result[20][1] += 100;
            }
            else
            {
                if (attr[0] <= 595)
                {
                    result[20][1] += 100;
                }
                else
                {
                    result[20][2] += 100;
                }
            }
        }
        else
        {
            if (attr[0] <= 610)
            {
                if (attr[0] <= 595)
                {
                    result[20][2] += 100;
                }
                else
                {
                    if (attr[2] <= 505)
                    {
                        result[20][2] += 100;
                    }
                    else
                    {
                        result[20][1] += 100;
                    }
                }
            }
            else
            {
                result[20][2] += 100;
            }
        }
    }
}
void tree21(int attr[4])
{
    if (attr[2] <= 485)
    {
        if (attr[3] <= 80)
        {
            result[21][0] += 100;
        }
        else
        {
            result[21][1] += 100;
        }
    }
    else
    {
        if (attr[0] <= 660)
        {
            result[21][2] += 100;
        }
        else
        {
            if (attr[3] <= 175)
            {
                result[21][1] += 100;
            }
            else
            {
                result[21][2] += 100;
            }
        }
    }
}
void tree22(int attr[4])
{
    if (attr[2] <= 495)
    {
        if (attr[3] <= 80)
        {
            result[22][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[22][1] += 100;
            }
            else
            {
                if (attr[3] <= 175)
                {
                    result[22][2] += 100;
                }
                else
                {
                    if (attr[2] <= 485)
                    {
                        if (attr[0] <= 595)
                        {
                            result[22][1] += 100;
                        }
                        else
                        {
                            result[22][2] += 100;
                        }
                    }
                    else
                    {
                        result[22][2] += 100;
                    }
                }
            }
        }
    }
    else
    {
        result[22][2] += 100;
    }
}
void tree23(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[23][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[0] <= 695)
            {
                if (attr[2] <= 485)
                {
                    if (attr[0] <= 500)
                    {
                        result[23][2] += 100;
                    }
                    else
                    {
                        result[23][1] += 100;
                    }
                }
                else
                {
                    if (attr[0] <= 635)
                    {
                        result[23][2] += 100;
                    }
                    else
                    {
                        result[23][1] += 100;
                    }
                }
            }
            else
            {
                result[23][2] += 100;
            }
        }
        else
        {
            if (attr[0] <= 595)
            {
                if (attr[2] <= 490)
                {
                    result[23][1] += 100;
                }
                else
                {
                    result[23][2] += 100;
                }
            }
            else
            {
                result[23][2] += 100;
            }
        }
    }
}
void tree24(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[24][0] += 100;
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[3] <= 160)
            {
                result[24][1] += 100;
            }
            else
            {
                if (attr[0] <= 640)
                {
                    result[24][2] += 100;
                }
                else
                {
                    result[24][1] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 170)
            {
                if (attr[3] <= 155)
                {
                    result[24][2] += 100;
                }
                else
                {
                    result[24][1] += 100;
                }
            }
            else
            {
                result[24][2] += 100;
            }
        }
    }
}
void tree25(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[25][0] += 100;
    }
    else
    {
        if (attr[3] <= 165)
        {
            if (attr[2] <= 495)
            {
                result[25][1] += 100;
            }
            else
            {
                result[25][2] += 100;
            }
        }
        else
        {
            result[25][2] += 100;
        }
    }
}
void tree26(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[26][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[3] <= 145)
            {
                result[26][1] += 100;
            }
            else
            {
                if (attr[2] <= 505)
                {
                    if (attr[0] <= 540)
                    {
                        result[26][2] += 100;
                    }
                    else
                    {
                        result[26][1] += 100;
                    }
                }
                else
                {
                    result[26][2] += 100;
                }
            }
        }
        else
        {
            if (attr[2] <= 485)
            {
                if (attr[0] <= 595)
                {
                    result[26][1] += 100;
                }
                else
                {
                    result[26][2] += 100;
                }
            }
            else
            {
                result[26][2] += 100;
            }
        }
    }
}
void tree27(int attr[4])
{
    if (attr[2] <= 485)
    {
        if (attr[2] <= 235)
        {
            result[27][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[27][1] += 100;
            }
            else
            {
                if (attr[0] <= 540)
                {
                    result[27][2] += 100;
                }
                else
                {
                    result[27][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[1] <= 255)
        {
            if (attr[3] <= 170)
            {
                result[27][1] += 100;
            }
            else
            {
                result[27][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 695)
                {
                    result[27][1] += 100;
                }
                else
                {
                    result[27][2] += 100;
                }
            }
            else
            {
                result[27][2] += 100;
            }
        }
    }
}
void tree28(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[28][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[1] <= 225)
            {
                if (attr[0] <= 550)
                {
                    result[28][1] += 100;
                }
                else
                {
                    result[28][2] += 100;
                }
            }
            else
            {
                if (attr[3] <= 155)
                {
                    result[28][1] += 100;
                }
                else
                {
                    if (attr[0] <= 695)
                    {
                        result[28][1] += 100;
                    }
                    else
                    {
                        result[28][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 485)
            {
                if (attr[1] <= 310)
                {
                    result[28][2] += 100;
                }
                else
                {
                    result[28][1] += 100;
                }
            }
            else
            {
                result[28][2] += 100;
            }
        }
    }
}
void tree29(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[29][0] += 100;
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[2] <= 485)
            {
                if (attr[0] <= 500)
                {
                    result[29][2] += 100;
                }
                else
                {
                    if (attr[2] <= 475)
                    {
                        result[29][1] += 100;
                    }
                    else
                    {
                        if (attr[1] <= 310)
                        {
                            result[29][2] += 100;
                        }
                        else
                        {
                            result[29][1] += 100;
                        }
                    }
                }
            }
            else
            {
                if (attr[0] <= 650)
                {
                    if (attr[2] <= 495)
                    {
                        if (attr[0] <= 620)
                        {
                            result[29][2] += 100;
                        }
                        else
                        {
                            result[29][1] += 100;
                        }
                    }
                    else
                    {
                        result[29][2] += 100;
                    }
                }
                else
                {
                    result[29][1] += 100;
                }
            }
        }
        else
        {
            if (attr[0] <= 610)
            {
                if (attr[0] <= 590)
                {
                    result[29][2] += 100;
                }
                else
                {
                    result[29][1] += 100;
                }
            }
            else
            {
                result[29][2] += 100;
            }
        }
    }
}
void tree30(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[30][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 505)
            {
                result[30][1] += 100;
            }
            else
            {
                result[30][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 185)
            {
                if (attr[2] <= 485)
                {
                    result[30][1] += 100;
                }
                else
                {
                    result[30][2] += 100;
                }
            }
            else
            {
                result[30][2] += 100;
            }
        }
    }
}
void tree31(int attr[4])
{
    if (attr[2] <= 250)
    {
        result[31][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 495)
            {
                if (attr[3] <= 165)
                {
                    result[31][1] += 100;
                }
                else
                {
                    result[31][2] += 100;
                }
            }
            else
            {
                if (attr[3] <= 155)
                {
                    result[31][2] += 100;
                }
                else
                {
                    if (attr[0] <= 695)
                    {
                        result[31][1] += 100;
                    }
                    else
                    {
                        result[31][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[1] <= 315)
            {
                result[31][2] += 100;
            }
            else
            {
                if (attr[2] <= 495)
                {
                    result[31][1] += 100;
                }
                else
                {
                    result[31][2] += 100;
                }
            }
        }
    }
}
void tree32(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[32][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 495)
            {
                if (attr[3] <= 165)
                {
                    result[32][1] += 100;
                }
                else
                {
                    result[32][2] += 100;
                }
            }
            else
            {
                if (attr[1] <= 245)
                {
                    result[32][2] += 100;
                }
                else
                {
                    if (attr[2] <= 505)
                    {
                        result[32][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 615)
                        {
                            result[32][1] += 100;
                        }
                        else
                        {
                            result[32][2] += 100;
                        }
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 185)
            {
                if (attr[1] <= 315)
                {
                    result[32][2] += 100;
                }
                else
                {
                    result[32][1] += 100;
                }
            }
            else
            {
                result[32][2] += 100;
            }
        }
    }
}
void tree33(int attr[4])
{
    if (attr[0] <= 595)
    {
        if (attr[1] <= 305)
        {
            if (attr[0] <= 485)
            {
                result[33][0] += 100;
            }
            else
            {
                if (attr[3] <= 60)
                {
                    result[33][0] += 100;
                }
                else
                {
                    if (attr[2] <= 475)
                    {
                        if (attr[0] <= 495)
                        {
                            if (attr[3] <= 135)
                            {
                                result[33][1] += 100;
                            }
                            else
                            {
                                result[33][2] += 100;
                            }
                        }
                        else
                        {
                            result[33][1] += 100;
                        }
                    }
                    else
                    {
                        result[33][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 120)
            {
                result[33][0] += 100;
            }
            else
            {
                result[33][1] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 475)
        {
            result[33][1] += 100;
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[1] <= 245)
                {
                    result[33][2] += 100;
                }
                else
                {
                    if (attr[1] <= 275)
                    {
                        result[33][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 650)
                        {
                            result[33][2] += 100;
                        }
                        else
                        {
                            result[33][1] += 100;
                        }
                    }
                }
            }
            else
            {
                result[33][2] += 100;
            }
        }
    }
}
void tree34(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[34][0] += 100;
    }
    else
    {
        if (attr[3] <= 165)
        {
            if (attr[3] <= 145)
            {
                result[34][1] += 100;
            }
            else
            {
                if (attr[0] <= 610)
                {
                    if (attr[0] <= 570)
                    {
                        result[34][1] += 100;
                    }
                    else
                    {
                        if (attr[2] <= 505)
                        {
                            result[34][2] += 100;
                        }
                        else
                        {
                            result[34][1] += 100;
                        }
                    }
                }
                else
                {
                    if (attr[1] <= 265)
                    {
                        result[34][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 660)
                        {
                            result[34][2] += 100;
                        }
                        else
                        {
                            result[34][1] += 100;
                        }
                    }
                }
            }
        }
        else
        {
            result[34][2] += 100;
        }
    }
}
void tree35(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[35][0] += 100;
    }
    else
    {
        if (attr[3] <= 165)
        {
            if (attr[2] <= 545)
            {
                if (attr[3] <= 145)
                {
                    result[35][1] += 100;
                }
                else
                {
                    if (attr[2] <= 500)
                    {
                        result[35][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 615)
                        {
                            result[35][1] += 100;
                        }
                        else
                        {
                            result[35][2] += 100;
                        }
                    }
                }
            }
            else
            {
                result[35][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 185)
            {
                if (attr[1] <= 315)
                {
                    result[35][2] += 100;
                }
                else
                {
                    if (attr[2] <= 540)
                    {
                        result[35][1] += 100;
                    }
                    else
                    {
                        result[35][2] += 100;
                    }
                }
            }
            else
            {
                result[35][2] += 100;
            }
        }
    }
}
void tree36(int attr[4])
{
    if (attr[3] <= 175)
    {
        if (attr[3] <= 70)
        {
            result[36][0] += 100;
        }
        else
        {
            if (attr[0] <= 500)
            {
                result[36][2] += 100;
            }
            else
            {
                if (attr[1] <= 225)
                {
                    result[36][2] += 100;
                }
                else
                {
                    if (attr[2] <= 505)
                    {
                        result[36][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 615)
                        {
                            result[36][1] += 100;
                        }
                        else
                        {
                            result[36][2] += 100;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (attr[1] <= 315)
        {
            result[36][2] += 100;
        }
        else
        {
            if (attr[0] <= 605)
            {
                result[36][1] += 100;
            }
            else
            {
                result[36][2] += 100;
            }
        }
    }
}
void tree37(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[37][0] += 100;
    }
    else
    {
        if (attr[0] <= 605)
        {
            if (attr[2] <= 435)
            {
                result[37][1] += 100;
            }
            else
            {
                if (attr[0] <= 585)
                {
                    if (attr[2] <= 480)
                    {
                        if (attr[1] <= 265)
                        {
                            result[37][2] += 100;
                        }
                        else
                        {
                            result[37][1] += 100;
                        }
                    }
                    else
                    {
                        result[37][2] += 100;
                    }
                }
                else
                {
                    if (attr[1] <= 245)
                    {
                        result[37][2] += 100;
                    }
                    else
                    {
                        if (attr[3] <= 170)
                        {
                            result[37][1] += 100;
                        }
                        else
                        {
                            if (attr[0] <= 595)
                            {
                                result[37][1] += 100;
                            }
                            else
                            {
                                result[37][2] += 100;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[2] <= 505)
                {
                    result[37][1] += 100;
                }
                else
                {
                    result[37][2] += 100;
                }
            }
            else
            {
                result[37][2] += 100;
            }
        }
    }
}
void tree38(int attr[4])
{
    if (attr[3] <= 155)
    {
        if (attr[2] <= 235)
        {
            result[38][0] += 100;
        }
        else
        {
            result[38][1] += 100;
        }
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[1] <= 285)
            {
                result[38][1] += 100;
            }
            else
            {
                if (attr[3] <= 165)
                {
                    result[38][2] += 100;
                }
                else
                {
                    result[38][1] += 100;
                }
            }
        }
        else
        {
            if (attr[2] <= 485)
            {
                if (attr[1] <= 310)
                {
                    result[38][2] += 100;
                }
                else
                {
                    result[38][1] += 100;
                }
            }
            else
            {
                result[38][2] += 100;
            }
        }
    }
}
void tree39(int attr[4])
{
    if (attr[2] <= 250)
    {
        result[39][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            result[39][1] += 100;
        }
        else
        {
            if (attr[3] <= 170)
            {
                if (attr[1] <= 275)
                {
                    if (attr[2] <= 505)
                    {
                        result[39][2] += 100;
                    }
                    else
                    {
                        result[39][1] += 100;
                    }
                }
                else
                {
                    result[39][2] += 100;
                }
            }
            else
            {
                result[39][2] += 100;
            }
        }
    }
}
void tree40(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[40][0] += 100;
    }
    else
    {
        if (attr[3] <= 155)
        {
            result[40][1] += 100;
        }
        else
        {
            if (attr[2] <= 465)
            {
                result[40][1] += 100;
            }
            else
            {
                if (attr[0] <= 605)
                {
                    if (attr[2] <= 505)
                    {
                        result[40][2] += 100;
                    }
                    else
                    {
                        if (attr[3] <= 170)
                        {
                            result[40][1] += 100;
                        }
                        else
                        {
                            result[40][2] += 100;
                        }
                    }
                }
                else
                {
                    result[40][2] += 100;
                }
            }
        }
    }
}
void tree41(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[41][0] += 100;
    }
    else
    {
        if (attr[2] <= 480)
        {
            if (attr[2] <= 445)
            {
                result[41][1] += 100;
            }
            else
            {
                if (attr[0] <= 550)
                {
                    result[41][2] += 100;
                }
                else
                {
                    result[41][1] += 100;
                }
            }
        }
        else
        {
            if (attr[1] <= 275)
            {
                if (attr[1] <= 235)
                {
                    result[41][2] += 100;
                }
                else
                {
                    if (attr[3] <= 170)
                    {
                        result[41][1] += 100;
                    }
                    else
                    {
                        result[41][2] += 100;
                    }
                }
            }
            else
            {
                result[41][2] += 100;
            }
        }
    }
}
void tree42(int attr[4])
{
    if (attr[3] <= 155)
    {
        if (attr[3] <= 75)
        {
            result[42][0] += 100;
        }
        else
        {
            if (attr[3] <= 145)
            {
                result[42][1] += 100;
            }
            else
            {
                if (attr[1] <= 290)
                {
                    if (attr[1] <= 250)
                    {
                        result[42][1] += 100;
                    }
                    else
                    {
                        result[42][2] += 100;
                    }
                }
                else
                {
                    result[42][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[3] <= 165)
        {
            if (attr[0] <= 660)
            {
                result[42][1] += 100;
            }
            else
            {
                result[42][2] += 100;
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[0] <= 650)
                {
                    if (attr[1] <= 310)
                    {
                        result[42][2] += 100;
                    }
                    else
                    {
                        result[42][1] += 100;
                    }
                }
                else
                {
                    result[42][1] += 100;
                }
            }
            else
            {
                result[42][2] += 100;
            }
        }
    }
}
void tree43(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[43][0] += 100;
    }
    else
    {
        if (attr[2] <= 475)
        {
            if (attr[3] <= 165)
            {
                result[43][1] += 100;
            }
            else
            {
                result[43][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[3] <= 155)
                {
                    if (attr[1] <= 265)
                    {
                        result[43][1] += 100;
                    }
                    else
                    {
                        result[43][2] += 100;
                    }
                }
                else
                {
                    result[43][1] += 100;
                }
            }
            else
            {
                if (attr[2] <= 485)
                {
                    if (attr[0] <= 595)
                    {
                        result[43][1] += 100;
                    }
                    else
                    {
                        result[43][2] += 100;
                    }
                }
                else
                {
                    result[43][2] += 100;
                }
            }
        }
    }
}
void tree44(int attr[4])
{
    if (attr[0] <= 555)
    {
        if (attr[2] <= 235)
        {
            result[44][0] += 100;
        }
        else
        {
            if (attr[0] <= 495)
            {
                result[44][2] += 100;
            }
            else
            {
                result[44][1] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[1] <= 360)
            {
                if (attr[0] <= 605)
                {
                    result[44][1] += 100;
                }
                else
                {
                    if (attr[3] <= 165)
                    {
                        result[44][1] += 100;
                    }
                    else
                    {
                        result[44][2] += 100;
                    }
                }
            }
            else
            {
                result[44][0] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[3] <= 165)
                {
                    result[44][2] += 100;
                }
                else
                {
                    result[44][1] += 100;
                }
            }
            else
            {
                result[44][2] += 100;
            }
        }
    }
}
void tree45(int attr[4])
{
    if (attr[2] <= 485)
    {
        if (attr[3] <= 75)
        {
            result[45][0] += 100;
        }
        else
        {
            if (attr[1] <= 260)
            {
                if (attr[2] <= 420)
                {
                    result[45][1] += 100;
                }
                else
                {
                    if (attr[0] <= 555)
                    {
                        result[45][2] += 100;
                    }
                    else
                    {
                        result[45][1] += 100;
                    }
                }
            }
            else
            {
                result[45][1] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 515)
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 650)
                {
                    if (attr[1] <= 245)
                    {
                        result[45][2] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 615)
                        {
                            result[45][1] += 100;
                        }
                        else
                        {
                            result[45][2] += 100;
                        }
                    }
                }
                else
                {
                    result[45][1] += 100;
                }
            }
            else
            {
                result[45][2] += 100;
            }
        }
        else
        {
            result[45][2] += 100;
        }
    }
}
void tree46(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[46][0] += 100;
    }
    else
    {
        if (attr[2] <= 480)
        {
            if (attr[0] <= 500)
            {
                if (attr[1] <= 245)
                {
                    result[46][1] += 100;
                }
                else
                {
                    result[46][2] += 100;
                }
            }
            else
            {
                result[46][1] += 100;
            }
        }
        else
        {
            if (attr[2] <= 515)
            {
                if (attr[3] <= 175)
                {
                    if (attr[0] <= 650)
                    {
                        if (attr[2] <= 505)
                        {
                            result[46][2] += 100;
                        }
                        else
                        {
                            if (attr[0] <= 615)
                            {
                                result[46][1] += 100;
                            }
                            else
                            {
                                result[46][2] += 100;
                            }
                        }
                    }
                    else
                    {
                        result[46][1] += 100;
                    }
                }
                else
                {
                    result[46][2] += 100;
                }
            }
            else
            {
                result[46][2] += 100;
            }
        }
    }
}
void tree47(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[47][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[3] <= 165)
            {
                result[47][1] += 100;
            }
            else
            {
                if (attr[0] <= 595)
                {
                    if (attr[2] <= 465)
                    {
                        result[47][2] += 100;
                    }
                    else
                    {
                        result[47][1] += 100;
                    }
                }
                else
                {
                    result[47][2] += 100;
                }
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[0] <= 635)
                {
                    result[47][2] += 100;
                }
                else
                {
                    result[47][1] += 100;
                }
            }
            else
            {
                result[47][2] += 100;
            }
        }
    }
}
void tree48(int attr[4])
{
    if (attr[3] <= 165)
    {
        if (attr[3] <= 75)
        {
            result[48][0] += 100;
        }
        else
        {
            if (attr[1] <= 225)
            {
                if (attr[0] <= 610)
                {
                    result[48][2] += 100;
                }
                else
                {
                    result[48][1] += 100;
                }
            }
            else
            {
                if (attr[0] <= 620)
                {
                    result[48][1] += 100;
                }
                else
                {
                    if (attr[1] <= 285)
                    {
                        if (attr[3] <= 140)
                        {
                            result[48][1] += 100;
                        }
                        else
                        {
                            if (attr[1] <= 265)
                            {
                                result[48][1] += 100;
                            }
                            else
                            {
                                result[48][2] += 100;
                            }
                        }
                    }
                    else
                    {
                        result[48][1] += 100;
                    }
                }
            }
        }
    }
    else
    {
        if (attr[0] <= 595)
        {
            if (attr[1] <= 295)
            {
                result[48][2] += 100;
            }
            else
            {
                result[48][1] += 100;
            }
        }
        else
        {
            result[48][2] += 100;
        }
    }
}
void tree49(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[49][0] += 100;
    }
    else
    {
        if (attr[0] <= 565)
        {
            if (attr[3] <= 160)
            {
                result[49][1] += 100;
            }
            else
            {
                result[49][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[1] <= 285)
                {
                    if (attr[1] <= 270)
                    {
                        result[49][1] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 600)
                        {
                            result[49][1] += 100;
                        }
                        else
                        {
                            result[49][2] += 100;
                        }
                    }
                }
                else
                {
                    result[49][1] += 100;
                }
            }
            else
            {
                result[49][2] += 100;
            }
        }
    }
}
void tree50(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[50][0] += 100;
    }
    else
    {
        if (attr[2] <= 475)
        {
            if (attr[3] <= 165)
            {
                result[50][1] += 100;
            }
            else
            {
                result[50][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[1] <= 235)
                {
                    result[50][2] += 100;
                }
                else
                {
                    if (attr[2] <= 545)
                    {
                        result[50][1] += 100;
                    }
                    else
                    {
                        result[50][2] += 100;
                    }
                }
            }
            else
            {
                if (attr[0] <= 595)
                {
                    result[50][1] += 100;
                }
                else
                {
                    result[50][2] += 100;
                }
            }
        }
    }
}
void tree51(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[51][0] += 100;
    }
    else
    {
        if (attr[2] <= 485)
        {
            if (attr[3] <= 165)
            {
                result[51][1] += 100;
            }
            else
            {
                if (attr[2] <= 465)
                {
                    result[51][2] += 100;
                }
                else
                {
                    if (attr[0] <= 595)
                    {
                        result[51][1] += 100;
                    }
                    else
                    {
                        result[51][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[51][1] += 100;
            }
            else
            {
                result[51][2] += 100;
            }
        }
    }
}
void tree52(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[52][0] += 100;
    }
    else
    {
        if (attr[2] <= 485)
        {
            if (attr[1] <= 255)
            {
                if (attr[2] <= 415)
                {
                    result[52][1] += 100;
                }
                else
                {
                    if (attr[0] <= 555)
                    {
                        result[52][2] += 100;
                    }
                    else
                    {
                        result[52][1] += 100;
                    }
                }
            }
            else
            {
                result[52][1] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[1] <= 285)
                {
                    result[52][1] += 100;
                }
                else
                {
                    if (attr[0] <= 705)
                    {
                        result[52][1] += 100;
                    }
                    else
                    {
                        result[52][2] += 100;
                    }
                }
            }
            else
            {
                result[52][2] += 100;
            }
        }
    }
}
void tree53(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[53][0] += 100;
    }
    else
    {
        if (attr[0] <= 575)
        {
            if (attr[3] <= 170)
            {
                result[53][1] += 100;
            }
            else
            {
                result[53][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[3] <= 145)
                {
                    result[53][1] += 100;
                }
                else
                {
                    if (attr[1] <= 290)
                    {
                        if (attr[1] <= 235)
                        {
                            result[53][2] += 100;
                        }
                        else
                        {
                            if (attr[1] <= 265)
                            {
                                result[53][1] += 100;
                            }
                            else
                            {
                                result[53][2] += 100;
                            }
                        }
                    }
                    else
                    {
                        result[53][1] += 100;
                    }
                }
            }
            else
            {
                result[53][2] += 100;
            }
        }
    }
}
void tree54(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[54][0] += 100;
    }
    else
    {
        if (attr[2] <= 485)
        {
            result[54][1] += 100;
        }
        else
        {
            if (attr[0] <= 605)
            {
                if (attr[3] <= 170)
                {
                    result[54][1] += 100;
                }
                else
                {
                    result[54][2] += 100;
                }
            }
            else
            {
                result[54][2] += 100;
            }
        }
    }
}
void tree55(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[55][0] += 100;
    }
    else
    {
        if (attr[0] <= 605)
        {
            if (attr[3] <= 185)
            {
                if (attr[1] <= 230)
                {
                    if (attr[2] <= 425)
                    {
                        result[55][1] += 100;
                    }
                    else
                    {
                        result[55][2] += 100;
                    }
                }
                else
                {
                    result[55][1] += 100;
                }
            }
            else
            {
                result[55][2] += 100;
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[2] <= 480)
                {
                    result[55][1] += 100;
                }
                else
                {
                    if (attr[3] <= 175)
                    {
                        result[55][1] += 100;
                    }
                    else
                    {
                        result[55][2] += 100;
                    }
                }
            }
            else
            {
                result[55][2] += 100;
            }
        }
    }
}
void tree56(int attr[4])
{
    if (attr[2] <= 250)
    {
        result[56][0] += 100;
    }
    else
    {
        if (attr[3] <= 165)
        {
            if (attr[2] <= 500)
            {
                result[56][1] += 100;
            }
            else
            {
                if (attr[0] <= 615)
                {
                    result[56][1] += 100;
                }
                else
                {
                    result[56][2] += 100;
                }
            }
        }
        else
        {
            if (attr[0] <= 595)
            {
                if (attr[3] <= 185)
                {
                    if (attr[0] <= 540)
                    {
                        result[56][2] += 100;
                    }
                    else
                    {
                        result[56][1] += 100;
                    }
                }
                else
                {
                    result[56][2] += 100;
                }
            }
            else
            {
                result[56][2] += 100;
            }
        }
    }
}
void tree57(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[57][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[3] <= 145)
            {
                result[57][1] += 100;
            }
            else
            {
                if (attr[0] <= 515)
                {
                    result[57][2] += 100;
                }
                else
                {
                    if (attr[3] <= 155)
                    {
                        if (attr[0] <= 595)
                        {
                            result[57][1] += 100;
                        }
                        else
                        {
                            result[57][2] += 100;
                        }
                    }
                    else
                    {
                        result[57][1] += 100;
                    }
                }
            }
        }
        else
        {
            result[57][2] += 100;
        }
    }
}
void tree58(int attr[4])
{
    if (attr[2] <= 485)
    {
        if (attr[2] <= 250)
        {
            result[58][0] += 100;
        }
        else
        {
            result[58][1] += 100;
        }
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[3] <= 175)
            {
                result[58][1] += 100;
            }
            else
            {
                result[58][2] += 100;
            }
        }
        else
        {
            result[58][2] += 100;
        }
    }
}
void tree59(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[59][0] += 100;
    }
    else
    {
        if (attr[3] <= 170)
        {
            if (attr[0] <= 710)
            {
                if (attr[1] <= 225)
                {
                    if (attr[2] <= 475)
                    {
                        result[59][1] += 100;
                    }
                    else
                    {
                        result[59][2] += 100;
                    }
                }
                else
                {
                    result[59][1] += 100;
                }
            }
            else
            {
                result[59][2] += 100;
            }
        }
        else
        {
            result[59][2] += 100;
        }
    }
}
void tree60(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[60][0] += 100;
    }
    else
    {
        if (attr[2] <= 485)
        {
            if (attr[0] <= 515)
            {
                if (attr[2] <= 390)
                {
                    result[60][1] += 100;
                }
                else
                {
                    result[60][2] += 100;
                }
            }
            else
            {
                result[60][1] += 100;
            }
        }
        else
        {
            if (attr[3] <= 165)
            {
                if (attr[1] <= 295)
                {
                    result[60][2] += 100;
                }
                else
                {
                    result[60][1] += 100;
                }
            }
            else
            {
                result[60][2] += 100;
            }
        }
    }
}
void tree61(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[61][0] += 100;
    }
    else
    {
        if (attr[3] <= 165)
        {
            if (attr[2] <= 500)
            {
                result[61][1] += 100;
            }
            else
            {
                result[61][2] += 100;
            }
        }
        else
        {
            if (attr[0] <= 595)
            {
                if (attr[0] <= 585)
                {
                    result[61][2] += 100;
                }
                else
                {
                    result[61][1] += 100;
                }
            }
            else
            {
                if (attr[0] <= 660)
                {
                    result[61][2] += 100;
                }
                else
                {
                    if (attr[1] <= 305)
                    {
                        if (attr[2] <= 510)
                        {
                            result[61][1] += 100;
                        }
                        else
                        {
                            result[61][2] += 100;
                        }
                    }
                    else
                    {
                        result[61][2] += 100;
                    }
                }
            }
        }
    }
}
void tree62(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[62][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 495)
            {
                if (attr[2] <= 445)
                {
                    result[62][1] += 100;
                }
                else
                {
                    if (attr[0] <= 545)
                    {
                        result[62][2] += 100;
                    }
                    else
                    {
                        result[62][1] += 100;
                    }
                }
            }
            else
            {
                if (attr[1] <= 245)
                {
                    result[62][2] += 100;
                }
                else
                {
                    if (attr[0] <= 615)
                    {
                        result[62][1] += 100;
                    }
                    else
                    {
                        if (attr[2] <= 505)
                        {
                            result[62][1] += 100;
                        }
                        else
                        {
                            result[62][2] += 100;
                        }
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 485)
            {
                if (attr[1] <= 310)
                {
                    result[62][2] += 100;
                }
                else
                {
                    result[62][1] += 100;
                }
            }
            else
            {
                result[62][2] += 100;
            }
        }
    }
}
void tree63(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[3] <= 80)
        {
            result[63][0] += 100;
        }
        else
        {
            if (attr[3] <= 160)
            {
                result[63][1] += 100;
            }
            else
            {
                result[63][2] += 100;
            }
        }
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[3] <= 70)
            {
                result[63][0] += 100;
            }
            else
            {
                if (attr[0] <= 710)
                {
                    if (attr[2] <= 495)
                    {
                        result[63][1] += 100;
                    }
                    else
                    {
                        if (attr[1] <= 260)
                        {
                            result[63][2] += 100;
                        }
                        else
                        {
                            result[63][1] += 100;
                        }
                    }
                }
                else
                {
                    result[63][2] += 100;
                }
            }
        }
        else
        {
            result[63][2] += 100;
        }
    }
}
void tree64(int attr[4])
{
    if (attr[0] <= 590)
    {
        if (attr[1] <= 290)
        {
            if (attr[0] <= 500)
            {
                result[64][2] += 100;
            }
            else
            {
                if (attr[2] <= 460)
                {
                    result[64][1] += 100;
                }
                else
                {
                    result[64][2] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 105)
            {
                result[64][0] += 100;
            }
            else
            {
                result[64][1] += 100;
            }
        }
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[0] <= 610)
            {
                result[64][2] += 100;
            }
            else
            {
                result[64][1] += 100;
            }
        }
        else
        {
            result[64][2] += 100;
        }
    }
}
void tree65(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[65][0] += 100;
    }
    else
    {
        if (attr[3] <= 165)
        {
            result[65][1] += 100;
        }
        else
        {
            result[65][2] += 100;
        }
    }
}
void tree66(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[2] <= 250)
        {
            result[66][0] += 100;
        }
        else
        {
            if (attr[2] <= 420)
            {
                result[66][1] += 100;
            }
            else
            {
                if (attr[3] <= 160)
                {
                    result[66][1] += 100;
                }
                else
                {
                    result[66][2] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[2] <= 240)
            {
                result[66][0] += 100;
            }
            else
            {
                if (attr[3] <= 170)
                {
                    result[66][1] += 100;
                }
                else
                {
                    if (attr[2] <= 485)
                    {
                        result[66][1] += 100;
                    }
                    else
                    {
                        result[66][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 515)
            {
                if (attr[0] <= 650)
                {
                    if (attr[1] <= 260)
                    {
                        result[66][2] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 595)
                        {
                            result[66][2] += 100;
                        }
                        else
                        {
                            if (attr[0] <= 615)
                            {
                                result[66][1] += 100;
                            }
                            else
                            {
                                result[66][2] += 100;
                            }
                        }
                    }
                }
                else
                {
                    if (attr[2] <= 505)
                    {
                        result[66][1] += 100;
                    }
                    else
                    {
                        result[66][2] += 100;
                    }
                }
            }
            else
            {
                result[66][2] += 100;
            }
        }
    }
}
void tree67(int attr[4])
{
    if (attr[2] <= 485)
    {
        if (attr[2] <= 235)
        {
            result[67][0] += 100;
        }
        else
        {
            if (attr[3] <= 165)
            {
                result[67][1] += 100;
            }
            else
            {
                if (attr[1] <= 285)
                {
                    result[67][2] += 100;
                }
                else
                {
                    result[67][1] += 100;
                }
            }
        }
    }
    else
    {
        if (attr[2] <= 515)
        {
            if (attr[3] <= 170)
            {
                if (attr[3] <= 155)
                {
                    if (attr[0] <= 645)
                    {
                        result[67][2] += 100;
                    }
                    else
                    {
                        result[67][1] += 100;
                    }
                }
                else
                {
                    result[67][1] += 100;
                }
            }
            else
            {
                result[67][2] += 100;
            }
        }
        else
        {
            result[67][2] += 100;
        }
    }
}
void tree68(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[68][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[0] <= 710)
            {
                if (attr[3] <= 145)
                {
                    result[68][1] += 100;
                }
                else
                {
                    if (attr[2] <= 505)
                    {
                        result[68][1] += 100;
                    }
                    else
                    {
                        result[68][2] += 100;
                    }
                }
            }
            else
            {
                result[68][2] += 100;
            }
        }
        else
        {
            result[68][2] += 100;
        }
    }
}
void tree69(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[3] <= 70)
        {
            result[69][0] += 100;
        }
        else
        {
            if (attr[0] <= 495)
            {
                if (attr[3] <= 135)
                {
                    result[69][1] += 100;
                }
                else
                {
                    result[69][2] += 100;
                }
            }
            else
            {
                result[69][1] += 100;
            }
        }
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 260)
            {
                result[69][0] += 100;
            }
            else
            {
                if (attr[2] <= 545)
                {
                    if (attr[3] <= 145)
                    {
                        result[69][1] += 100;
                    }
                    else
                    {
                        if (attr[2] <= 505)
                        {
                            result[69][1] += 100;
                        }
                        else
                        {
                            if (attr[1] <= 275)
                            {
                                result[69][1] += 100;
                            }
                            else
                            {
                                result[69][2] += 100;
                            }
                        }
                    }
                }
                else
                {
                    result[69][2] += 100;
                }
            }
        }
        else
        {
            result[69][2] += 100;
        }
    }
}
void tree70(int attr[4])
{
    if (attr[0] <= 585)
    {
        if (attr[1] <= 295)
        {
            if (attr[3] <= 165)
            {
                result[70][1] += 100;
            }
            else
            {
                result[70][2] += 100;
            }
        }
        else
        {
            if (attr[2] <= 290)
            {
                result[70][0] += 100;
            }
            else
            {
                result[70][1] += 100;
            }
        }
    }
    else
    {
        if (attr[3] <= 170)
        {
            if (attr[0] <= 635)
            {
                if (attr[0] <= 625)
                {
                    if (attr[2] <= 475)
                    {
                        result[70][1] += 100;
                    }
                    else
                    {
                        if (attr[3] <= 155)
                        {
                            result[70][2] += 100;
                        }
                        else
                        {
                            result[70][1] += 100;
                        }
                    }
                }
                else
                {
                    if (attr[1] <= 265)
                    {
                        result[70][1] += 100;
                    }
                    else
                    {
                        result[70][2] += 100;
                    }
                }
            }
            else
            {
                result[70][1] += 100;
            }
        }
        else
        {
            if (attr[0] <= 595)
            {
                if (attr[2] <= 495)
                {
                    result[70][1] += 100;
                }
                else
                {
                    result[70][2] += 100;
                }
            }
            else
            {
                result[70][2] += 100;
            }
        }
    }
}
void tree71(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[71][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[0] <= 495)
            {
                if (attr[2] <= 390)
                {
                    result[71][1] += 100;
                }
                else
                {
                    result[71][2] += 100;
                }
            }
            else
            {
                if (attr[0] <= 595)
                {
                    result[71][1] += 100;
                }
                else
                {
                    if (attr[3] <= 170)
                    {
                        result[71][1] += 100;
                    }
                    else
                    {
                        result[71][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 695)
                {
                    if (attr[3] <= 155)
                    {
                        result[71][2] += 100;
                    }
                    else
                    {
                        result[71][1] += 100;
                    }
                }
                else
                {
                    result[71][2] += 100;
                }
            }
            else
            {
                result[71][2] += 100;
            }
        }
    }
}
void tree72(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[72][0] += 100;
    }
    else
    {
        if (attr[3] <= 165)
        {
            if (attr[3] <= 145)
            {
                result[72][1] += 100;
            }
            else
            {
                if (attr[2] <= 495)
                {
                    result[72][1] += 100;
                }
                else
                {
                    result[72][2] += 100;
                }
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[1] <= 285)
                {
                    result[72][2] += 100;
                }
                else
                {
                    result[72][1] += 100;
                }
            }
            else
            {
                result[72][2] += 100;
            }
        }
    }
}
void tree73(int attr[4])
{
    if (attr[3] <= 70)
    {
        result[73][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[3] <= 165)
            {
                result[73][1] += 100;
            }
            else
            {
                if (attr[1] <= 275)
                {
                    result[73][2] += 100;
                }
                else
                {
                    result[73][1] += 100;
                }
            }
        }
        else
        {
            result[73][2] += 100;
        }
    }
}
void tree74(int attr[4])
{
    if (attr[3] <= 175)
    {
        if (attr[2] <= 270)
        {
            result[74][0] += 100;
        }
        else
        {
            result[74][1] += 100;
        }
    }
    else
    {
        result[74][2] += 100;
    }
}
void tree75(int attr[4])
{
    if (attr[0] <= 575)
    {
        if (attr[3] <= 80)
        {
            result[75][0] += 100;
        }
        else
        {
            result[75][1] += 100;
        }
    }
    else
    {
        if (attr[0] <= 705)
        {
            if (attr[2] <= 505)
            {
                if (attr[2] <= 475)
                {
                    result[75][1] += 100;
                }
                else
                {
                    if (attr[0] <= 650)
                    {
                        if (attr[3] <= 165)
                        {
                            result[75][1] += 100;
                        }
                        else
                        {
                            if (attr[0] <= 595)
                            {
                                result[75][1] += 100;
                            }
                            else
                            {
                                result[75][2] += 100;
                            }
                        }
                    }
                    else
                    {
                        result[75][1] += 100;
                    }
                }
            }
            else
            {
                if (attr[0] <= 610)
                {
                    if (attr[3] <= 170)
                    {
                        result[75][1] += 100;
                    }
                    else
                    {
                        result[75][2] += 100;
                    }
                }
                else
                {
                    result[75][2] += 100;
                }
            }
        }
        else
        {
            result[75][2] += 100;
        }
    }
}
void tree76(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[76][0] += 100;
    }
    else
    {
        if (attr[0] <= 620)
        {
            if (attr[2] <= 485)
            {
                if (attr[3] <= 165)
                {
                    result[76][1] += 100;
                }
                else
                {
                    if (attr[1] <= 310)
                    {
                        result[76][2] += 100;
                    }
                    else
                    {
                        result[76][1] += 100;
                    }
                }
            }
            else
            {
                if (attr[0] <= 590)
                {
                    result[76][2] += 100;
                }
                else
                {
                    if (attr[0] <= 605)
                    {
                        result[76][1] += 100;
                    }
                    else
                    {
                        result[76][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[2] <= 495)
                {
                    result[76][1] += 100;
                }
                else
                {
                    if (attr[0] <= 650)
                    {
                        result[76][2] += 100;
                    }
                    else
                    {
                        result[76][1] += 100;
                    }
                }
            }
            else
            {
                result[76][2] += 100;
            }
        }
    }
}
void tree77(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[77][0] += 100;
    }
    else
    {
        if (attr[0] <= 615)
        {
            if (attr[2] <= 495)
            {
                result[77][1] += 100;
            }
            else
            {
                result[77][2] += 100;
            }
        }
        else
        {
            if (attr[2] <= 480)
            {
                result[77][1] += 100;
            }
            else
            {
                if (attr[3] <= 175)
                {
                    if (attr[2] <= 505)
                    {
                        result[77][1] += 100;
                    }
                    else
                    {
                        result[77][2] += 100;
                    }
                }
                else
                {
                    result[77][2] += 100;
                }
            }
        }
    }
}
void tree78(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[2] <= 235)
        {
            result[78][0] += 100;
        }
        else
        {
            if (attr[3] <= 160)
            {
                result[78][1] += 100;
            }
            else
            {
                result[78][2] += 100;
            }
        }
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 260)
            {
                result[78][0] += 100;
            }
            else
            {
                if (attr[1] <= 225)
                {
                    if (attr[2] <= 475)
                    {
                        result[78][1] += 100;
                    }
                    else
                    {
                        result[78][2] += 100;
                    }
                }
                else
                {
                    if (attr[3] <= 145)
                    {
                        result[78][1] += 100;
                    }
                    else
                    {
                        if (attr[1] <= 290)
                        {
                            if (attr[1] <= 265)
                            {
                                result[78][1] += 100;
                            }
                            else
                            {
                                result[78][2] += 100;
                            }
                        }
                        else
                        {
                            result[78][1] += 100;
                        }
                    }
                }
            }
        }
        else
        {
            result[78][2] += 100;
        }
    }
}
void tree79(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[79][0] += 100;
    }
    else
    {
        if (attr[2] <= 470)
        {
            result[79][1] += 100;
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[2] <= 545)
                {
                    if (attr[0] <= 650)
                    {
                        if (attr[3] <= 155)
                        {
                            if (attr[1] <= 235)
                            {
                                result[79][2] += 100;
                            }
                            else
                            {
                                if (attr[2] <= 500)
                                {
                                    result[79][1] += 100;
                                }
                                else
                                {
                                    result[79][2] += 100;
                                }
                            }
                        }
                        else
                        {
                            result[79][1] += 100;
                        }
                    }
                    else
                    {
                        result[79][1] += 100;
                    }
                }
                else
                {
                    result[79][2] += 100;
                }
            }
            else
            {
                result[79][2] += 100;
            }
        }
    }
}
void tree80(int attr[4])
{
    if (attr[0] <= 545)
    {
        if (attr[2] <= 235)
        {
            result[80][0] += 100;
        }
        else
        {
            result[80][1] += 100;
        }
    }
    else
    {
        if (attr[3] <= 170)
        {
            if (attr[3] <= 70)
            {
                result[80][0] += 100;
            }
            else
            {
                result[80][1] += 100;
            }
        }
        else
        {
            result[80][2] += 100;
        }
    }
}
void tree81(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[81][0] += 100;
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[2] <= 475)
            {
                if (attr[3] <= 165)
                {
                    result[81][1] += 100;
                }
                else
                {
                    result[81][2] += 100;
                }
            }
            else
            {
                if (attr[1] <= 305)
                {
                    result[81][2] += 100;
                }
                else
                {
                    result[81][1] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[3] <= 165)
                {
                    if (attr[2] <= 505)
                    {
                        result[81][2] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 660)
                        {
                            result[81][1] += 100;
                        }
                        else
                        {
                            result[81][2] += 100;
                        }
                    }
                }
                else
                {
                    result[81][1] += 100;
                }
            }
            else
            {
                result[81][2] += 100;
            }
        }
    }
}
void tree82(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[82][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 485)
            {
                result[82][1] += 100;
            }
            else
            {
                if (attr[3] <= 155)
                {
                    result[82][2] += 100;
                }
                else
                {
                    if (attr[0] <= 695)
                    {
                        result[82][1] += 100;
                    }
                    else
                    {
                        result[82][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[0] <= 600)
            {
                if (attr[1] <= 310)
                {
                    result[82][2] += 100;
                }
                else
                {
                    result[82][1] += 100;
                }
            }
            else
            {
                result[82][2] += 100;
            }
        }
    }
}
void tree83(int attr[4])
{
    if (attr[2] <= 250)
    {
        result[83][0] += 100;
    }
    else
    {
        if (attr[2] <= 485)
        {
            if (attr[2] <= 475)
            {
                if (attr[3] <= 165)
                {
                    result[83][1] += 100;
                }
                else
                {
                    result[83][2] += 100;
                }
            }
            else
            {
                if (attr[1] <= 310)
                {
                    result[83][2] += 100;
                }
                else
                {
                    result[83][1] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[2] <= 505)
                {
                    result[83][1] += 100;
                }
                else
                {
                    result[83][2] += 100;
                }
            }
            else
            {
                result[83][2] += 100;
            }
        }
    }
}
void tree84(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[84][0] += 100;
    }
    else
    {
        if (attr[3] <= 170)
        {
            if (attr[2] <= 500)
            {
                result[84][1] += 100;
            }
            else
            {
                if (attr[3] <= 155)
                {
                    result[84][2] += 100;
                }
                else
                {
                    result[84][1] += 100;
                }
            }
        }
        else
        {
            if (attr[2] <= 485)
            {
                if (attr[1] <= 310)
                {
                    result[84][2] += 100;
                }
                else
                {
                    result[84][1] += 100;
                }
            }
            else
            {
                result[84][2] += 100;
            }
        }
    }
}
void tree85(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[85][0] += 100;
    }
    else
    {
        if (attr[0] <= 635)
        {
            if (attr[3] <= 165)
            {
                if (attr[2] <= 495)
                {
                    result[85][1] += 100;
                }
                else
                {
                    result[85][2] += 100;
                }
            }
            else
            {
                if (attr[1] <= 310)
                {
                    result[85][2] += 100;
                }
                else
                {
                    if (attr[1] <= 330)
                    {
                        result[85][1] += 100;
                    }
                    else
                    {
                        result[85][2] += 100;
                    }
                }
            }
        }
        else
        {
            if (attr[3] <= 160)
            {
                result[85][1] += 100;
            }
            else
            {
                result[85][2] += 100;
            }
        }
    }
}
void tree86(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[86][0] += 100;
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 495)
                {
                    if (attr[2] <= 390)
                    {
                        result[86][1] += 100;
                    }
                    else
                    {
                        result[86][2] += 100;
                    }
                }
                else
                {
                    result[86][1] += 100;
                }
            }
            else
            {
                result[86][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 170)
            {
                if (attr[0] <= 615)
                {
                    result[86][1] += 100;
                }
                else
                {
                    result[86][2] += 100;
                }
            }
            else
            {
                result[86][2] += 100;
            }
        }
    }
}
void tree87(int attr[4])
{
    if (attr[2] <= 475)
    {
        if (attr[2] <= 235)
        {
            result[87][0] += 100;
        }
        else
        {
            result[87][1] += 100;
        }
    }
    else
    {
        if (attr[2] <= 495)
        {
            if (attr[1] <= 305)
            {
                result[87][2] += 100;
            }
            else
            {
                result[87][1] += 100;
            }
        }
        else
        {
            if (attr[3] <= 170)
            {
                if (attr[3] <= 155)
                {
                    result[87][2] += 100;
                }
                else
                {
                    if (attr[1] <= 285)
                    {
                        result[87][1] += 100;
                    }
                    else
                    {
                        result[87][2] += 100;
                    }
                }
            }
            else
            {
                result[87][2] += 100;
            }
        }
    }
}
void tree88(int attr[4])
{
    if (attr[2] <= 475)
    {
        if (attr[2] <= 250)
        {
            result[88][0] += 100;
        }
        else
        {
            result[88][1] += 100;
        }
    }
    else
    {
        if (attr[2] <= 485)
        {
            if (attr[0] <= 595)
            {
                result[88][1] += 100;
            }
            else
            {
                result[88][2] += 100;
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[0] <= 650)
                {
                    result[88][2] += 100;
                }
                else
                {
                    if (attr[2] <= 540)
                    {
                        result[88][1] += 100;
                    }
                    else
                    {
                        result[88][2] += 100;
                    }
                }
            }
            else
            {
                result[88][2] += 100;
            }
        }
    }
}
void tree89(int attr[4])
{
    if (attr[2] <= 475)
    {
        if (attr[3] <= 80)
        {
            result[89][0] += 100;
        }
        else
        {
            result[89][1] += 100;
        }
    }
    else
    {
        if (attr[3] <= 155)
        {
            if (attr[0] <= 660)
            {
                result[89][2] += 100;
            }
            else
            {
                result[89][1] += 100;
            }
        }
        else
        {
            result[89][2] += 100;
        }
    }
}
void tree90(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[90][0] += 100;
    }
    else
    {
        if (attr[3] <= 155)
        {
            result[90][1] += 100;
        }
        else
        {
            if (attr[3] <= 185)
            {
                if (attr[1] <= 310)
                {
                    if (attr[2] <= 500)
                    {
                        result[90][2] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 660)
                        {
                            result[90][1] += 100;
                        }
                        else
                        {
                            result[90][2] += 100;
                        }
                    }
                }
                else
                {
                    result[90][1] += 100;
                }
            }
            else
            {
                result[90][2] += 100;
            }
        }
    }
}
void tree91(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[91][0] += 100;
    }
    else
    {
        if (attr[2] <= 505)
        {
            if (attr[2] <= 485)
            {
                if (attr[0] <= 495)
                {
                    if (attr[1] <= 245)
                    {
                        result[91][1] += 100;
                    }
                    else
                    {
                        result[91][2] += 100;
                    }
                }
                else
                {
                    result[91][1] += 100;
                }
            }
            else
            {
                if (attr[3] <= 175)
                {
                    result[91][1] += 100;
                }
                else
                {
                    result[91][2] += 100;
                }
            }
        }
        else
        {
            result[91][2] += 100;
        }
    }
}
void tree92(int attr[4])
{
    if (attr[3] <= 155)
    {
        if (attr[0] <= 545)
        {
            if (attr[2] <= 260)
            {
                result[92][0] += 100;
            }
            else
            {
                result[92][1] += 100;
            }
        }
        else
        {
            if (attr[3] <= 70)
            {
                result[92][0] += 100;
            }
            else
            {
                result[92][1] += 100;
            }
        }
    }
    else
    {
        if (attr[2] <= 485)
        {
            if (attr[0] <= 615)
            {
                if (attr[1] <= 310)
                {
                    result[92][2] += 100;
                }
                else
                {
                    result[92][1] += 100;
                }
            }
            else
            {
                result[92][1] += 100;
            }
        }
        else
        {
            result[92][2] += 100;
        }
    }
}
void tree93(int attr[4])
{
    if (attr[3] <= 75)
    {
        result[93][0] += 100;
    }
    else
    {
        if (attr[3] <= 155)
        {
            if (attr[3] <= 145)
            {
                result[93][1] += 100;
            }
            else
            {
                if (attr[1] <= 290)
                {
                    result[93][2] += 100;
                }
                else
                {
                    result[93][1] += 100;
                }
            }
        }
        else
        {
            if (attr[0] <= 610)
            {
                if (attr[2] <= 490)
                {
                    if (attr[0] <= 540)
                    {
                        result[93][2] += 100;
                    }
                    else
                    {
                        if (attr[0] <= 595)
                        {
                            result[93][1] += 100;
                        }
                        else
                        {
                            if (attr[2] <= 465)
                            {
                                result[93][1] += 100;
                            }
                            else
                            {
                                result[93][2] += 100;
                            }
                        }
                    }
                }
                else
                {
                    result[93][2] += 100;
                }
            }
            else
            {
                result[93][2] += 100;
            }
        }
    }
}
void tree94(int attr[4])
{
    if (attr[2] <= 250)
    {
        result[94][0] += 100;
    }
    else
    {
        if (attr[3] <= 155)
        {
            if (attr[3] <= 145)
            {
                result[94][1] += 100;
            }
            else
            {
                if (attr[2] <= 500)
                {
                    result[94][1] += 100;
                }
                else
                {
                    result[94][2] += 100;
                }
            }
        }
        else
        {
            if (attr[3] <= 175)
            {
                if (attr[2] <= 545)
                {
                    if (attr[0] <= 545)
                    {
                        result[94][2] += 100;
                    }
                    else
                    {
                        result[94][1] += 100;
                    }
                }
                else
                {
                    result[94][2] += 100;
                }
            }
            else
            {
                if (attr[2] <= 485)
                {
                    if (attr[1] <= 310)
                    {
                        result[94][2] += 100;
                    }
                    else
                    {
                        result[94][1] += 100;
                    }
                }
                else
                {
                    result[94][2] += 100;
                }
            }
        }
    }
}
void tree95(int attr[4])
{
    if (attr[3] <= 170)
    {
        if (attr[0] <= 535)
        {
            if (attr[3] <= 75)
            {
                result[95][0] += 100;
            }
            else
            {
                result[95][1] += 100;
            }
        }
        else
        {
            if (attr[3] <= 70)
            {
                result[95][0] += 100;
            }
            else
            {
                if (attr[2] <= 545)
                {
                    result[95][1] += 100;
                }
                else
                {
                    result[95][2] += 100;
                }
            }
        }
    }
    else
    {
        result[95][2] += 100;
    }
}
void tree96(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[96][0] += 100;
    }
    else
    {
        if (attr[2] <= 475)
        {
            if (attr[0] <= 500)
            {
                result[96][2] += 100;
            }
            else
            {
                result[96][1] += 100;
            }
        }
        else
        {
            if (attr[2] <= 495)
            {
                if (attr[1] <= 305)
                {
                    if (attr[1] <= 260)
                    {
                        result[96][1] += 100;
                    }
                    else
                    {
                        result[96][2] += 100;
                    }
                }
                else
                {
                    result[96][1] += 100;
                }
            }
            else
            {
                result[96][2] += 100;
            }
        }
    }
}
void tree97(int attr[4])
{
    if (attr[2] <= 235)
    {
        result[97][0] += 100;
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[2] <= 505)
            {
                result[97][1] += 100;
            }
            else
            {
                result[97][2] += 100;
            }
        }
        else
        {
            if (attr[0] <= 600)
            {
                if (attr[2] <= 490)
                {
                    result[97][1] += 100;
                }
                else
                {
                    result[97][2] += 100;
                }
            }
            else
            {
                result[97][2] += 100;
            }
        }
    }
}
void tree98(int attr[4])
{
    if (attr[3] <= 80)
    {
        result[98][0] += 100;
    }
    else
    {
        if (attr[0] <= 625)
        {
            if (attr[3] <= 185)
            {
                if (attr[3] <= 160)
                {
                    result[98][1] += 100;
                }
                else
                {
                    if (attr[1] <= 285)
                    {
                        result[98][2] += 100;
                    }
                    else
                    {
                        result[98][1] += 100;
                    }
                }
            }
            else
            {
                result[98][2] += 100;
            }
        }
        else
        {
            if (attr[2] <= 505)
            {
                if (attr[2] <= 495)
                {
                    result[98][1] += 100;
                }
                else
                {
                    if (attr[3] <= 180)
                    {
                        result[98][1] += 100;
                    }
                    else
                    {
                        result[98][2] += 100;
                    }
                }
            }
            else
            {
                result[98][2] += 100;
            }
        }
    }
}
void tree99(int attr[4])
{
    if (attr[2] <= 475)
    {
        if (attr[3] <= 70)
        {
            result[99][0] += 100;
        }
        else
        {
            if (attr[0] <= 500)
            {
                if (attr[1] <= 245)
                {
                    result[99][1] += 100;
                }
                else
                {
                    result[99][2] += 100;
                }
            }
            else
            {
                result[99][1] += 100;
            }
        }
    }
    else
    {
        if (attr[3] <= 175)
        {
            if (attr[1] <= 245)
            {
                result[99][2] += 100;
            }
            else
            {
                if (attr[1] <= 275)
                {
                    result[99][1] += 100;
                }
                else
                {
                    if (attr[0] <= 650)
                    {
                        result[99][2] += 100;
                    }
                    else
                    {
                        result[99][1] += 100;
                    }
                }
            }
        }
        else
        {
            result[99][2] += 100;
        }
    }
}
int voting()
{
    for (int t = 0; t < 100; t++)
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
    for (int t = 0; t < 100; t++)
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
    tree1(attr);
    tree2(attr);
    tree3(attr);
    tree4(attr);
    tree5(attr);
    tree6(attr);
    tree7(attr);
    tree8(attr);
    tree9(attr);
    tree10(attr);
    tree11(attr);
    tree12(attr);
    tree13(attr);
    tree14(attr);
    tree15(attr);
    tree16(attr);
    tree17(attr);
    tree18(attr);
    tree19(attr);
    tree20(attr);
    tree21(attr);
    tree22(attr);
    tree23(attr);
    tree24(attr);
    tree25(attr);
    tree26(attr);
    tree27(attr);
    tree28(attr);
    tree29(attr);
    tree30(attr);
    tree31(attr);
    tree32(attr);
    tree33(attr);
    tree34(attr);
    tree35(attr);
    tree36(attr);
    tree37(attr);
    tree38(attr);
    tree39(attr);
    tree40(attr);
    tree41(attr);
    tree42(attr);
    tree43(attr);
    tree44(attr);
    tree45(attr);
    tree46(attr);
    tree47(attr);
    tree48(attr);
    tree49(attr);
    tree50(attr);
    tree51(attr);
    tree52(attr);
    tree53(attr);
    tree54(attr);
    tree55(attr);
    tree56(attr);
    tree57(attr);
    tree58(attr);
    tree59(attr);
    tree60(attr);
    tree61(attr);
    tree62(attr);
    tree63(attr);
    tree64(attr);
    tree65(attr);
    tree66(attr);
    tree67(attr);
    tree68(attr);
    tree69(attr);
    tree70(attr);
    tree71(attr);
    tree72(attr);
    tree73(attr);
    tree74(attr);
    tree75(attr);
    tree76(attr);
    tree77(attr);
    tree78(attr);
    tree79(attr);
    tree80(attr);
    tree81(attr);
    tree82(attr);
    tree83(attr);
    tree84(attr);
    tree85(attr);
    tree86(attr);
    tree87(attr);
    tree88(attr);
    tree89(attr);
    tree90(attr);
    tree91(attr);
    tree92(attr);
    tree93(attr);
    tree94(attr);
    tree95(attr);
    tree96(attr);
    tree97(attr);
    tree98(attr);
    tree99(attr);
    return voting();
}
}  // namespace VIVADO100
