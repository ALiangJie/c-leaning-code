#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<math.h>
#include<windows.h>
#include<tchar.h>
#include<stdio.h>
#include<stdlib.h>
/// <summary>
/// 球
/// </summary>
void drawBall()
{
    float x, y;
    for (y = 1; y >= -1; y -= 0.05f, putchar('\n'))
        for (x = -1; x <= 1; x += 0.025f)
            putchar(x * x + y * y > 1 ? 'M' : "@@%#*+=;:. "[(int)(
                ((x + y + sqrt(1 - (x * x + y * y))) * 0.5773502692f + 1)
                * 5.0f + 0.5f)]);
}

/// <summary>
/// 心形1
/// </summary>
void drawHeart1()
{
    for (float y = 1.5f; y > -1.5f; y -= 0.1f) {
        for (float x = -1.5f; x < 1.5f; x += 0.05f) {
            float a = x * x + y * y - 1;
            putchar(a * a * a - x * x * y * y * y <= 0.0f ? '*' : ' ');
        }
        putchar('\n');
    }
}

/// <summary>
/// 心形2
/// </summary>
void drawHeart2()
{
    for (float y = 1.5f; y > -1.5f; y -= 0.1f) {
        for (float x = -1.5f; x < 1.5f; x += 0.05f) {
            float z = x * x + y * y - 1;
            float f = z * z * z - x * x * y * y * y;
            putchar(f <= 0.0f ? ".:-=+*#%@"[(int)(f * -8.0f)] : ' ');
        }
        putchar('\n');
    }
}

float f(float x, float y, float z) {
    float a = x * x + 9.0f / 4.0f * y * y + z * z - 1;
    return a * a * a - x * x * z * z * z - 9.0f / 80.0f * y * y * z * z * z;
}

float h(float x, float z) {
    for (float y = 1.0f; y >= 0.0f; y -= 0.001f)
        if (f(x, y, z) <= 0.0f)
            return y;
    return 0.0f;
}
/// <summary>
/// 心形3
/// </summary>
void drawHeart3()
{

    for (float z = 1.5f; z > -1.5f; z -= 0.05f) {
        for (float x = -1.5f; x < 1.5f; x += 0.025f) {
            float v = f(x, 0.0f, z);
            if (v <= 0.0f) {
                float y0 = h(x, z);
                float ny = 0.01f;
                float nx = h(x + ny, z) - y0;
                float nz = h(x, z + ny) - y0;
                float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
                float d = (nx + ny - nz) * nd * 0.5f + 0.5f;
                putchar(".:-=+*#%@"[(int)(d * 5.0f)]);
            }
            else
                putchar(' ');
        }
        putchar('\n');
    }
}

/// <summary>
/// 心形4
/// </summary>
void drawHeart4()
{
    FILE* fp = fopen("heart.ppm", "w");
    int sw = 512, sh = 512;
    fprintf(fp, "P3\n%d %d\n255\n", sw, sh);
    for (int sy = 0; sy < sh; sy++) {
        float z = 1.5f - sy * 3.0f / sh;
        for (int sx = 0; sx < sw; sx++) {
            float x = sx * 3.0f / sw - 1.5f;
            float v = f(x, 0.0f, z);
            int r = 0;
            if (v <= 0.0f) {
                float y0 = h(x, z);
                float ny = 0.001f;
                float nx = h(x + ny, z) - y0;
                float nz = h(x, z + ny) - y0;
                float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
                float d = (nx + ny - nz) / sqrtf(3) * nd * 0.5f + 0.5f;
                r = (int)(d * 255.0f);
            }
            fprintf(fp, "%d 0 0 ", r);
        }
        fputc('\n', fp);
    }
    fclose(fp);
}

/// <summary>
/// 心形5
/// </summary>
void drawHeart5()
{
    HANDLE o = GetStdHandle(STD_OUTPUT_HANDLE);
    _TCHAR buffer[25][80] = { _T(' ') };
    _TCHAR ramp[] = _T(".:-=+*#%@");

    for (float t = 0.0f;; t += 0.1f) {
        int sy = 0;
        float s = sinf(t);
        float a = s * s * s * s * 0.2f;
        for (float z = 1.3f; z > -1.2f; z -= 0.1f) {
            _TCHAR* p = &buffer[sy++][0];
            float tz = z * (1.2f - a);
            for (float x = -1.5f; x < 1.5f; x += 0.05f) {
                float tx = x * (1.2f + a);
                float v = f(tx, 0.0f, tz);
                if (v <= 0.0f) {
                    float y0 = h(tx, tz);
                    float ny = 0.01f;
                    float nx = h(tx + ny, tz) - y0;
                    float nz = h(tx, tz + ny) - y0;
                    float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
                    float d = (nx + ny - nz) * nd * 0.5f + 0.5f;
                    *p++ = ramp[(int)(d * 5.0f)];
                }
                else
                    *p++ = ' ';
            }
        }

        for (sy = 0; sy < 25; sy++) {
            COORD coord = { 0, sy };
            SetConsoleCursorPosition(o, coord);
            WriteConsole(o, buffer[sy], 79, NULL, 0);
        }
        Sleep(33);
    }
}

void drawSnow()
{

}
