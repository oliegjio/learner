#include "dataset_table.h"

#include <stdio.h>
#include <string.h>

#define STRING_SIZE 100
#define LABEL_SIZE 100

typedef union TableCell {

    char s[STRING_SIZE];
    float f;

} TableCell;

typedef struct TableColumn {

    ColumnType t;
    TableCell *c;
    size_t cs;
    
} TableColumn;

typedef struct DatasetTable {

    char **l;
    size_t lss;
    LabelsFlag lf;

    TableColumn *c;
    size_t cs;

} DatasetTable;

char **get_csv_labels(FILE *f, size_t ls, size_t lss);
size_t count_columns_in_file(FILE *f, char d);
size_t count_rows_in_file(FILE *f);

DatasetTable *dataset_load_csv(const char *p, LabelsFlag lf) {

    DatasetTable *t = (DatasetTable*) malloc(sizeof(DatasetTable));
    if (t == NULL) return NULL;

    const size_t buffer_size = 100;
    char buffer[buffer_size];

    FILE *f = fopen(p, "r");
    if (f == NULL) goto cleanup_from_file;

    size_t columns = count_columns_in_file(f, ',');
    if (columns == -1) goto cleanup_from_dataset;
    
    t->cs = columns;
    t->lss = LABEL_SIZE;
    t->lf = lf;

    if (lf == WITH_LABELS) {
        if ((t->l = get_csv_labels(f, t->cs, t->lss)) == NULL) goto cleanup_from_dataset;
    }

    if (fclose(f) != 0) return NULL;

    size_t rows = count_rows_in_file(f);
    for (size_t i = 0; i < rows; i++) {
        t->c = (TableColumn*) malloc(t->cs * sizeof(TableColumn));
    }

    return t;

    cleanup_from_columns: {
        free(t->c);
        goto cleanup_from_dataset;
    }
    cleanup_from_dataset: {
        fclose(f);
        goto cleanup_from_file;
    };
    cleanup_from_file: {
        free(t);
        return NULL;
    };
}

char **get_csv_labels(FILE *f, size_t ls, size_t lss) {

    char line[lss];

    rewind(f);
    if (fgets(line, lss, f) == NULL) return NULL;

    size_t counter = 1;
    size_t indexes[lss];
    indexes[0] = -1;

    for (size_t i = 0; i < strlen(line); i++) {

        if (line[i] == ',' || line[i] == '\n') {

            indexes[counter] = i;
            counter += 1;

        }
    }

    if (counter - 1 != ls) return NULL;

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




