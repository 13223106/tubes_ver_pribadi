#ifndef PENJADWALAN_H
#define PENJADWALAN_H

#include "data.h"  // Asumsinya struktur Dokter dan Jadwal didefinisikan di sini

// Fungsi pengecekan spesialisasi
int cekAnak(Dokter* dokterAnak);
int cekUmum(Dokter* dokterUmum);
int cekBedah(Dokter* dokterBedah);

// Fungsi pengecekan preferensi shift dan ketersediaan
int cekPreferensi(Dokter* dokterPreferensi, const char* shift);
int cekShiftSisa(Dokter* dokterUtama);
int sudahAmbilShift(Dokter* dokterUtama, int arrayIDShift[10]);

// Fungsi manajemen data dokter
int hitung_jumlah_dokter(Dokter* head);
int* get_max_shift_array(Dokter* dokter, int* jumlah_dokter);
void reset_shift(Dokter* head, int* shift_awal, int jumlah_dokter);

// Fungsi utilitas
void inisialisasiPelanggaranShift(Dokter* dokterUtama);

// Fungsi untuk menyalin data dokter sementara
Dokter* salin_dokterSementara(Dokter** dokterHeadSementara, 
                              Dokter** dokterTailSementara, 
                              Dokter* dokterUtama);

// Fungsi untuk menyusun jadwal shift harian
Jadwal* salin_dokter_ke_jadwal(Jadwal** head_jadwal, 
                               Jadwal** tail_jadwal, 
                               int hari_ke, 
                               const char* shift, 
                               Dokter* dokterSementara);

// RNG untuk memilih dokter secara acak
int rng_dokter_acak(int jumlahDokter);

// Fungsi utama penjadwalan bulanan
Jadwal* buat_jadwal_hari(Dokter* dokter);

#endif // PENJADWALAN_H