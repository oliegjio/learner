#ifndef DATASET_H_
#define DATASET_H_

#include <stdlib.h>

typedef enum LabelsFlag {
    NO_LABELS = 0,
    WITH_LABELS
} LabelsFlag;

typedef enum ColumnType {
    STRING_COLUMN = 0,
    NUMBER_COLUMN
} ColumnType;

typedef struct DatasetTable DatasetTable;
typedef struct TableColumn TableColumn;
typedef union TableCell TableCell;

DatasetTable *dataset_load_csv(const char *p, LabelsFlag lf);

void dataset_print_table(const DatasetTable *t);

#endif // DATASET_H_
