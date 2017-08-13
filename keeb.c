#include <avr/io.h>
#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>
#include "Descriptors.h"

#include "keeb.h"

static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

USB_ClassInfo_HID_Device_t Keyboard_HID_Interface =
    {
        .Config =
            {
                .InterfaceNumber              = INTERFACE_ID_Keyboard,
                .ReportINEndpoint             =
                    {
                        .Address              = KEYBOARD_EPADDR,
                        .Size                 = KEYBOARD_EPSIZE,
                        .Banks                = 1,
                    },
                .PrevReportINBuffer           = PrevKeyboardHIDReportBuffer,
                .PrevReportINBufferSize       = sizeof(PrevKeyboardHIDReportBuffer),
            },
    };




int main(void) {
    setup_io();
    GlobalInterruptEnable();

    while (true) {
        HID_Device_USBTask(&Keyboard_HID_Interface);
        USB_USBTask();
    }
    
    return 0;
}

void set_io_mode(char port_chr, int bit, int mode) {
    if (port_chr == 'A') {
        _set_bit(DDRA, bit, mode);
    } else if (port_chr == 'B') {
        _set_bit(DDRB, bit, mode);
    } else if (port_chr == 'C') {
        _set_bit(DDRC, bit, mode);
    } else if (port_chr == 'D') {
        _set_bit(DDRD, bit, mode);
    } else if (port_chr == 'E') {
        _set_bit(DDRE, bit, mode);
    } else if (port_chr == 'F') {
        _set_bit(DDRF, bit, mode);
    }
}

bool scan_matrix(int row, int col) {
    // todo
}

void setup_io(void) {
    for (int i = 0; i < N_COLS; i++) {
        // set cols to input
        set_io_mode(MATRIX_COL_PORTS[i], MATRIX_COL_BITS[i], 0);
    }

    for (int i = 0; i < N_ROWS; i++) {
        // set rows to output
        set_io_mode(MATRIX_ROW_PORTS[i], MATRIX_ROW_BITS[i], 1);
    }
}

bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize) {


    
    // todo
    return false;
}
