#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int mbcompare(const char* pStr, int index, const char* pMatch)
{
    mbstate_t mbs = { 0 };
    int len = 0;
    int i = 0;

    const char* pEnd = pStr + strlen(pStr);
    mbrlen(NULL, 0, &mbs);

    while ((len = mbrlen(pStr, pEnd - pStr, &mbs)) > 0)
    {
        if (i == index) {
            return strncmp(pStr, pMatch, len) == 0;
        }
        pStr += len;
        i++;
    }
    return 0;
}

void mbprint(const char* pStr)
{
    mbstate_t mbs = { 0 };
    int len = 0;
    int i = 0;
    char buf[6];

    const char* pEnd = pStr + strlen(pStr);
    mbrlen(NULL, 0, &mbs);

    while ((len = mbrlen(pStr, pEnd - pStr, &mbs)) > 0)
    {

        strncpy_s(buf, sizeof(buf), pStr, len);
        printf(u8"%2d: %s (%d байт)\n", i, buf, len);

        pStr += len;
        i++;
    }
}

int main()
{
    setlocale(LC_ALL, "ru_RU.utf8");

    char str[] = u8"Привет Мир!";
    mbprint(str);

    if (mbcompare(str, 1, u8"р")) printf(u8"Символ 1 == [р]\n");
    else printf(u8"Символ 1 != [р]\n");

    getchar();
}