#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "showSchedule.h"
#include "data.h"
const char* getNamaHari(int hari_ke) {
    const char* namaHari[] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};
    return namaHari[(hari_ke - 1) % 7];
}

void showScheduleByMonth(Jadwal* head) {
    printf("\n=== JADWAL DOKTER BULANAN ===\n");
    printf("+-----------+--------+----------------------+----------------------+\n");
    printf("| Hari      | Shift  | Dokter               | Spesialis            |\n");
    printf("+-----------+--------+----------------------+----------------------+\n");

    while (head != NULL) {
        const char* namaHari = getNamaHari(head->hari_ke);

        for (int i = 0; i < 10; i++) {
            if (head->daftar_dokter[i] != NULL) {
                printf("| %-9s | %-6s | %-20s | %-20s |\n",
                    (i == 0) ? namaHari : "",
                    (i == 0) ? head->shift : "",
                    head->daftar_dokter[i]->nama,
                    head->daftar_dokter[i]->spesialisasi);
            }
        }

        printf("+-----------+--------+----------------------+----------------------+\n");
        head = head->next;
    }
}

void showScheduleByWeek(Jadwal* head, int minggu_ke) {
    printf("\n=== JADWAL DOKTER - MINGGU KE-%d ===\n", minggu_ke);
    printf("+-----------+--------+----------------------+----------------------+\n");
    printf("| Hari      | Shift  | Dokter               | Spesialis            |\n");
    printf("+-----------+--------+----------------------+----------------------+\n");

    while (head != NULL) {
        int minggu = (head->hari_ke - 1) / 7 + 1;
        if (minggu == minggu_ke) {
            const char* namaHari = getNamaHari(head->hari_ke);

            for (int i = 0; i < 10; i++) {
                if (head->daftar_dokter[i] != NULL) {
                    printf("| %-9s | %-6s | %-20s | %-20s |\n",
                        (i == 0) ? namaHari : "",
                        (i == 0) ? head->shift : "",
                        head->daftar_dokter[i]->nama,
                        head->daftar_dokter[i]->spesialisasi);
                }
            }

            printf("+-----------+--------+----------------------+----------------------+\n");
        }

        head = head->next;
    }
}

void showScheduleByDay(Jadwal* head, int minggu_ke, int hari_ke) {
    const char* namaHari = getNamaHari(hari_ke);
    printf("\n=== JADWAL DOKTER - %s (HARI KE-%d, MINGGU KE-%d) ===\n", namaHari, hari_ke, minggu_ke);
    printf("+-----------+--------+----------------------+----------------------+\n");
    printf("| Hari      | Shift  | Dokter               | Spesialis            |\n");
    printf("+-----------+--------+----------------------+----------------------+\n");

    int found = 0;

    while (head != NULL) {
        int minggu = (head->hari_ke - 1) / 7 + 1;

        if (minggu == minggu_ke && head->hari_ke == hari_ke) {
            for (int i = 0; i < 10; i++) {
                if (head->daftar_dokter[i] != NULL) {
                    printf("| %-9s | %-6s | %-20s | %-20s |\n",
                        (i == 0) ? namaHari : "",
                        (i == 0) ? head->shift : "",
                        head->daftar_dokter[i]->nama,
                        head->daftar_dokter[i]->spesialisasi);
                    found = 1;
                }
            }
            printf("+-----------+--------+----------------------+----------------------+\n");
        }

        head = head->next;
    }

    if (!found) {
        printf("| Tidak ada jadwal ditemukan untuk hari & minggu ini.         |\n");
        printf("+--------------------------------------------------------------+\n");
    }
}

void showSpesificByMonth(Jadwal* head, int id_dokter) {
    printf("\n=== JADWAL DOKTER ID %d (1 BULAN) ===\n", id_dokter);
    printf("+-----------+--------+\n");
    printf("| Hari      | Shift  |\n");
    printf("+-----------+--------+\n");

    int ditemukan = 0;

    while (head != NULL) {
        for (int i = 0; i < 10; i++) {
            if (head->daftar_dokter[i] != NULL && head->daftar_dokter[i]->id == id_dokter) {
                const char* hari = getNamaHari(head->hari_ke);
                printf("| %-9s | %-6s |\n", hari, head->shift);
                ditemukan = 1;
                break;
            }
        }
        head = head->next;
    }

    if (!ditemukan) {
        printf("| Tidak ada jadwal ditemukan. |\n");
    }

    printf("+-----------+--------+\n");
}

void showSpesificByWeek(Jadwal* head, int id_dokter, int minggu_ke) {
    printf("\n=== JADWAL DOKTER ID %d (MINGGU KE-%d) ===\n", id_dokter, minggu_ke);
    printf("+-----------+--------+\n");
    printf("| Hari      | Shift  |\n");
    printf("+-----------+--------+\n");

    int ditemukan = 0;

    while (head != NULL) {
        int minggu = (head->hari_ke - 1) / 7 + 1;
        if (minggu == minggu_ke) {
            for (int i = 0; i < 10; i++) {
                if (head->daftar_dokter[i] != NULL && head->daftar_dokter[i]->id == id_dokter) {
                    const char* hari = getNamaHari(head->hari_ke);
                    printf("| %-9s | %-6s |\n", hari, head->shift);
                    ditemukan = 1;
                    break;
                }
            }
        }
        head = head->next;
    }

    if (!ditemukan) {
        printf("| Tidak ada jadwal ditemukan. |\n");
    }

    printf("+-----------+--------+\n");
}

void showSpesificByDay(Jadwal* head, int id_dokter, int minggu_ke, int hari_ke) {
    const char* hari = getNamaHari(hari_ke);
    printf("\n=== JADWAL DOKTER ID %d (HARI %s - MINGGU KE-%d) ===\n", id_dokter, hari, minggu_ke);
    printf("+-----------+--------+\n");
    printf("| Hari      | Shift  |\n");
    printf("+-----------+--------+\n");

    int ditemukan = 0;

    while (head != NULL) {
        int minggu = (head->hari_ke - 1) / 7 + 1;

        if (minggu == minggu_ke && head->hari_ke == hari_ke) {
            for (int i = 0; i < 10; i++) {
                if (head->daftar_dokter[i] != NULL && head->daftar_dokter[i]->id == id_dokter) {
                    printf("| %-9s | %-6s |\n", hari, head->shift);
                    ditemukan = 1;
                    break;
                }
            }
        }
        head = head->next;
    }

    if (!ditemukan) {
        printf("| Tidak ada jadwal ditemukan. |\n");
    }

    printf("+-----------+--------+\n");
}
