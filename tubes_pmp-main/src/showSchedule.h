#ifndef SHOW_SCHEDULE
#define SHOW_SCHEDULE
#include "data.h"

const char* getNamaHari(int hari_ke);

void showSchedule(Jadwal* head, int minggu_input);

void showScheduleByMonth(Jadwal* head);
void showScheduleByWeek(Jadwal* head, int minggu_ke);
void showScheduleByDay(Jadwal* head, int minggu_ke, int hari_ke);

void showScheduleSpesific(Jadwal* head, const char* nama_dokter, int minggu_input);

void showSpesificByMonth(Jadwal* head, int id_dokter);
void showSpesificByWeek(Jadwal* head, int id_dokter, int minggu_ke);
void showSpesificByDay(Jadwal* head, int id_dokter, int minggu_ke, int hari_ke);

#endif