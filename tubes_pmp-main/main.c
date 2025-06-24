#include <stdio.h>
#include <stdlib.h>
#include "src/data.h"
#include "src/file_handling.h"
#include "src/memory_handling.h"
#include "src/utility.h"
#include "src/penjadwalan.h"
#include "src/showSchedule.h"

void print_dokter(Dokter* dokter) {
    while (dokter != NULL) {
        printf("%d %s %s %d %s\n", dokter->id, dokter->nama, dokter->spesialisasi, dokter->max_shift, dokter->preference);
        dokter = dokter->next;
    }
}

int main() {
    Dokter* data_dokter = NULL;
    Dokter* data_dokter_tail = NULL;
    char** keterangan_csv = NULL;
    int size = 0;

    Jadwal* jadwal_bulanan = NULL;

    // Baca data dari CSV
    read_file("data/data_dokter.csv", &data_dokter, &data_dokter_tail, &size, &keterangan_csv);

    int run = 1;
    char input;

    while (run) {
        printf("\n=== MENU ===\n");
        printf("1. Tambah Dokter\n");
        printf("2. Hapus Dokter\n");
        printf("3. Lihat Semua Dokter\n");
        printf("4. Ubah Data Dokter\n");
        printf("5. Buat Jadwal Bulanan\n");
        printf("6. Lihat Jadwal Bulanan\n");
        printf("7. Lihat Jadwal Mingguan\n");
        printf("8. Lihat Jadwal Harian\n");
        printf("9. Lihat Jadwal Berdasarkan ID Dokter\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf(" %c", &input);

        switch (input) {
            case '1':
                tambah_dokter(&data_dokter, &size);
                break;

            case '2':
                hapus_dokter(&data_dokter, &size);
                break;

            case '3':
                for (int i = 0; i < 4; i++) {
                    printf("%s ", keterangan_csv[i]);
                }
                printf("\n");
                print_dokter(data_dokter);
                break;

            case '4':
                ubah_dokter(data_dokter);
                break;

            case '5':
                printf("\nMembuat jadwal bulanan...\n");
                jadwal_bulanan = buat_jadwal_hari(data_dokter);
                printf("Jadwal berhasil dibuat.\n");
                break;

            case '6':
                if (jadwal_bulanan)
                    showScheduleByMonth(jadwal_bulanan);
                else
                    printf("Belum ada jadwal. Silakan buat dulu (menu 5).\n");
                break;

            case '7': {
                if (!jadwal_bulanan) {
                    printf("Belum ada jadwal. Silakan buat dulu (menu 5).\n");
                    break;
                }
                int minggu;
                printf("Masukkan minggu ke-: ");
                scanf("%d", &minggu);
                showScheduleByWeek(jadwal_bulanan, minggu);
                break;
            }

            case '8': {
                if (!jadwal_bulanan) {
                    printf("Belum ada jadwal. Silakan buat dulu (menu 5).\n");
                    break;
                }
                int minggu, hari;
                printf("Masukkan minggu ke-: ");
                scanf("%d", &minggu);
                printf("Masukkan hari ke-: ");
                scanf("%d", &hari);
                showScheduleByDay(jadwal_bulanan, minggu, hari);
                break;
            }

            case '9': {
                if (!jadwal_bulanan) {
                    printf("Belum ada jadwal. Silakan buat dulu (menu 5).\n");
                    break;
                }
                int id, pilih;
                printf("Masukkan ID dokter: ");
                scanf("%d", &id);
                printf("1. Lihat sebulan penuh\n");
                printf("2. Lihat minggu tertentu\n");
                printf("3. Lihat hari tertentu\n");
                printf("Pilihan: ");
                scanf("%d", &pilih);
                if (pilih == 1) {
                    showSpesificByMonth(jadwal_bulanan, id);
                } else if (pilih == 2) {
                    int minggu;
                    printf("Minggu ke-: ");
                    scanf("%d", &minggu);
                    showSpesificByWeek(jadwal_bulanan, id, minggu);
                } else if (pilih == 3) {
                    int minggu, hari;
                    printf("Minggu ke-: ");
                    scanf("%d", &minggu);
                    printf("Hari ke-: ");
                    scanf("%d", &hari);
                    showSpesificByDay(jadwal_bulanan, id, minggu, hari);
                } else {
                    printf("Pilihan tidak valid.\n");
                }
                break;
            }

            case '0':
                close_program(data_dokter, keterangan_csv);
                printf("Keluar...\n");
                run = 0;
                break;

            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    }

    return 0;
}
