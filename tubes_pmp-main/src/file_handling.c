#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "file_handling.h"
#include "utility.h"

void read_file(const char* file_name, Dokter** data_dokter_h, Dokter** data_dokter_t, int* size, char*** header_csv) {
    // pembacaan file dimulai dari null, jika tidak harus di free dulu
    if (*data_dokter_h != NULL) {
        return;
    }
    // buka file
    FILE* file_ptr = fopen(file_name, "r");
    if (file_ptr == NULL) {
        printf("File gagal dibuka!\n");
        return;
    }

    int size_ = *size;
    Dokter* data_dokter_head = NULL;
    Dokter* data_dokter_tail = NULL;

    // buffer untuk menerima input
    char buffer_input[1000];
    char* buffer_pointer_point[10];
    int max_column = 0;

    // tandai keterangan header csv
    fgets(buffer_input, 1000, file_ptr);
    int index = 0;
    buffer_pointer_point[max_column] = buffer_input;
    while (buffer_input[index] != '\0') {
        if (buffer_input[index] == ',') {
            buffer_input[index] = '\0';
            max_column += 1;
            buffer_pointer_point[max_column] = buffer_input + index + 1;
        } else if (buffer_input[index] == '\n') {
            buffer_input[index] = '\0';
        }
        index += 1;
    }

    // ambil keterangan header csv dan simpan ke array
    char** header_csv_ = (char**) malloc(sizeof(char*) * (max_column + 1));
    for (int i = 0; i <= max_column; i ++) {
        header_csv_[i] = (char*) malloc(sizeof(char) * (strlen(buffer_pointer_point[i]) + 1));
        strcpy(header_csv_[i], buffer_pointer_point[i]);
    }
    *header_csv = header_csv_;

    // ambil data dokter
    max_column = 0;
    while (fgets(buffer_input, 1000, file_ptr)) {
        buffer_input[999] = '\0';

        int index = 0;
        buffer_pointer_point[max_column] = buffer_input;

        // separasi file csv
        while (buffer_input[index] != '\0') {
            if (buffer_input[index] == ',') {
                buffer_input[index] = '\0';
                max_column += 1;
                buffer_pointer_point[max_column] = buffer_input + index + 1;
            } else if (buffer_input[index] == '\n') {
                buffer_input[index] = '\0';
            }
            index += 1;
        }

        if (max_column <= 1) {
            break;
        }
        
        size_ += 1;

        // input data ke struct
        Dokter* dokter_baru = (Dokter*) malloc(sizeof(Dokter));
        dokter_baru->id = atoi(buffer_pointer_point[0]);

        dokter_baru->nama = (char*) malloc(sizeof(char) * (strlen(buffer_pointer_point[1]) + 1));
        strcpy(dokter_baru->nama, buffer_pointer_point[1]);

        dokter_baru->spesialisasi = (char*) malloc(sizeof(char) * (strlen(buffer_pointer_point[2]) + 1));
        strcpy(dokter_baru->spesialisasi, buffer_pointer_point[2]);

        dokter_baru->max_shift = atoi(buffer_pointer_point[3]);

        dokter_baru->preference = (char*) malloc(sizeof(char) * (strlen(buffer_pointer_point[4]) + 1));
        strcpy(dokter_baru->preference, buffer_pointer_point[4]);

        dokter_baru->next = NULL;
        
        max_column = 0;

        if (size_ == 1) {
            data_dokter_tail = dokter_baru;
            data_dokter_head = dokter_baru;
            continue;
        }

        data_dokter_tail->next = dokter_baru;
        data_dokter_tail = dokter_baru;

    }

    *data_dokter_h = data_dokter_head;
    *data_dokter_t = data_dokter_tail;
    *size = size_;
    fclose(file_ptr);
}

void overwrite_file(const char* file_name, Dokter* data_dokter, char** header_csv) {
    // buka file
    FILE* file_ptr = fopen(file_name, "w");
    if (file_ptr == NULL) {
        printf("File gagal dibuka!\n");
        return;
    }

    // tulis header
    for (int i = 0; i < 4; i ++) {
        fprintf(file_ptr,"%s,", header_csv[i]);
    }
    fprintf(file_ptr,"%s\n", header_csv[4]);

    // tulis data
    while (data_dokter != NULL) {
        fprintf(file_ptr, "%d,%s,%s,%d,%s\n", data_dokter->id ,data_dokter->nama, data_dokter->spesialisasi, data_dokter->max_shift, data_dokter->preference);
        data_dokter = data_dokter->next;
    }

    // tutup file
    fclose(file_ptr);
}

void close_program(Dokter* data_dokter, char** keterangan_csv) {
    printf("Apakah ingin menyimpan perubahan yang dilakukan? (Y/N)");
    char yesno;
    scanf(" %c", &yesno);
    if (yesno == 'y' || yesno == 'Y') {
        overwrite_file("data/data_dokter.csv", data_dokter, keterangan_csv);
    }
    free_all_dokter(data_dokter);
    free_list_of_strings(keterangan_csv, 5);
}