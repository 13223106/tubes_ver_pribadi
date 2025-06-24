#ifndef UTILITY
#define UTILITY

void str_to_lower(char* str);

void clear_terminal();

void free_list_of_strings(char** str, int size);

void free_dokter(Dokter* dokter);

void free_all_dokter(Dokter* data_dokter);

Dokter* cari_id(int id, Dokter* data_dokter);

Dokter* cari_id_alamat_sebelumnya(int id, Dokter* data_dokter, Dokter** alamat_sebelumnya);

#endif