#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <malloc.h>
#include <queue>
#include <locale>
#include "interface_races_classes_background.h"
#include "character.cpp"
#include "Race_Class_Background.cpp"



using namespace std;

int main() {
    setlocale(LC_ALL,"rus");
    printf("%s","Dungeons and Dragons game (PC) starts here");

    return 0;
}
/*
 * 1. персонажи
 * 2. mobs and experience
 * 3. случайные события и инициатива
 * 4. очередь хода
 * 5. поле
 * 6. карта
 * 7. умное поведение мобов в бою
 * 8. в процесе...
 * 9. в процесе...
 */