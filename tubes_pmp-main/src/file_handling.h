#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include "data.h" // ⬅ wajib, biar 'Dokter' dikenali

void read_file(const char* file_name, Dokter** data_dokter_h, Dokter** data_dokter_t, int* size, char*** header_csv);
void overwrite_file(const char* file_name, Dokter* data_dokter, char** header_csv);
void close_program(Dokter* data_dokter, char** keterangan_csv);
Dokter* baca_data_dokter(const char* file_path); // ⬅ tambahkan ini kalau kamu punya fungsi ini di .c-nya

#endif
