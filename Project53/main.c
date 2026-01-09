#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "project.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    DataItem* items = (DataItem*)malloc(MAX_ITEMS * sizeof(DataItem));
    int count = 0;
    int choice;
    int result;
    DataItem newItem;
    int licenseChoice;
    int activityChoice;
    double minSize, maxSize;
    char filename[100];
    int num;

    printf("=== Система управления база данных ===\n");

    do {
        printf("\n=== Главное меню ===\n");
        printf("1. Показать все записи\n");
        printf("2. Добавить новую запись\n");
        printf("3. Поиск записей\n");
        printf("4. Сортировка данных\n");
        printf("5. Сохранить в файл\n");
        printf("6. Загрузить из файла\n");
        printf("7. Создать тестовые данные\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            printf("\n=== Показать все записи ===\n");
            result = showAll(items, count);
            if (result == 0) {
                printf("Нет записей для отображения.\n");
                printf("Добавьте записи через пункт 'Добавить новую запись'.\n");
            }
            else {
                printf("Показано записей: %d (максимум %d)\n", result, MAX_ITEMS);
            }
            break;

        case 2:
            printf("\n=== Добавить новую запись ===\n");
            if (count >= MAX_ITEMS) {
                printf("Достигнут максимум записей (%d).\n", MAX_ITEMS);
                break;
            }
            printf("Название проекта: ");
            fgets(newItem.name, sizeof(newItem.name), stdin);
            newItem.name[strcspn(newItem.name, "\n")] = 0;
            printf("Тип лицензии:\n");
            printf("1 - MIT\n");
            printf("2 - Apache\n");
            printf("3 - GPL\n");
            printf("4 - BSD\n");
            printf("5 - Другая\n");
            printf("Лицензия: ");
            scanf("%d", &licenseChoice);
            while (getchar() != '\n');
            switch (licenseChoice) {
            case 1: newItem.license = LIC_MIT; break;
            case 2: newItem.license = LIC_APACHE; break;
            case 3: newItem.license = LIC_GPL; break;
            case 4: newItem.license = LIC_BSD; break;
            case 5: newItem.license = LIC_OTHER; break;
            default: newItem.license = LIC_MIT;
            }
            printf("Размер репозитория в МБ: ");
            scanf("%lf", &newItem.size);
            while (getchar() != '\n');

            printf("Дата создания (в формате день.месяц.год): ");
            char dateInput[20];
            fgets(dateInput, sizeof(dateInput), stdin);
            sscanf(dateInput, "%d.%d.%d",
                &newItem.date.day,
                &newItem.date.month,
                &newItem.date.year);

            printf("Количество коммитов: ");
            scanf("%d", &newItem.commits);
            while (getchar() != '\n');

            printf("Язык программирования: ");
            fgets(newItem.language, sizeof(newItem.language), stdin);
            newItem.language[strcspn(newItem.language, "\n")] = 0;

            printf("Уровень активности:\n");
            printf("1 - Низкий\n");
            printf("2 - Средний\n");
            printf("3 - Высокий\n");
            printf("Активность: ");
            scanf("%d", &activityChoice);
            while (getchar() != '\n');
            switch (activityChoice) {
            case 1: newItem.activity = ACT_LOW; break;
            case 2: newItem.activity = ACT_MEDIUM; break;
            case 3: newItem.activity = ACT_HIGH; break;
            default: newItem.activity = ACT_MEDIUM;
            }
            result = addItem(items, &count, &newItem);
            if (result == 1) {
                printf("Запись добавлена. Всего записей: %d\n", count);
            }
            else if (result == -1) {
                printf("Ошибка: достигнут максимум записей.\n");
            }
            break;

        case 3:
            printf("\n=== Поиск записей по размеру репозитория ===\n");
            printf("Минимальный размер (МБ): ");
            scanf("%lf", &minSize);
            printf("Максимальный размер (МБ): ");
            scanf("%lf", &maxSize);
            while (getchar() != '\n');

            result = findByRange(items, count, minSize, maxSize);
            if (result == 0) {
                printf("Записи в указанном диапазоне не найдены.\n");
            }
            else {
                printf("Найдено записей: %d\n", result);
            }
            break;

        case 4:
            printf("\n=== Сортировка данных ===\n");
            result = sortData(items, count);
            if (result == 0) {
                printf("Нет записей для сортировки.\n");
            }
            else {
                printf("Выполнено перестановок элементов: %d\n", result);
            }
            break;

        case 5:
            printf("\n=== Сохранить в файл ===\n");
            printf("Имя файла (в формате имя_файла.bin): ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = 0;
            result = saveToFile(items, count, filename);
            if (result == 0) {
                printf("Нет записей для сохранения.\n");
            }
            else if (result == -1) {
                printf("Ошибка открытия файла.\n");
            }
            else {
                printf("Сохранено записей: %d\n", result);
            }
            break;

        case 6:
            printf("\n=== Загрузить из файла ===\n");
            if (count >= MAX_ITEMS) {
                printf("Достигнут максимум записей (%d).\n", MAX_ITEMS);
                break;
            }
            printf("Имя файла: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = 0;
            int before = count;
            result = loadFromFile(items, &count, filename);
            if (result == -1) {
                printf("Ошибка открытия файла '%s'.\n", filename);
            }
            else if (result == 0) {
                printf("Файл пуст или нет места.\n");
            }
            else {
                int added = count - before;
                printf("Загружено записей: %d\n", added);
                printf("Всего записей: %d (до загрузки: %d)\n", count, before);
                printf("Доступно места: %d записей\n", MAX_ITEMS - count);
            }
            break;

        case 7:
            printf("\n=== Создать тестовые данные ===\n");
            printf("Введите количество создаваемых тестовых записей (1-%d): ", MAX_ITEMS - count);
            scanf("%d", &num);
            while (getchar() != '\n');
            result = createTest(items, &count, &newItem, num);
            if (result > 0) {
                printf("Создано тестовых записей: %d. Всего записей: %d\n", result, count);
            }
            else if (result == -1) {
                printf("Ошибка: количество записей должно быть не менее 1.\n");
            }
            else if (result == -2) {
                printf("Ошибка: недостаточно места. Доступно: %d записей\n", MAX_ITEMS - count);
            }
            break;

        case 0:
            printf("\nВыход из программы.\n");
            break;

        default:
            printf("\nОшибка: неверный выбор.\n");
            break;
        }

    } while (choice != 0);

    free(items);
    return 0;
}
