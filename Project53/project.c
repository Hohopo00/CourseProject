#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "project.h"

char* getLicense(int license) {
    switch (license) {
    case LIC_MIT: return "MIT";
    case LIC_APACHE: return "Apache";
    case LIC_GPL: return "GPL";
    case LIC_BSD: return "BSD";
    case LIC_OTHER: return "Другая";
    default: return "Неизвестно";
    }
}

char* getActivity(int activity) {
    switch (activity) {
    case ACT_LOW: return "Низкая";
    case ACT_MEDIUM: return "Средняя";
    case ACT_HIGH: return "Высокая";
    default: return "Неизвестно";
    }
}

int showItem(DataItem item, int number) {
    printf("\n--- Проект %d ---\n", number);
    printf("Название: %s\n", item.name);
    printf("Лицензия: %s\n", getLicense(item.license));
    printf("Размер репозитория: %.2f МБ\n", item.size);
    printf("Дата создания: %02d.%02d.%04d\n", item.date.day, item.date.month, item.date.year);
    printf("Количество коммитов: %d\n", item.commits);
    printf("Язык программирования: %s\n", item.language);
    printf("Уровень активности: %s\n", getActivity(item.activity));
    return 1;
}

int showAll(DataItem* items, int count) {
    if (count == 0) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        showItem(items[i], i + 1);
    }
    return count;
}

int addItem(DataItem* items, int* count, DataItem* newItem) {
    if (*count >= MAX_ITEMS) {
        return -1;
    }
    items[*count] = *newItem;
    (*count)++;
    return 1;
}

int makeHash(const char* text) {
    int hash = 5381;
    int c;
    while ((c = *text++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

int findByRange(DataItem* items, int count, double minSize, double maxSize) {
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (items[i].size >= minSize && items[i].size <= maxSize) {
            showItem(items[i], i + 1);
            found++;
        }
    }
    return found;
}

int sortData(DataItem* items, int count) {
    if (count == 0) {
        return 0;
    }
    int swaps = 0;

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int needSwap = 0;

            int hash1 = makeHash(items[j].name);
            int hash2 = makeHash(items[j + 1].name);

            if (hash1 > hash2) {
                needSwap = 1;
            }
            else if (hash1 == hash2) {
                if (items[j].size < items[j + 1].size) {
                    needSwap = 1;
                }
            }

            if (needSwap) {
                DataItem temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
                swaps++;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        showItem(items[i], i + 1);
    }

    return swaps;
}

int saveToFile(DataItem* items, int count, char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) return -1;

    fwrite(&count, sizeof(int), 1, file);
    fwrite(items, sizeof(DataItem), count, file);

    fclose(file);
    return count;
}

int loadFromFile(DataItem* items, int* count, char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return -1;

    int fileCount;
    fread(&fileCount, sizeof(int), 1, file);

    int canLoad = (MAX_ITEMS - *count < fileCount) ? MAX_ITEMS - *count : fileCount;

    fread(&items[*count], sizeof(DataItem), canLoad, file);
    *count += canLoad;

    fclose(file);
    return canLoad;
}

int createTest(DataItem* items, int* count, DataItem* newItem, int num) {
    if (num < 1) {
        return -1;
    }
    if (*count + num > MAX_ITEMS) {
        return -2;
    }
    srand(time(NULL));
    char* names[] = {
        "проект1", "библиотека2", "приложение3", "инструмент4", "фреймворк5",
        "сервер6", "клиент7", "базаданных8", "вебприложение9", "мобильное10"
    };
    char* languages[] = {
        "C", "C++", "Java", "Python", "JavaScript",
        "Go", "Rust", "Swift", "Kotlin", "PHP"
    };
    for (int i = 0; i < num; i++) {
        strcpy(newItem->name, names[rand() % 10]);
        strcpy(newItem->language, languages[rand() % 10]);
        newItem->license = rand() % 5;
        newItem->size = 1.0 + (rand() % 20000) / 100.0;
        newItem->date.day = 1 + rand() % 28;
        newItem->date.month = 1 + rand() % 12;
        newItem->date.year = 2015 + rand() % 10;
        newItem->commits = rand() % 10000;
        newItem->activity = rand() % 3;
        items[*count] = *newItem;
        (*count)++;
    }
    return num;
}
