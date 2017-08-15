#include <stdbool.h>
#include <inttypes.h>

#define N_COLS 14
#define N_ROWS 5

#define _set_bit(__port, __bit, __mode) \
    if (__mode==1) { __port |= (1<<__bit); } \
    else { __port &= ~(1<<__bit); }

char MATRIX_COL_PORTS[N_COLS] = {
    'C', 'B', 'E', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'B'
};

int MATRIX_COL_BITS[N_COLS] = {
    6, 6, 6, 0, 7, 0, 1, 2, 3, 5, 4, 6, 7, 5
};

char MATRIX_ROW_PORTS[N_ROWS] = {
    'C', 'B', 'B', 'B', 'B'
};

int MATRIX_ROW_BITS[N_ROWS] = {
    7, 1, 2, 3, 5
};

void set_io_mode(char port_chr, int bit, int mode);
void set_pin(char port_chr, int bit, int val);
bool read_pin(char port_chr, int bit);

void setup_io(void);

bool scan_matrix(int row, int col);

void init_layout(int *layout, int rows, int cols);

bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize);


