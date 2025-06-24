#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

// include kode pembagian jadwal
//include

// Constants
#define ADMIN_PASSKEY 1456
#define MAX_DOCTORS 10

// Doctor database -> nanti pake nya yg udah linked list dari hanif
//int doctorIDs[MAX_DOCTORS] = {1001, 1002, 1003, 1004, 1005};
//int numDoctors = 5;

// Function 
void adminMenu();
void doctorMenu(int doctorID);

int main() {
    int choice;
    
    do {
        clearScreen();
        
        // Main menu
        printf("\n========== SISTEM JADWAL DOKTER ==========\n");
        printf("Pilih masuk sebagai:\n");
        printf("1. Admin\n");
        printf("2. Dokter\n");
        printf("3. Keluar\n");
        printf("==========================================\n");
        
        printf("Pilih menu (1-3): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: {
                // Admin authentication
                int passkey, attempts = 0;
                do {
                    printf("\nMasukkan passkey: ");
                    scanf("%d", &passkey);
                    
                    if(passkey == ADMIN_PASSKEY) {
                        adminMenu();
                        break;
                    } else {
                        attempts++;
                        printf("Passkey salah! (%d percobaan tersisa)\n", 3-attempts);
                    }
                } while(attempts < 3);
                
                if(attempts >= 3) {
                    printf("Terlalu banyak percobaan gagal.\n");
                    printf("Tekan Enter untuk kembali...");
                    while(getchar() != '\n');
                    getchar();
                }
                break;
            }
            case 2: {
                // Doctor authentication
                int doctorID, found = 0;
                printf("\nMasukkan ID Dokter: ");
                scanf("%d", &doctorID);
                
                // Check if ID exists
                for(int i = 0; i < numDoctors; i++) {
                    if(doctorIDs[i] == doctorID) {
                        found = 1;
                        doctorMenu(doctorID);
                        break;
                    }
                }
                
                if(!found) {
                    printf("ID Dokter tidak ditemukan!\n");
                    printf("Tekan Enter untuk kembali...");
                    while(getchar() != '\n');
                    getchar();
                }
                break;
            }
            case 3:
                printf("\nTerima kasih telah menggunakan sistem ini.\n");
                break;
            default:
                printf("\nPilihan tidak valid!\n");
                printf("Tekan Enter untuk melanjutkan...");
                while(getchar() != '\n');
                getchar();
        }
    } while(choice != 3);
    
    return 0;
}


void adminMenu() {
    int choice;
    
    do {
        clearScreen();
        printf("\n========== MENU ADMIN ==========\n");
        printf("1. Tambah Dokter\n");
        printf("2. Hapus Dokter\n");
        printf("3. Lihat Jadwal\n");
        printf("4. Kembali ke Menu Utama\n");
        printf("===============================\n");
        
        printf("Pilih menu (1-4): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if(numDoctors < MAX_DOCTORS) {
                    printf("\nMasukkan ID Dokter baru: ");
                    scanf("%d", &doctorIDs[numDoctors]);
                    numDoctors++;
                    printf("Dokter berhasil ditambahkan!\n");
                } else {
                    printf("\nDatabase dokter penuh!\n");
                }
                break;
            case 2:
                printf("\nMasukkan ID Dokter yang akan dihapus: ");
                int idToRemove;
                scanf("%d", &idToRemove);
                
                int found = 0;
                for(int i = 0; i < numDoctors; i++) {
                    if(doctorIDs[i] == idToRemove) {
                        // Shift elements to remove the doctor
                        for(int j = i; j < numDoctors-1; j++) {
                            doctorIDs[j] = doctorIDs[j+1];
                        }
                        numDoctors--;
                        found = 1;
                        printf("Dokter berhasil dihapus!\n");
                        break;
                    }
                }
                
                if(!found) {
                    printf("ID Dokter tidak ditemukan!\n");
                }
                break;
            case 3:
                printf("\n=== DAFTAR JADWAL DOKTER ===\n");
                for(int i = 0; i < numDoctors; i++) {
                    printf("Dokter ID: %d - Jadwal: Senin-Jumat 08:00-16:00\n", doctorIDs[i]);
                }
                break;
            case 4:
                return;
            default:
                printf("\nPilihan tidak valid!\n");
        }
        
        printf("\nTekan Enter untuk melanjutkan...");
        while(getchar() != '\n');
        getchar();
    } while(1);
}

void doctorMenu(int doctorID) {
    int choice;
    
    do {
        clearScreen();
        printf("\n========== MENU DOKTER (ID: %d) ==========\n", doctorID);
        printf("1. Tampilkan Jadwal Bulanan\n");
        printf("2. Tampilkan Jadwal Mingguan\n");
        printf("3. Tampilkan Jadwal Harian\n");
        printf("4. Kembali ke Menu Utama\n");
        printf("=========================================\n");
        
        printf("Pilih menu (1-4): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("\n=== JADWAL BULANAN ===\n");
                break;
            case 2:
                printf("\n=== JADWAL MINGGUAN ===\n");
                printf("Masukkan minggu);
                break;
            case 3:
                printf("\n=== JADWAL HARIAN ===\n");
                printf("masukkan minggu dan hari");
                break;
            case 4:
                return;
            default:
                printf("\nPilihan tidak valid!\n");
        }
        
        printf("\nTekan Enter untuk melanjutkan...");
        while(getchar() != '\n');
        getchar();
    } while(1);
}
