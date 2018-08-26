#include "dataset_table.h"

#include <stdio.h>
#include <string.h>

typedef union TableCell {

    char s[100];
    float f;

} TableCell;

typedef struct DatasetTable {

    char **l;
    LabelsFlag lf;

    TableCell **c;
    size_t cs;
    size_t css;

} DatasetTable;

char **get_csv_labels(FILE *f);
size_t count_columns_in_file(FILE *f, char d);
size_t count_rows_in_file(FILE *f);

DatasetTable *dataset_load_csv(const char *p, LabelsFlag lf) {

    DatasetTable *t = (DatasetTable*) malloc(sizeof(DatasetTable));
    if (t == NULL) return NULL;

    const size_t buffer_size = 100;
    char buffer[buffer_size];

    FILE *f = fopen(p, "r");
    if (f == NULL) goto cleanup_from_dataset;

    if (lf == WITH_LABELS) {
        if ((t->l = get_csv_labels(f)) == NULL) goto cleanup_from_file;
    }


    t->cs = count_columns_in_file(f, ',');
    t->css = count_rows_in_file(f);
    t->lf = lf;

    printf("!!! %d \n", t->css);

    if (fclose(f) != 0) goto cleanup_from_file;

    return t;

    cleanup_from_file: {
        fclose(f);
        goto cleanup_from_dataset;
    };
    cleanup_from_dataset: {
        free(t);
        return NULL;
    };
}

char **get_csv_labels(FILE *f) {

    const size_t line_size = 100;
    char line[line_size];

    if (fgets(line, line_size, f) == NULL) return NULL;

    size_t counter = 1;
    size_t indexes[line_size];
    indexes[0] = -1;

    for (size_t i = 0; i < strlen(line); i++) {

        if (line[i] == ',' || line[i] == '\n') {

            indexes[counter] = i;
            counter += 1;

        }
    }

    char **r = (char**) malloc(counter * sizeof(char*));
    if (r == NULL) return NULL;

    for (size_t i = 0; i < counter - 1; i++) {

        size_t length = indexes[i + 1] - indexes[i] - 1;
        r[i] = (char*) malloc(length * sizeof(char));
        memcpy(r[i], line + indexes[i] + 1, length);
    }

    return r;
}

size_t count_columns_in_file(FILE *f, char d) {

    size_t buffer_size = 1000;
    char buffer[buffer_size];

    if ((fgets(buffer, buffer_size, f)) == NULL) return -1;

    size_t counter = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == d || buffer[i] == '\n') {
            counter += 1;
        }
    }

    return counter;
}

size_t count_rows_in_file(FILE *f) {

    size_t counter = 0;

    while (!feof(f)) {
        if (fgetc(f) == '\n') counter++;
    }
    
    return counter;
}

void dataset_print_table(const DatasetTable *t) {

    printf("| ");
    for (size_t i = 0; i < t->cs; i++) {
        printf("%s | ", t->l[i]);
    }
    printf("\n");
}




