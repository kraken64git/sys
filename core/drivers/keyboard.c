#include "drivers/keyboard.h"

static BOOL capsLock = FALSE;
static BOOL shiftPressed = FALSE;
char ch = 0, scanCode = 0;

char keymap[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
};

static int getScanCode()
{
    int i, code = 0;
    for (i = 1000; i > 0; i++) {
        if ((inportb(KEYBOARD_STATUS_PORT) & 1) == 0) continue;

        code = inportb(KEYBOARD_DATA_PORT);
        break;
    } if (i > 0)
        return code;
    return 0;
}

char alternateChars(char ch)
{
    switch(ch) {
        case '`': return '~';
        case '1': return '!';
        case '2': return '@';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '^';
        case '7': return '&';
        case '8': return '*';
        case '9': return '(';
        case '0': return ')';
        case '-': return '_';
        case '=': return '+';
        case '[': return '{';
        case ']': return '}';
        case '\\': return '|';
        case ';': return ':';
        case '\'': return '\"';
        case ',': return '<';
        case '.': return '>';
        case '/': return '?';
        default: return ch;
    }
}

void kbHandler(REGISTERS_t *r)
{
    int code;

    ch = 0;
    code = getScanCode();
    scanCode = code;
    if (code & 0x80);
    else {
        switch(code) {
            case SCAN_CODE_KEY_CAPS_LOCK:
                if (capsLock == FALSE)
                    capsLock = TRUE;
                else
                    capsLock = FALSE;
                break;
            case SCAN_CODE_KEY_ENTER:
                ch = '\n';
                break;
            case SCAN_CODE_KEY_TAB:
                ch = '\t';
                break;
            case SCAN_CODE_KEY_LEFT_SHIFT:
                shiftPressed = TRUE;
                break;

            default:
                ch = keymap[code];

                if (capsLock) {
                    if (shiftPressed)
                        ch = alternateChars(ch);
                    else
                        ch = upper(ch);
                } else {
                    if (shiftPressed)
                        if (isAlpha(ch))
                            ch = upper(ch);
                        else
                            ch = alternateChars(ch);
                    else
                        ch = keymap[code];
                    shiftPressed = FALSE;
                } break;
        }
    }
}

char kbGetChar()
{
    char c;

    while(ch <= 0);
    c = ch;
    ch = 0;
    scanCode = 0;
    return c;
}

char kbGetScanCode()
{
    char code;

    while(scanCode <= 0);
    code = scanCode;
    ch = 0;
    scanCode = 0;
    return code;
}

void InitKeyboard()
{
    isrRegisterInterruptHandler(IRQ_BASE + 1, kbHandler);
}
