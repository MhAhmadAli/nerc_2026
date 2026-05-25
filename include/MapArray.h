#ifndef _MAPARRAY_H_
#define _MAPARRAY_H_

#include <Arduino.h>

const uint8_t MAP_PINS[3][3] = {{30, 36, 34},
                                {42, 38, 40},
                                {48, 44, 46}};

void initMapArray()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            pinMode(MAP_PINS[i][j], INPUT);
        }
    }
}

void readMapSingleSensor(uint8_t sensor)
{
    Serial.println(digitalRead(sensor));
}

void checkMap()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Serial.print(digitalRead(MAP_PINS[i][j]));
            Serial.print(" ");
        }
        Serial.println("");
    }

    Serial.println("\n\n");
}

uint8_t readMapBlue()
{
    int map[3][3] = {0};
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // white -> 1
            // black -> 0
            bool isBlack = digitalRead(MAP_PINS[i][j]) ? 0 : 1;
            map[i][j] = isBlack;
            if (isBlack)
                count++;
        }
    }

    // swap first and third column
    int temp = map[0][0];
    map[0][0] = map[0][2];
    map[0][2] = temp;

    temp = map[1][0];
    map[1][0] = map[1][2];
    map[1][2] = temp;

    temp = map[2][0];
    map[2][0] = map[2][2];
    map[2][2] = temp;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Serial.print(map[i][j]);
            Serial.print(" ");
        }
        Serial.println();
    }
    Serial.println();

    if (count < 3)
    {
        return 0;
    }
    else if (count > 3)
    {
        return 0;
    }

    if (map[0][0] && map[1][1] && map[2][2])
    {
        // 0 0 1
        // 0 1 0
        // 1 0 0
        return 1;
    }
    else if (map[0][0] && map[0][1] && map[0][2])
    {
        // 1 1 1
        // 0 0 0
        // 0 0 0
        return 2;
    }
    else if (map[1][0] && map[1][1] && map[1][2])
    {
        // 0 0 0
        // 1 1 1
        // 0 0 0
        return 3;
    }
    else if (map[0][1] && map[1][1] && map[1][0])
    {
        // 0 1 0
        // 0 1 1
        // 0 0 0
        return 4;
    }
    else if (map[0][1] && map[1][1] && map[1][2])
    {
        // 0 1 0
        // 1 1 0
        // 0 0 0
        return 5;
    }
    else if (map[0][1] && map[2][0] && map[2][2])
    {
        // 0 1 0
        // 0 0 0
        // 1 0 1
        return 6;
    }
    else if (map[0][0] && map[0][2] && map[2][1])
    {
        // 1 0 1
        // 0 0 0
        // 0 1 0
        return 7;
    }
    else if (map[0][2] && map[1][1] && map[2][0])
    {
        // 1 0 0
        // 0 1 0
        // 0 0 1
        return 8;
    }
    else if (map[0][1] && map[1][0] && map[1][2])
    {
        // 0 1 0
        // 1 0 1
        // 0 0 0
        return 9;
    }
    else if (map[1][1] && map[2][0] && map[2][2])
    {
        // 0 0 0
        // 0 1 0
        // 1 0 1
        return 10;
    }
    else if (map[0][0] && map[0][2] && map[2][0])
    {
        // 1 0 1
        // 0 0 0
        // 0 0 1
        return 11;
    }
    else if (map[0][2] && map[2][0] && map[2][2])
    {
        // 1 0 0
        // 0 0 0
        // 1 0 1
        return 12;
    }
    else if (map[0][1] && map[1][1] && map[2][0])
    {
        // 0 1 0
        // 0 1 0
        // 0 0 1
        return 13;
    }
    else if (map[0][1] && map[1][1] && map[2][2])
    {
        // 0 1 0
        // 0 1 0
        // 1 0 0
        return 14;
    }
    else if (map[0][2] && map[1][0] && map[2][2])
    {
        // 1 0 0
        // 0 0 1
        // 1 0 0
        return 15;
    }
    else if (map[0][0] && map[1][2] && map[2][0])
    {
        // 0 0 1
        // 1 0 0
        // 0 0 1
        return 16;
    }
    else if (map[0][0] && map[1][1] && map[2][0])
    {
        // 0 0 1
        // 0 1 0
        // 0 0 1
        return 17;
    }
    else if (map[0][2] && map[1][1] && map[2][2])
    {
        // 1 0 0
        // 0 1 0
        // 1 0 0
        return 18;
    }
    else if (map[0][0] && map[1][1] && map[2][1])
    {
        // 0 0 1
        // 0 1 0
        // 0 1 0
        return 19;
    }
    else if (map[0][2] && map[1][1] && map[2][1])
    {
        // 1 0 0
        // 0 1 0
        // 0 1 0
        return 20;
    }
    else
    {
        return 0;
    }
}

