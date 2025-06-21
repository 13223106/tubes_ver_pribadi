#include "data.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>     // untuk malloc, calloc, free
#include <string.h>     // untuk strcmp, strlen, strcpy

int cekAnak(Dokter* dokterAnak){
    return (strcmp(dokterAnak->spesialisasi, "Anak") == 0);
}

int cekUmum(Dokter* dokterUmum){
    return (strcmp(dokterUmum->spesialisasi, "Umum") == 0);
}

int cekBedah(Dokter* dokterBedah){
    return (strcmp(dokterBedah->spesialisasi, "Bedah") == 0);
}

int cekPreferensi(Dokter* dokterPreferensi, const char* shift){
     return (strcmp(dokterPreferensi->preference, shift) == 0);
}

int cekShiftSisa(Dokter* dokterUtama){
    return (dokterUtama -> max_shift > 0);
}

int sudahAmbilShift(Dokter* dokterUtama, int arrayIDShift[10]){
    for(int i = 0; i <= 9; i++){
        if(dokterUtama -> id == arrayIDShift[i]){
            return 1;
        } 
    }
    return 0;
}


int hitung_jumlah_dokter(Dokter* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Fungsi untuk mendapatkan jumlah shift awal dan mengembalikan array
int* get_max_shift_array(Dokter* dokter, int* jumlah_dokter) {
    *jumlah_dokter = hitung_jumlah_dokter(dokter);
    int* max_shift_awal = (int*)malloc(*jumlah_dokter * sizeof(int));
    
    Dokter* current = dokter;
    int i = 0;
    while(current != NULL) {
        max_shift_awal[i] = current->max_shift;
        current = current->next;
        i++;
    }
    
    return max_shift_awal;
}

void reset_shift(Dokter* head, int* shift_awal, int jumlah_dokter) {
    Dokter* curr = head;
    int i = 0;

    while (curr != NULL && i < jumlah_dokter) {
        curr->max_shift = shift_awal[i];
        curr = curr->next;
        i++;
    }
}



Dokter* salin_dokterSementara(Dokter** dokterHeadSementara, Dokter** dokterTailSementara, Dokter* dokterUtama) {
    if (!dokterUtama) return NULL;  // Handle input NULL

    Dokter* dokterSementara = (Dokter*)malloc(sizeof(Dokter));
    if (!dokterSementara) return NULL;  // Handle malloc gagal

    // Initialize with default values
    memset(dokterSementara, 0, sizeof(Dokter));

    // Salin nama
    dokterSementara->nama = (char*)malloc(strlen(dokterUtama->nama) + 1);
    if (!dokterSementara->nama) goto error;
    strcpy(dokterSementara->nama, dokterUtama->nama);

    // Salin spesialisasi
    dokterSementara->spesialisasi = (char*)malloc(strlen(dokterUtama->spesialisasi) + 1);
    if (!dokterSementara->spesialisasi) goto error;
    strcpy(dokterSementara->spesialisasi, dokterUtama->spesialisasi);

    // Salin preference
    dokterSementara->preference = (char*)malloc(strlen(dokterUtama->preference) + 1);
    if (!dokterSementara->preference) goto error;
    strcpy(dokterSementara->preference, dokterUtama->preference);

    if (*dokterHeadSementara == NULL) {
        // List masih kosong
        *dokterHeadSementara = dokterSementara;
        *dokterTailSementara = dokterSementara;
    } else {
        // List sudah ada, sambung ke tail
        (*dokterTailSementara)->next = dokterSementara;
        *dokterTailSementara = dokterSementara;
    }
    return dokterSementara;

error:
    // Bebaskan semua memori yang sudah dialokasikan
    free(dokterSementara->nama);
    free(dokterSementara->spesialisasi);
    free(dokterSementara->preference);
    free(dokterSementara);
    return NULL;
}

Jadwal* salin_dokter_ke_jadwal(Jadwal** head_jadwal, Jadwal** tail_jadwal, int i, const char* shift, Dokter* dokterSementara){
    // Buat struct node baru
    Jadwal* rencana = (Jadwal*)malloc(sizeof(Jadwal));

    // Masukkan parameter fungsi ke struct
    rencana -> hari_ke = i;
    rencana -> shift = (char*)malloc(strlen(shift) + 1);
    rencana -> next = NULL;
    strcpy(rencana->shift, shift);

    int d = 0;
    memset(rencana -> daftar_dokter, 0, sizeof(rencana -> daftar_dokter));

    while (dokterSementara != NULL && d < 10) {
        rencana->daftar_dokter[d] = dokterSementara;
        dokterSementara = dokterSementara->next;
        d++;
}



    if (*head_jadwal == NULL) {
        // List masih kosong
        *head_jadwal = rencana;
        *tail_jadwal = rencana;
    } else {
        // List sudah ada, sambung ke tail
        (*tail_jadwal)->next = rencana;
        *tail_jadwal = rencana;
    }
    return rencana;
}


Jadwal* buat_jadwal_hari(Dokter* dokter){
    int i, d, j;
    int bulan = 9;
    int tahun = 2025;
    int tanggal_bulan = bulan - 1;
    int total_hari = 30;
    struct tm tanggal = {0};

    Dokter* head = dokter;
    Dokter* dokterUtama = dokter;

    Jadwal* head_jadwal = NULL;
    Jadwal* tail_jadwal = NULL;

    // Hitung jumlah dokter dan shift maksimal tiap dokter
    int jumlah_dokter = hitung_jumlah_dokter(head);
    int* shift_awal = get_max_shift_array(head, &jumlah_dokter);

    for(i = 1; i <= total_hari; i++){
        tanggal.tm_mday = i;
        tanggal.tm_mon = tanggal_bulan;
        tanggal.tm_year = tahun - 1900;
        mktime(&tanggal); //tanggal.tm_wday

        // Kondisi tiap 1 minggu (reset shift maksimal masing-masing dokter)
        if((i-1) % 7 == 0){
            reset_shift(head, shift_awal, jumlah_dokter); 
        }

        for(j = 0; j <= 2; j++){
            int pilih;
            const char* shift_dokter;
            int shift_sisa_pelanggaran;
            Dokter* dokterHeadSementara = NULL;
            Dokter* dokterTailSementara = NULL;

            int idDokterTersedia = 0;
            int arrayIDSHift[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            if(j == 0){
                shift_dokter = "Pagi";
            }
            
            else if(j == 1){
                shift_dokter = "Siang";
            }
            
            else if(j == 2){
                shift_dokter = "Malam";
            }

            for(d = 0; d < 10; d++){
                pilih = 0;
                dokterUtama = head;
                if(d == 0){ // Ambil Dokter Anak
                    while(dokterUtama != NULL){
                        if(cekAnak(dokterUtama) && cekPreferensi(dokterUtama, shift_dokter) && cekShiftSisa(dokterUtama)){
                            // Masukin ke struct dokter pakai fungsi nashwa
                            salin_dokterSementara(&dokterHeadSementara, &dokterTailSementara, dokterUtama);
                            pilih = 1;
                            dokterUtama -> max_shift -= 1;
                            arrayIDSHift[idDokterTersedia++] = dokterUtama -> id;
                            dokterUtama = dokterUtama -> next;
                            break;
                        }
                        else{ // Dokter di node selanjutnya
                            dokterUtama = dokterUtama -> next;
                        }
                    }
                }
                else if(d == 1){ // Ambil Dokter Umum
                    while(dokterUtama != NULL){
                        if(cekUmum(dokterUtama) && cekPreferensi(dokterUtama, shift_dokter) && cekShiftSisa(dokterUtama)){
                            // Masukin ke struct dokter pakai fungsi nashwa
                            salin_dokterSementara(&dokterHeadSementara, &dokterTailSementara, dokterUtama);
                            pilih = 1;
                            dokterUtama -> max_shift -= 1;
                            arrayIDSHift[idDokterTersedia++] = dokterUtama -> id;
                            dokterUtama = dokterUtama -> next;
                            break;
                        }
                        else{ // Dokter di node selanjutnya
                            dokterUtama = dokterUtama -> next;
                        }
                    }
                }
                else if(d == 2){ // Ambil Dokter Bedah
                    while(dokterUtama != NULL){
                        if(cekBedah(dokterUtama) && cekPreferensi(dokterUtama, shift_dokter) && cekShiftSisa(dokterUtama)){
                            // Masukin ke struct dokter pakai fungsi nashwa
                            salin_dokterSementara(&dokterHeadSementara, &dokterTailSementara, dokterUtama);
                            pilih = 1;
                            dokterUtama -> max_shift -= 1;
                            arrayIDSHift[idDokterTersedia++] = dokterUtama -> id;
                            dokterUtama = dokterUtama -> next;
                            break;
                        }
                        else{ // Dokter di node selanjutnya
                            dokterUtama = dokterUtama -> next;
                        }
                    }
                }
                else{ // Ambil Dokter Bebas Spesialisasi, mementingkan max shift, preferensi, dan sudah masuk atau belum
                    while(dokterUtama != NULL){
                        if(!sudahAmbilShift(dokterUtama, arrayIDSHift) && cekPreferensi(dokterUtama, shift_dokter) && cekShiftSisa(dokterUtama)){
                            // Masukin ke struct dokter pakai fungsi nashwa
                            salin_dokterSementara(&dokterHeadSementara, &dokterTailSementara, dokterUtama);
                            pilih = 1;
                            dokterUtama -> max_shift -= 1;
                            arrayIDSHift[idDokterTersedia++] = dokterUtama -> id;
                            dokterUtama = dokterUtama -> next;
                            break;
                        }
                        else{ // Dokter di node selanjutnya
                            dokterUtama = dokterUtama -> next;
                        }
                    }
                }

                if(pilih == 0){
                    shift_sisa_pelanggaran = 10 - (d+1);
                    dokterUtama = head;
                    break;
                }
            }
            if((pilih == 0)){
                    int k;
                    for(k = 0; k <= shift_sisa_pelanggaran; k++){
                        if(k == 0){ // Ambil Dokter Anak
                            while(dokterUtama != NULL){
                                if(cekAnak(dokterUtama) && !sudahAmbilShift(dokterUtama, arrayIDSHift)){
                                    // Masukin ke struct dokter pakai fungsi nashwa
                                    salin_dokterSementara(&dokterHeadSementara, &dokterTailSementara, dokterUtama);
                                    pilih = 1;
                                    dokterUtama -> max_shift -= 1;
                                    arrayIDSHift[idDokterTersedia++] = dokterUtama -> id;
                                    dokterUtama = dokterUtama -> next;
                                    break;
                                }
                                else{ // Dokter di node selanjutnya
                                    dokterUtama = dokterUtama -> next;
                                }
                            }
                        }
                        else if(k == 1){ // Ambil Dokter Umum
                            while(dokterUtama != NULL){
                                if(cekUmum(dokterUtama) && !sudahAmbilShift(dokterUtama, arrayIDSHift)){
                                    // Masukin ke struct dokter pakai fungsi nashwa
                                    salin_dokterSementara(&dokterHeadSementara, &dokterTailSementara, dokterUtama);
                                    pilih = 1;
                                    dokterUtama -> max_shift -= 1;
                                    arrayIDSHift[idDokterTersedia++] = dokterUtama -> id;
                                    dokterUtama = dokterUtama -> next;
                                    break;
                                }
                                else{ // Dokter di node selanjutnya
                                    dokterUtama = dokterUtama -> next;
                                }
                            }
                        }
                        else if(k == 2){ // Ambil Dokter Bedah
                            while(dokterUtama != NULL){
                                if(cekBedah(dokterUtama) && !sudahAmbilShift(dokterUtama, arrayIDSHift)){
                                    // Masukin ke struct dokter pakai fungsi nashwa
                                    salin_dokterSementara(&dokterHeadSementara, &dokterTailSementara, dokterUtama);
                                    pilih = 1;
                                    dokterUtama -> max_shift -= 1;
                                    arrayIDSHift[idDokterTersedia++] = dokterUtama -> id;
                                    dokterUtama = dokterUtama -> next;
                                    break;
                                }
                                else{ // Dokter di node selanjutnya
                                    dokterUtama = dokterUtama -> next;
                                }
                            }
                        }
                        else{ // Ambil Dokter Bebas Spesialisasi, mementingkan max shift, preferensi, dan sudah masuk atau belum
                            while(dokterUtama != NULL){
                                if(!sudahAmbilShift(dokterUtama, arrayIDSHift)){
                                    // Masukin ke struct dokter pakai fungsi nashwa
                                    salin_dokterSementara(&dokterHeadSementara, &dokterTailSementara, dokterUtama);
                                    pilih = 1;
                                    dokterUtama -> max_shift -= 1;
                                    arrayIDSHift[idDokterTersedia++] = dokterUtama -> id;
                                    dokterUtama = dokterUtama -> next;
                                    break;
                                }
                                else{ // Dokter di node selanjutnya
                                    dokterUtama = dokterUtama -> next;
                                }
                            }
                        }
                    }
                }
            salin_dokter_ke_jadwal(&head_jadwal, &tail_jadwal, i, shift_dokter, dokterHeadSementara);

        }
    }
    return head_jadwal;
}