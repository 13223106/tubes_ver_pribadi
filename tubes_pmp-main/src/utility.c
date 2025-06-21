#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "utility.h"

void str_to_lower(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] > 'A' && str[i] < 'Z') {
            str[i] += 32;
        }
        i += 1;
    }
}

void clear_terminal() {
    printf("\e[1;1H\e[2J");
}

void free_list_of_strings(char** str, int size) {
    for (int i = 0; i < size; i ++) {
        free(str[i]);
    }
    free(str);
}

// buat 1 dokter
void free_dokter(Dokter* dokter) {
    free(dokter->nama);
    free(dokter->preference);
    free(dokter->spesialisasi);
    free(dokter);
}

// buat 1 linked list
void free_all_dokter(Dokter* data_dokter) {
    Dokter* before = data_dokter;
    while (data_dokter != NULL) {
        data_dokter = data_dokter->next;
        free_dokter(before);
        before = data_dokter;
    }
}

Dokter* cari_id(int id, Dokter* data_dokter) {
    while (data_dokter != NULL) {
        if (data_dokter->id == id) {
            return data_dokter;
        }
        data_dokter = data_dokter->next;
    }
    return NULL;
}

Dokter* cari_id_alamat_sebelumnya(int id, Dokter* data_dokter, Dokter** alamat_sebelumnya) {
    Dokter* before = NULL;
    while (data_dokter != NULL) {
        if (data_dokter->id == id) {
            *alamat_sebelumnya = before;
            return data_dokter;
        }
        before = data_dokter;
        data_dokter = data_dokter->next;
    }
    *alamat_sebelumnya = NULL;
    return NULL;
}