uint8_t readMapRed()
{
    int map[3][3] = {0};
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 2; j >= 0; j--)
        {
            // white -> 1
            // black -> 0
            bool isBlack = digitalRead(MAP_PINS[i][j]) ? 0 : 1;
            map[i][j] = isBlack;
            if (isBlack)
                count++;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Serial.print(map[i][j]);
            Serial.print(" ");
        }
        Serial.println();
    }
    Serial.println();

    if (count < 3)
    {
        return 0;
    }
    else if (count > 3)
    {
        return 0;
    }

    if (map[0][0] && map[1][1] && map[2][2])
    {
        // 0 0 1
        // 0 1 0
        // 1 0 0
        return 1;
    }
    else if (map[0][0] && map[0][1] && map[0][2])
    {
        // 1 1 1
        // 0 0 0
        // 0 0 0
        return 2;
    }
    else if (map[1][0] && map[1][1] && map[1][2])
    {
        // 0 0 0
        // 1 1 1
        // 0 0 0
        return 3;
    }
    else if (map[0][1] && map[1][1] && map[1][0])
    {
        // 0 1 0
        // 0 1 1
        // 0 0 0
        return 4;
    }
    else if (map[0][1] && map[1][1] && map[1][2])
    {
        // 0 1 0
        // 1 1 0
        // 0 0 0
        return 5;
    }
    else if (map[0][1] && map[2][0] && map[2][2])
    {
        // 0 1 0
        // 0 0 0
        // 1 0 1
        return 6;
    }
    else if (map[0][0] && map[0][2] && map[2][1])
    {
        // 1 0 1
        // 0 0 0
        // 0 1 0
        return 7;
    }
    else if (map[0][2] && map[1][1] && map[2][0])
    {
        // 1 0 0
        // 0 1 0
        // 0 0 1
        return 8;
    }
    else if (map[0][1] && map[1][0] && map[1][2])
    {
        // 0 1 0
        // 1 0 1
        // 0 0 0
        return 9;
    }
    else if (map[1][1] && map[2][0] && map[2][2])
    {
        // 0 0 0
        // 0 1 0
        // 1 0 1
        return 10;
    }
    else if (map[0][0] && map[0][2] && map[2][0])
    {
        // 1 0 1
        // 0 0 0
        // 0 0 1
        return 11;
    }
    else if (map[0][2] && map[2][0] && map[2][2])
    {
        // 1 0 0
        // 0 0 0
        // 1 0 1
        return 12;
    }
    else if (map[0][1] && map[1][1] && map[2][0])
    {
        // 0 1 0
        // 0 1 0
        // 0 0 1
        return 13;
    }
    else if (map[0][1] && map[1][1] && map[2][2])
    {
        // 0 1 0
        // 0 1 0
        // 1 0 0
        return 14;
    }
    else if (map[0][2] && map[1][0] && map[2][2])
    {
        // 1 0 0
        // 0 0 1
        // 1 0 0
        return 15;
    }
    else if (map[0][0] && map[1][2] && map[2][0])
    {
        // 0 0 1
        // 1 0 0
        // 0 0 1
        return 16;
    }
    else if (map[0][0] && map[1][1] && map[2][0])
    {
        // 0 0 1
        // 0 1 0
        // 0 0 1
        return 17;
    }
    else if (map[0][2] && map[1][1] && map[2][2])
    {
        // 1 0 0
        // 0 1 0
        // 1 0 0
        return 18;
    }
    else if (map[0][0] && map[1][1] && map[2][1])
    {
        // 0 0 1
        // 0 1 0
        // 0 1 0
        return 19;
    }
    else if (map[0][2] && map[1][1] && map[2][1])
    {
        // 1 0 0
        // 0 1 0
        // 0 1 0
        return 20;
    }
    else
    {
        return 0;
    }
}

#endif //_MAPARRAY_H_