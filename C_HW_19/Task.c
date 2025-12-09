#include <stdio.h>
#include <locale.h>

typedef struct {
    char title[100];
    int year;
    char style[50];
    int tracks;
    double duration;
} Album;

void input_album(Album* a);
void print_album(const Album a);
void print_suitable_albums(const Album arr[], int n);
int writefile(const char* fname, const Album* arr, int size);

int main() {
    setlocale(LC_ALL, "RUS");

    int n = 5;
    Album arr[10];

    printf("Ввод альбомов:\n");
    for (int i = 0; i < n; i++) {
        printf("\n=== Альбом %d ===\n", i + 1);
        input_album(&arr[i]);
    }

    printf("\nВсе альбомы:\n");
    for (int i = 0; i < n; i++) {
        print_album(arr[i]);
    }

    print_suitable_albums(arr, n);

    if (writefile("albums.txt", arr, n)) {
        printf("\nФайл успешно записан.\n");
    }

    return 0;
}


void input_album(Album* a) {
    printf("Введите название (без пробелов, используйте _ ): ");
    scanf("%99s", (*a).title);

    printf("Введите год выпуска: ");
    scanf("%d", &(*a).year);

    printf("Введите стиль (без пробелов): ");
    scanf("%49s", (*a).style);

    printf("Введите количество треков: ");
    scanf("%d", &(*a).tracks);

    printf("Введите длительность (минуты): ");
    scanf("%lf", &(*a).duration);
}

void print_album(const Album a) {
    printf("\nНазвание: %s\n", a.title);
    printf("Год выпуска: %d\n", a.year);
    printf("Стиль: %s\n", a.style);
    printf("Количество треков: %d\n", a.tracks);
    printf("Длительность: %.2f минут\n", a.duration);
}

void print_suitable_albums(const Album arr[], int n) {
    printf("\nПодходящие альбомы:\n");

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].tracks >= 10 && arr[i].duration <= 50.0) {
            print_album(arr[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("Нет подходящих альбомов.\n");
    }
}

int writefile(const char* fname, const Album* arr, int size) {
    FILE* out = fopen(fname, "wt");
    if (out == NULL) {
        printf("Ошибка открытия файла!\n");
        return 0;
    }

    for (int i = 0; i < size; i++) {
        fprintf(out, "%s %d %s %d %.2f\n",
            arr[i].title,
            arr[i].year,
            arr[i].style,
            arr[i].tracks,
            arr[i].duration);
    }

    fclose(out);
    return 1;
}