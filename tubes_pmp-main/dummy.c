#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/data.h"
#include "src/showSchedule.h"

int main() {
    // Dokter dummy (nama dialokasikan manual)
    Dokter dokter1;
    dokter1.id = 1;
    dokter1.nama = (char*)malloc(sizeof(char) * 20);
    strcpy(dokter1.nama, "dr. Siti");
    dokter1.spesialisasi = (char*)malloc(sizeof(char) * 20);
    strcpy(dokter1.spesialisasi, "Anak");
    dokter1.max_shift = 5;
    dokter1.preference = (char*)malloc(sizeof(char) * 10);
    strcpy(dokter1.preference, "Pagi");
    dokter1.next = NULL;

    Dokter dokter2;
    dokter2.id = 2;
    dokter2.nama = (char*)malloc(sizeof(char) * 20);
    strcpy(dokter2.nama, "dr. Budi");
    dokter2.spesialisasi = (char*)malloc(sizeof(char) * 20);
    strcpy(dokter2.spesialisasi, "Bedah");
    dokter2.max_shift = 5;
    dokter2.preference = (char*)malloc(sizeof (char) * 10);
    strcpy(dokter2.preference, "Siang");
    dokter2.next = NULL;

    const char* shift_list[3] = {"Pagi", "Siang", "Malam"};

    Jadwal* head = NULL;
    Jadwal* tail = NULL;

    for (int hari = 1; hari <= 30; hari++) {
        for (int s = 0; s < 3; s++) {
            Jadwal* node = (Jadwal*)malloc(sizeof(Jadwal));
            node->hari_ke = hari;
            node->shift = (char*)malloc(sizeof(char) * 10);
            strcpy(node->shift, shift_list[s]);

            // Masukkan 2 dokter pertama
            node->daftar_dokter[0] = dokter1;
            node->daftar_dokter[1] = dokter2;

            // Sisanya dikosongkan
            for (int i = 2; i < 10; i++) {
                node->daftar_dokter[i].id = -1;
                node->daftar_dokter[i].nama = NULL;
                node->daftar_dokter[i].spesialisasi = NULL;
                node->daftar_dokter[i].preference = NULL;
                node->daftar_dokter[i].next = NULL;
            }

            node->next = NULL;

            // Tambahkan ke linked list
            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
    }

    //Jadwal* temp = head;

    /*
    int counter = 0;
    while (temp != NULL && counter < 3) {  // Cukup 3 node pertama
        printf("Hari ke-%d, Shift: %s\n", temp->hari_ke, temp->shift);
        for (int j = 0; j < 10; j++) {
            if (temp->daftar_dokter[j].id != -1 && temp->daftar_dokter[j].nama != NULL) {
                printf("  - %s (%s)\n", temp->daftar_dokter[j].nama, temp->daftar_dokter[j].spesialisasi);
            }
        }
        printf("------------------------\n");
        temp = temp->next;
        counter++;
    }
        */
    showScheduleByDay(head,1,2);
}

