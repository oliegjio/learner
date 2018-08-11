#include "dataset.h"

#include <stdio.h>

struct DatasetTable {

    const char **l;
    enum CSV_LABEL_FLAG lf;

    float **c;
    size_t cs;

};

const char **get_csv_labels(FILE *f);

struct DatasetTable *dataset_csv_load(const char *p, enum CSV_LABEL_FLAG lf) {

    struct DatasetTable *d = (struct DatasetTable*) malloc(sizeof(struct DatasetTable));
    if (d == NULL) return NULL;

    const size_t bs = 1000;
    char buf[bs];

    FILE *f = fopen(p, "r");
    if (f == NULL) goto cleanup;

    if (lf == CSV_LABEL) {

        while (fgets(buf, bs, f) != NULL) {
            printf("%s", buf);
        }

    }

    if (lf == CSV_NO_LABEL) {

    }

    if (fclose(f) != 0) goto cleanup;

    d->lf = lf;

    return d;

    cleanup: {
        free(d);
        return NULL;
    };
}

// const char **get_csv_labels(FILE *f) {
//
//
// }
