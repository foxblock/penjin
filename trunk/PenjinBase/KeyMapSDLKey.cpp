#include "KeyMapSDLKey.h"

KeyMapSDLKey::KeyMapSDLKey()
{
    //ctor
    device = DEV_KEYBOARD;
    setDeviceID(0);
    target = SJ_UNMAPPED;
}

KeyMapSDLKey::~KeyMapSDLKey()
{
    //dtor
}

void KeyMapSDLKey::setSDLKey(CRstring k)
{
    if(k == "0")
        key=SDLK_0;
    else if(k == "1")
        key=SDLK_1;
    else if(k == "2")
        key=SDLK_2;
    else if(k == "3")
        key=SDLK_3;
    else if(k == "4")
        key=SDLK_4;
    else if(k == "5")
        key=SDLK_5;
    else if(k == "6")
        key=SDLK_6;
    else if(k == "7")
        key=SDLK_7;
    else if(k == "8")
        key=SDLK_8;
    else if(k == "9")
        key=SDLK_9;
    else if(k == "a" || k == "A")
        key=SDLK_a;
    else if(k == "&")
        key=SDLK_AMPERSAND;
    else if(k == "*")
        key=SDLK_ASTERISK;
    else if(k == "@")
        key=SDLK_AT;
    else if(k == "b" || k == "B")
        key=SDLK_b;
    else if(k == "`")
        key=SDLK_BACKQUOTE;
    else if(k == "\\")
        key=SDLK_BACKSLASH;
    else if(k == "BACKSPACE")
        key=SDLK_BACKSPACE;
    else if(k == "BREAK")
        key=SDLK_BREAK;
    else if(k == "c" || k == "C")
        key=SDLK_c;
    else if(k == "CAPS")
        key=SDLK_CAPSLOCK;
    else if(k == "^")
        key=SDLK_CARET;
    else if(k == "CLEAR")
        key=SDLK_CLEAR;
    else if(k == "COLON")
        key=SDLK_COLON;
    else if(k == "COMMA")
        key=SDLK_COMMA;
    else if(k == "COMPOSE")
        key=SDLK_COMPOSE;
    else if(k == "d" || k == "D")
        key=SDLK_d;
    else if(k == "DELETE")
        key=SDLK_DELETE;
    else if(k == "$")
        key=SDLK_DOLLAR;
    else if(k == "DOWN")
        key=SDLK_DOWN;
    else if(k == "e" || k == "E")
        key=SDLK_e;
    else if(k == "END")
        key=SDLK_END;
    else if(k == "=")
        key=SDLK_EQUALS;
    else if(k == "ESCAPE")
        key=SDLK_ESCAPE;
    else if(k == "�")
        key=SDLK_EURO;
    else if(k == "!")
        key=SDLK_EXCLAIM;
    else if(k == "f" || k == "F")
        key=SDLK_f;
    else if(k == "F1")
        key=SDLK_F1;
    else if(k == "F10")
        key=SDLK_F10;
    else if(k == "F11")
        key=SDLK_F11;
    else if(k == "F12")
        key=SDLK_F12;
    else if(k == "F13")
        key=SDLK_F13;
    else if(k == "F14")
        key=SDLK_F14;
    else if(k == "F15")
        key=SDLK_F15;
    else if(k == "F2")
        key=SDLK_F2;
    else if(k == "F3")
        key=SDLK_F3;
    else if(k == "F4")
        key=SDLK_F4;
    else if(k == "F5")
        key=SDLK_F5;
    else if(k == "F6")
        key=SDLK_F6;
    else if(k == "F7")
        key=SDLK_F7;
    else if(k == "F8")
        key=SDLK_F8;
    else if(k == "F9")
        key=SDLK_F9;
    else if(k == "g" || k == "G")
        key=SDLK_g;
    else if(k == ">")
        key=SDLK_GREATER;
    else if(k == "h" || k == "H")
        key=SDLK_h;
    else if(k == "#")
        key=SDLK_HASH;
    else if(k == "HELP")
        key=SDLK_HELP;
    else if(k == "HOME")
        key=SDLK_HOME;
    else if(k == "i" || k == "I")
        key=SDLK_i;
    else if(k == "INSERT")
        key=SDLK_INSERT;
    else if(k == "j" || k == "J")
        key=SDLK_j;
    else if(k == "k" || k == "K")
        key=SDLK_k;
    else if(k == "KP_0")
        key=SDLK_KP0;
    else if(k == "KP_1")
        key=SDLK_KP1;
    else if(k == "KP_2")
        key=SDLK_KP2;
    else if(k == "KP_3")
        key=SDLK_KP3;
    else if(k == "KP_4")
        key=SDLK_KP4;
    else if(k == "KP_5")
        key=SDLK_KP5;
    else if(k == "KP_6")
        key=SDLK_KP6;
    else if(k == "KP_7")
        key=SDLK_KP7;
    else if(k == "KP_8")
        key=SDLK_KP8;
    else if(k == "KP_9")
        key=SDLK_KP9;
    else if(k == "KP_/")
        key=SDLK_KP_DIVIDE;
    else if(k == "KP_ENTER")
        key=SDLK_KP_ENTER;
    else if(k == "KP_=")
        key=SDLK_KP_EQUALS;
    else if(k == "KP_-")
        key=SDLK_KP_MINUS;
    else if(k == "KP_*")
        key=SDLK_KP_MULTIPLY;
    else if(k == "KP_.")
        key=SDLK_KP_PERIOD;
    else if(k == "KP_+")
        key=SDLK_KP_PLUS;
    else if(k == "l" || k == "L")
        key=SDLK_l;
    else if(k == "LEFT_ALT")
        key=SDLK_LALT;
    else if(k == "LEFT_CTRL")
        key=SDLK_LCTRL;
    else if(k == "LEFT")
        key=SDLK_LEFT;
    else if(k == "[")
        key=SDLK_LEFTBRACKET;
    else if(k == "(")
        key=SDLK_LEFTPAREN;
    else if(k == "<")
        key=SDLK_LESS;
    else if(k == "LEFT_META")
        key=SDLK_LMETA;
    else if(k == "LEFT_SHIFT")
        key=SDLK_LSHIFT;
    else if(k == "m" || k == "M")
        key=SDLK_m;
    else if(k == "MENU")
        key=SDLK_MENU;
    else if(k == "-")
        key=SDLK_MINUS;
    else if(k == "MODE")
        key=SDLK_MODE;
    else if(k == "n" || k == "N")
        key=SDLK_n;
    else if(k == "NUMLOCK")
        key=SDLK_NUMLOCK;
    else if(k == "o" || k == "O")
        key=SDLK_o;
    else if(k == "p" || k == "P")
        key=SDLK_p;
    else if(k == "PAGEDOWN")
        key=SDLK_PAGEDOWN;
    else if(k == "PAGEUP")
        key=SDLK_PAGEUP;
    else if(k == "PAUSE")
        key=SDLK_PAUSE;
    else if(k == ".")
        key=SDLK_PERIOD;
    else if(k == "+")
        key=SDLK_PLUS;
    else if(k == "POWER")
        key=SDLK_POWER;
    else if(k == "PRINT")
        key=SDLK_PRINT;
    else if(k == "q" || k == "Q")
        key=SDLK_q;
    else if(k == "?")
        key=SDLK_QUESTION;
    else if(k == "'")
        key=SDLK_QUOTE;
    else if(k == "\"")
        key=SDLK_QUOTEDBL;
    else if(k == "r" || k == "R")
        key=SDLK_r;
    else if(k == "RIGHT_ALT")
        key=SDLK_RALT;
    else if(k == "RIGHT_CTRL")
        key=SDLK_RCTRL;
    else if(k == "RETURN")
        key=SDLK_RETURN;
    else if(k == "RIGHT")
        key=SDLK_RIGHT;
    else if(k == "]")
        key=SDLK_RIGHTBRACKET;
    else if(k == ")")
        key=SDLK_RIGHTPAREN;
    else if(k == "RIGHT_META")
        key=SDLK_RMETA;
    else if(k == "RIGHT_SHIFT")
        key=SDLK_RSHIFT;
    else if(k == "s" || k == "S")
        key=SDLK_s;
    else if(k == "SCROLL_LOCK")
        key=SDLK_SCROLLOCK;
    else if(k == "SEMICOLON")
        key=SDLK_SEMICOLON;
    else if(k == "/")
        key=SDLK_SLASH;
    else if(k == "SPACE")
        key=SDLK_SPACE;
    else if(k == "SYSTEM_REQUEST")
        key=SDLK_SYSREQ;
    else if(k == "t" || k == "T")
        key=SDLK_t;
    else if(k == "TAB")
        key=SDLK_TAB;
    else if(k == "u" || k == "U")
        key=SDLK_u;
    else if(k == "_")
        key=SDLK_UNDERSCORE;
    else if(k == "UNDO")
        key=SDLK_UNDO;
    else if(k == "UP")
        key=SDLK_UP;
    else if(k == "v" || k == "V")
        key=SDLK_v;
    else if(k == "w" || k == "W")
        key=SDLK_w;
    else if(k == "x" || k == "X")
        key=SDLK_x;
    else if(k == "y" || k == "Y")
        key=SDLK_y;
    else if(k == "z" || k == "Z")
        key=SDLK_z;
    else
        key=SDLK_UNKNOWN;
}
