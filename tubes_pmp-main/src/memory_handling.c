#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "memory_handling.h"
#include "utility.h"

void print_data_dokter(Dokter* dokter) {
    printf("1. Nama: %s\n", dokter->nama);
    printf("2. Spesialisasi: %s\n", dokter->spesialisasi);
    printf("3. Max shift: %d\n", dokter->max_shift);
    printf("4. Preferensi: %s\n", dokter->preference);
}

void tambah_dokter(Dokter** data_dokter, int* size) {
    Dokter* data_dokter_ = *data_dokter;
    int size_ = *size;

    printf("Masukkan data dokter baru :\n");
    char nama[100];
    char spesialis[100];
    char max_shift[3];
    char preferensi[10];

    printf("Nama : ");
    fseek(stdin, 0, SEEK_END);
    fgets(nama, 100, stdin);
    nama[99] = '\0';
    nama[strlen(nama) - 1] = '\0';

    printf("Spesialis : ");
    fgets(spesialis, 100, stdin);
    spesialis[99] = '\0';
    spesialis[strlen(spesialis) - 1] = '\0';

    printf("Maximum shift : ");
    fgets(max_shift, 100, stdin);
    max_shift[99] = '\0';
    max_shift[strlen(max_shift) - 1] = '\0';

    printf("Preferensi : ");
    fgets(preferensi, 100, stdin);
    preferensi[99] = '\0';
    preferensi[strlen(preferensi) - 1] = '\0';

    Dokter* cur = data_dokter_;
    Dokter* before = NULL;
    while(cur != NULL) {
        if (!strcmp(nama, data_dokter_->nama)) {
            printf("Dokter tersebut telah ditambahkan\n");
            return;
        }
        before = cur;
        cur = cur->next;
    }

    size_ += 1;
    Dokter* dokter_baru = (Dokter*) malloc(sizeof(Dokter));
    
    if (data_dokter_ == NULL) {
        *data_dokter = dokter_baru;
        dokter_baru->id = 1;
    } else {
        dokter_baru->id = before->id + 1;
        before->next = dokter_baru;
    }
    

    dokter_baru->nama = (char*) malloc(sizeof(char) * strlen(nama) + 1);
    strcpy(dokter_baru->nama, nama);

    dokter_baru->spesialisasi = (char*) malloc(sizeof(char) * strlen(spesialis) + 1);
    strcpy(dokter_baru->spesialisasi, spesialis);

    dokter_baru->max_shift = atoi(max_shift);

    dokter_baru->preference = (char*) malloc(sizeof(char) * strlen(preferensi) + 1);
    strcpy(dokter_baru->preference, preferensi);

    dokter_baru->next = NULL;

    *size = size_;
}

void hapus_dokter(Dokter** data_dokter, int* size) {
    clear_terminal();
    int run = 1;
    int id;
    char confirm;

    Dokter* data_dokter_ = *data_dokter;
    Dokter* cur; 
    Dokter* before;
    while (run) {
        printf("0. Keluar\n");
        printf("Id dokter mana yang ingin dihapus : ");
        scanf(" %d", &id);
        cur = cari_id_alamat_sebelumnya(id, data_dokter_, &before);
        
        if (id == 0) {
            *data_dokter = data_dokter_;
            run = 0;
            clear_terminal();
            continue;
        }

        if (cur == NULL) {
            clear_terminal();
            printf("Id yang ditunjuk tidak ada\n");
            continue;
        } else {
            print_data_dokter(cur);

            printf("Apakah data dokter tersebut ingin dihapus?(Y/N): ");
            scanf(" %c", &confirm);

            if (!(confirm == 'Y' || confirm == 'y')) {
                clear_terminal();
                printf("Id %d tidak jadi dihapus\n", id);
                continue;
            }

        }

        if (before == NULL) {
            data_dokter_ = data_dokter_->next;
        } else {
            before->next = cur->next;
            
        }
        free_dokter(cur);
        *size -= 1;
        clear_terminal();
        printf("Id %d berhasil dihapus\n", id);
    }
    
}

void ubah_dokter(Dokter* data_dokter) {
    int run = 1;
    int id;

    Dokter* cur; 
    while (run) {
        printf("0. Keluar\n");
        printf("Id dokter mana yang ingin diganti datanya : ");
        scanf(" %d", &id);
        cur = cari_id(id, data_dokter);
        
        if (id == 0) {
            run = 0;
            clear_terminal();
            continue;
        }

        if (cur == NULL) {
            clear_terminal();
            printf("Id yang ditunjuk tidak ada\n");
            continue;
        }

        int process = 1;
        char buffer[100];
        while (process) {
            clear_terminal();
            printf("Id dokter: %d\n", id);
            printf("0. Kembali\n");
            print_data_dokter(cur);
            printf("\n");
            printf("Data mana yang ingin diubah: ");
            fseek(stdin, 0, SEEK_END);
            fgets(buffer, 100, stdin);

            buffer[99] = '\0';
            buffer[strlen(buffer) - 1] = '\0';
            str_to_lower(buffer);

            if (buffer[0] == '1' || !strcmp(buffer, "nama")) {
                printf("Masukkan nama baru: ");
                fgets(buffer, 100, stdin);
                buffer[99] = '\0';
                buffer[strlen(buffer) - 1] = '\0';

                cur->nama = (char*) realloc(cur->nama, sizeof(char) * (strlen(buffer) + 1));
                strcpy(cur->nama, buffer);

            } else if (buffer[0] == '2' || !strcmp(buffer, "spesialisasi")) {
                printf("Masukkan spesialisasi baru: ");
                fgets(buffer, 100, stdin);
                buffer[99] = '\0';
                buffer[strlen(buffer) - 1] = '\0';

                cur->spesialisasi = (char*) realloc(cur->spesialisasi, sizeof(char) * (strlen(buffer) + 1));
                strcpy(cur->spesialisasi, buffer);
                
            } else if (buffer[0] == '3' || !strcmp(buffer, "max shift")) {
                printf("Masukkan max shift baru: ");
                scanf(" %d", &cur->max_shift);

            } else if (buffer[0] == '4' || !strcmp(buffer, "preferensi")) {
                printf("Masukkan preferensi baru: ");
                fgets(buffer, 100, stdin);
                buffer[99] = '\0';
                buffer[strlen(buffer) - 1] = '\0';

                cur->preference = (char*) realloc(cur->preference, sizeof(char) * (strlen(buffer) + 1));
                strcpy(cur->preference, buffer);

            } else if (buffer[0] == '0' || !strcmp(buffer, "kembali")) {
                process = 0;
                clear_terminal();
            }

        }
    }
}