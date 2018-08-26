#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "machine_learning.h"

int main(int argc, char *argv[]) {

    srand((unsigned int) time(NULL));

    DatasetTable *ds = dataset_load_csv("../datasets/iris.csv", WITH_LABELS);
    if (ds == NULL) {
        printf("FAIL! \n");
        return 0;
    }
    dataset_print_table(ds);

     /* int cfg[] = {2, 2, 1}; */
     /* Perceptron *p = perceptron_create(cfg, 3); */
     /* perceptron_print(p); */
     /* perceptron_randomize(p, 1.5, 2); */

     /* float samples[4][3]; */
     /* samples[0][0] = 1; */
     /* samples[0][1] = 0; */
     /* samples[0][2] = 1; */

     /* samples[1][0] = 0; */
     /* samples[1][1] = 1; */
     /* samples[1][2] = 1; */

     /* samples[2][0] = 1; */
     /* samples[2][1] = 1; */
     /* samples[2][2] = 0; */

     /* samples[3][0] = 0; */
     /* samples[3][1] = 0; */
     /* samples[3][2] = 0; */

     /* float input[2]; */
     /* float target[1]; */
     /* float output[1]; */
     /* float error[1]; */
     /* float error_avg = 0; */
     /* float error_avg_before = 0; */
     /* int min = 0; */
     /* int max = 4 - 1; */
     /* int r; */
     /* int train_time = 100000; */
     /* int train_select = 100; */

     /* for (int i = 0; i < train_time; i++) { */
     /*     r = rand() % (max + 1 - min) + min; */
     /*     input[0] = samples[r][0]; */
     /*     input[1] = samples[r][1]; */
     /*     target[0] = samples[r][2]; */

     /*     if (perceptron_train(p, input, 2, target, 1) == 0) return 0; */
     /*     if (perceptron_feedforward(p, input, 2, output, 1) == 0) return 0; */

     /*     error[0] = target[0] - output[0]; */
     /*     if (i < train_select || i > train_time - train_select) { */
     /*        /\* printf("INPUT: [%.0f, %.0f]  |  TARGET: %.0f  |  OUTPUT: %.2f  |  ERROR: %.2f \n", input[0], input[1], target[0], output[0], error[0]); *\/ */
     /*     } */
     /*     if (i > train_time - train_select) { */
     /*         error_avg += fabs(error[0]); */
     /*     } */
     /*     if (i < train_select) { */
     /*         error_avg_before += fabs(error[0]); */
     /*     } */
     /* } */
     /* error_avg /=  train_select; */
     /* printf("AFTER AVG ERROR: %f \n", error_avg); */

     /* error_avg_before /= train_select; */
     /* printf("BEFORE AVG ERROR: %f \n", error_avg_before); */

     /* perceptron_destroy(p); */

    return 0;
}
