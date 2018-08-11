#ifndef DATASET_H_
#define DATASET_H_

#include <stdlib.h>

enum CSV_LABEL_FLAG {
    CSV_NO_LABEL = 0,
    CSV_LABEL
};

enum DATASET_COLUMN_TYPE {
    STRING_COLUMN_TYPE = 0,
    NUMBER_COLUMN_TYPE
};

struct DatasetTable;

struct DatasetTable *dataset_csv_load(const char *p, enum CSV_LABEL_FLAG lf);

#endif // DATASET_H_
