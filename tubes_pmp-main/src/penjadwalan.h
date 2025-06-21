#ifndef PENJADWALAN_H
#define PENJADWALAN_H

#include "data.h"


// Fungsi pengecekan spesialisasi
int cekAnak(Dokter* dokterAnak);
int cekUmum(Dokter* dokterUmum);
int cekBedah(Dokter* dokterBedah);

// Fungsi pengecekan preferensi shift dan jumlah shift tersisa
int cekPreferensi(Dokter* dokterPreferensi, const char* shift);
int cekShiftSisa(Dokter* dokterUtama);
int sudahAmbilShift(Dokter* dokterUtama, int arrayIDShift[10]);

// Fungsi utilitas jumlah dokter dan array shift awal
int hitung_jumlah_dokter(Dokter* head);
int* get_max_shift_array(Dokter* dokter, int* jumlah_dokter);

// Reset shift dokter ke nilai awal
void reset_shift(Dokter* dokterUtama, Dokter* dokter);

// Salin data dokter ke dalam struct Jadwal
void salin_dokter_ke_jadwal(Jadwal* rencana, int d, Dokter* dokterUtama, Dokter* dokter_head);

// Fungsi utama untuk membuat penjadwalan selama 30 hari
Jadwal* buat_jadwal_hari(Dokter* dokter);

#endif // PENJADWALAN_H