#ifndef project_h
#define project_h

#define MAX_ITEMS 50

// Перечисление для типов лицензий
enum License {
    LIC_MIT,
    LIC_APACHE,
    LIC_GPL,
    LIC_BSD,
    LIC_OTHER
};

// Перечисление для уровней активности
enum Activity {
    ACT_LOW,
    ACT_MEDIUM,
    ACT_HIGH
};

// Структура для даты
typedef struct {
    int day;
    int month;
    int year;
} MyDate;

// Структура элемента данных
typedef struct {
    char name[32];
    int license;
    double size;
    MyDate date;
    int commits;
    char language[20];
    int activity;
} DataItem;

/**
 * @brief Преобразует числовой код лицензии в строковое представление
 * @param license Числовой код лицензии (из enum License)
 * @return Указатель на строку с названием лицензии
 */
char* getLicense(int license);

/**
 * @brief Преобразует числовой код активности в строковое представление
 * @param activity Числовой код активности (из enum Activity)
 * @return Указатель на строку с описанием уровня активности
 */
char* getActivity(int activity);

/**
 * @brief Отображает информацию об одном элементе данных
 * @param item Элемент данных для отображения
 * @param number Порядковый номер элемента
 * @return Всегда возвращает 1
 */
int showItem(DataItem item, int number);

/**
 * @brief Отображает информацию обо всех элементах в массиве
 * @param items Указатель на массив элементов данных
 * @param count Количество элементов в массиве
 * @return Количество отображенных элементов (0 если массив пуст)
 */
int showAll(DataItem* items, int count);

/**
 * @brief Добавляет новый элемент в массив
 * @param items Указатель на массив элементов данных
 * @param count Указатель на переменную с количеством элементов
 * @param newItem Указатель на новый элемент для добавления
 * @return 1 при успешном добавлении, -1 при достижении максимального количества
 */
int addItem(DataItem* items, int* count, DataItem* newItem);

/**
 * @brief Вычисляет хэш строки для сортировки
 * @param text Входная строка
 * @return Числовой хэш строки
 */
int makeHash(const char* text);

/**
 * @brief Ищет элементы по диапазону размера репозитория
 * @param items Указатель на массив элементов данных
 * @param count Количество элементов в массиве
 * @param minSize Минимальный размер репозитория
 * @param maxSize Максимальный размер репозитория
 * @return Количество найденных элементов
 */
int findByRange(DataItem* items, int count, double minSize, double maxSize);

/**
 * @brief Сортирует элементы по хэшу названия (при равенстве - по размеру)
 *        и отображает отсортированный массив
 * @param items Указатель на массив элементов данных
 * @param count Количество элементов в массиве
 * @return Количество выполненных перестановок при сортировке
 */
int sortData(DataItem* items, int count);

/**
 * @brief Сохраняет массив элементов в бинарный файл
 * @param items Указатель на массив элементов данных
 * @param count Количество элементов в массиве
 * @param filename Имя файла для сохранения
 * @return Количество сохраненных элементов, -1 при ошибке открытия файла
 */
int saveToFile(DataItem* items, int count, char* filename);

/**
 * @brief Загружает элементы из бинарного файла в массив
 * @param items Указатель на массив элементов данных
 * @param count Указатель на переменную с количеством элементов
 * @param filename Имя файла для загрузки
 * @return Количество загруженных элементов, -1 при ошибке открытия файла
 */
int loadFromFile(DataItem* items, int* count, char* filename);

/**
 * @brief Создает тестовые данные
 * @param items Указатель на массив элементов данных
 * @param count Указатель на переменную с количеством элементов
 * @param newItem Указатель на временный элемент для заполнения
 * @param num Количество тестовых элементов для создания
 * @return Количество созданных элементов, -1 при неверном параметре,
 *         -2 при недостатке места
 */
int createTest(DataItem* items, int* count, DataItem* newItem, int num);

#endif

