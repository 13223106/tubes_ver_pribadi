#ifndef DATA
#define DATA

typedef struct Dokter {
    int id;
    char* nama;
    char* spesialisasi;
    int max_shift;
    char* preference;
    int pelanggaran;
    struct Dokter* next;
} Dokter;

typedef struct Jadwal {
    int hari_ke;
    char* shift;
    Dokter* daftar_dokter[10];
    struct Jadwal* next;
} Jadwal;

#endif