#include "summary.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "constants.h"

void write_csv_header(const char filename[]) {
    FILE* file = fopen(filename, "w");

    if (!file) {
        perror("Failed to open file for writing header");
        return;
    }

    fprintf(file, "Set,Total,Time");

    for (uint8_t i = 0; i < NUMBER_OF_PROPERTIES; i++)
        fprintf(file, ",%s_Count,%s_Pct", PROPERTY_NAMES[i], PROPERTY_NAMES[i]);

    fprintf(file, "\n");
    fclose(file);
}

void append_results_to_csv(const char filename[], uint8_t set_size,
                           uint64_t count[NUMBER_OF_PROPERTIES],
                           uint64_t total_relations, double elapsed) {
    FILE* file = fopen(filename, "a");

    if (!file) {
        perror("Failed to open file for appending");
        return;
    }

    fprintf(file, "%" PRIu8 ",%" PRIu64 ",%f", set_size, total_relations,
            elapsed);

    for (uint8_t i = 0; i < NUMBER_OF_PROPERTIES; i++) {
        float pct = ((float)count[i] / total_relations) * 100;
        fprintf(file, ",%" PRIu64 ",%f", count[i], pct);
    }

    fprintf(file, "\n");
    fclose(file);
}
