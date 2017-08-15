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


int layout[N_ROWS * N_COLS];

int main(void) {
    setup_io();
    init_layout(layout, N_ROWS, N_COLS);
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

void set_pin(char port_chr, int bit, int val) {
    if (port_chr == 'A') {
        _set_bit(PORTA, bit, val);
    } else if (port_chr == 'B') {
        _set_bit(PORTB, bit, val);
    } else if (port_chr == 'C') {
        _set_bit(PORTC, bit, val);
    } else if (port_chr == 'D') {
        _set_bit(PORTD, bit, val);
    } else if (port_chr == 'E') {
        _set_bit(PORTE, bit, val);
    } else if (port_chr == 'F') {
        _set_bit(PORTF, bit, val);
    }
}

bool read_pin(char port_chr, int bit) {
    uint8_t p = 0;
    if (port_chr == 'A') {
        p = PINA;
    } else if (port_chr == 'B') {
        p = PINB;
    } else if (port_chr == 'C') {
        p = PINC;
    } else if (port_chr == 'D') {
        p = PIND;
    } else if (port_chr == 'E') {
        p = PINE;
    } else if (port_chr == 'F') {
        p = PINF;
    }

    return ((p >> bit) & 1) == 1;
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

    USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;


    int hits = 0;
    // scan matrix
    for (int row = 0; row < N_ROWS; row++) {
        char row_port = MATRIX_ROW_PORTS[row];
        int row_bit   = MATRIX_ROW_BITS[row];
        set_pin(row_port, row_bit, 1);

        for (int col = 0; col < N_COLS; col++) {
            char col_port = MATRIX_COL_PORTS[col];
            int col_bit   = MATRIX_COL_BITS[col];

            if (read_pin(col_port, col_bit)) {
                int idx = row*N_ROWS + col;
                int scancode = layout[idx];
                if (scancode == -1)
                    continue; // not registered

                KeyboardReport->KeyCode[hits] = scancode;
                hits++;
            }

            if (hits == 6)
                break;
        }
        set_pin(row_port, row_bit, 0);

        if (hits == 6)
            break;
    }

    *ReportSize = sizeof(USB_KeyboardReport_Data_t);
    return false;
}
