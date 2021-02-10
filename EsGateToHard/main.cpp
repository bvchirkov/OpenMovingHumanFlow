/*Copyright (c) 2019 Boris Chirkov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// File created 26.06.2019
//wcalc -b "(256 | 3) & 0xff"

#include "usetty.hpp"
#include <stdint.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Для sleep

void print_byte_as_bits(char val) {
    for (int i = 7; 0 <= i; i--) {
        printf("%c", (val & (1 << i)) ? '1' : '0');
    }
}

void print_bits(unsigned char * bytes, size_t num_bytes) {
    for (size_t i = 0; i < num_bytes; i++) {
        print_byte_as_bits(bytes[i]);
    }
    printf(" ");
}

#define SHOW(T,V) {T x = V; print_bits((unsigned char*) &x, sizeof(x));}

#define STATUS		( 0x00 )
#define SET         ( 0x01 )

#define IDLE		( 0x00 )
#define CMD_OFF		( 0x00 )
#define CMD_LEFT	( 0x01 )
#define CMD_RIGHT	( 0x02 )
#define CMD_STOP	( 0x01 )
#define CMD_GO		( 0x02 )

#define INTERVAL	( 2 )	 //ms

typedef struct Pkg_t
{
    uint8_t     addr;
    uint8_t     cmd;
    uint8_t     data;
    char*       str;
} PKG;

static PKG pkg;

int userCmds();
void autoTests();
void pushCmds(uint8_t*, size_t, PKG*, size_t);

int main(int argc, char** argv)
{
    // ======= MANUAL TEST ======
    userCmds();

    // ======= AUTOTESTS ========
    //autoTests();
    return 0;
}

int userCmds()
{
    UseTTY tty;

    bool res = tty.openPort("/dev/ttyUSB0", B9600);
    if(!res)
    {
        printf("Невозможно открыть COM порт\n");
        return 0;
    }

    uint count = 1;
    uint interval = 0;
    printf("Введите SLAVE_ADDR: ");
    scanf("%u", &pkg.addr);
    printf("Введите CMD: ");
    scanf("%u", &pkg.cmd);

    if (pkg.cmd == 1)
    {
        pkg.str = "SET";

        printf("Введите DATA: ");
        scanf("%u", &pkg.data);
        } else if (pkg.cmd == 0)
        {
        pkg.str = "STATUS";
        pkg.data = 0x00;

        printf("Введите количество повторений команды: ");
        scanf("%u", &count);

        printf("Введите временной интервал между повторами: ");
        scanf("%u", &interval);
        }

        //pkg = {0x01, STATUS, CMD_OFF, "STATUS"};
        //pkg = {0x01, SET, CMD_OFF, "SET, CMD_OFF"};

        for (size_t r = 0; r < count; r++)
        {
        tty.sendData(&pkg.addr, 1);
        tty.sendData(&pkg.cmd,  1);
        tty.sendData(&pkg.data, 1);

        printf("----------------------------------\n");
        SHOW(uint8_t, pkg.addr); SHOW(uint8_t, pkg.cmd); SHOW(uint8_t, pkg.data);
        printf("%s\n", pkg.str);

        u_char rbuff[3];
        size_t i = 0;
        while (i < 3)
        {
            ssize_t s = tty.readData(&rbuff[i], 1);
            if (s < 1)
            {
            printf("Нет ответа\n");
            return 0;
            }
            i++;
        }

        SHOW(uint8_t, rbuff[0]); SHOW(uint8_t, rbuff[1]); SHOW(uint8_t, rbuff[2]);
        printf("\n");
        sleep(interval);
    }

    tty.closeCom();
}

void autoTests()
{
    // Тестирование стрелок (ARW) на включение-выключение:
    uint8_t addrs_arw[2] = {10, 12};
    // Порядок теста:
    //  1. Запрос состояния
    //  2. Включение стрелки вправо
    //  3. Запрос состяния
    //  4. Включение стрелки влево
    //  5. Запрос состяния
    //  6. Выключение стрелки
    //  7. Запрос состояния
    //  8. Включение стрелки вправо
    PKG pkgs_arw[8];
    pkgs_arw[0] = {0x00, STATUS, IDLE,   	"STATUS"};
    pkgs_arw[1] = {0x00, SET,    CMD_RIGHT, "SET CMD_RIGHT"};
    pkgs_arw[2] = {0x00, STATUS, IDLE,   	"STATUS"};
    pkgs_arw[3] = {0x00, SET,    CMD_LEFT,  "SET CMD_LEFT"};
    pkgs_arw[4] = {0x00, STATUS, IDLE,   	"STATUS"};
    pkgs_arw[5] = {0x00, SET,    CMD_OFF,   "SET CMD_OFF"};
    pkgs_arw[6] = {0x00, STATUS, IDLE,   	"STATUS"};
    pkgs_arw[7] = {0x00, SET,    CMD_RIGHT, "SET CMD_RIGHT"};

    pushCmds(addrs_arw, (sizeof addrs_arw/sizeof(uint8_t)), pkgs_arw, ((sizeof pkgs_arw)/sizeof(PKG)));

    // Тестирование светофоров (LHT) на включение-выключение:
    uint8_t addrs_lht[2] = {20, 22};
    // Порядок теста:
    //  1. Запрос состояния
    //  2. Перевод светофора в состояние GO
    //  3. Запрос состяния
    //  4. Перевод светофора в состояние STOP
    //  5. Запрос состяния
    //  6. Выключение светофора
    //  7. Запрос состояния
    //  8. Перевод светофора в состояние GO
    PKG pkgs_lht[8];
    pkgs_lht[0] = {0x00, STATUS, IDLE,   	"STATUS"};
    pkgs_lht[1] = {0x00, SET,    CMD_GO,    "SET CMD_GO"};
    pkgs_lht[2] = {0x00, STATUS, IDLE,   	"STATUS"};
    pkgs_lht[3] = {0x00, SET,    CMD_STOP,  "SET CMD_STOP"};
    pkgs_lht[4] = {0x00, STATUS, IDLE,   	"STATUS"};
    pkgs_lht[5] = {0x00, SET,    CMD_OFF,   "SET CMD_OFF"};
    pkgs_lht[6] = {0x00, STATUS, IDLE,   	"STATUS"};
    pkgs_lht[7] = {0x00, SET,    CMD_GO,    "SET CMD_GO"};

    pushCmds(addrs_lht, (sizeof addrs_lht/sizeof(uint8_t)), pkgs_lht, ((sizeof pkgs_lht)/sizeof(PKG)));

    // Тестирование всей системы на включение-выключение:
    uint8_t addrs_1[4] = {10, 12, 20, 22};
    // Порядок теста:
    //  1. Запрос состояния
    //  2. Перевод каждого устройства в одно из состояний
    //  3. Запрос состояния
    //  4. Перевод каждого устройства в другое состояние
    //  5. Запрос состояния
    //  6. Выключение всех устройств
    PKG pkgs_1[5];
    pkgs_1[0] = {0x00, STATUS, IDLE,   	"STATUS"};
    pkgs_1[1] = {0x00, SET,    CMD_GO,  "SET CMD_GO/RIGHT"};
    pkgs_1[2] = {0x00, STATUS, IDLE,   	"STATUS"};
    pkgs_1[3] = {0x00, SET,    CMD_STOP,"SET CMD_STOP/LEFT"};
    pkgs_1[4] = {0x00, STATUS, IDLE,   	"STATUS"};

    pushCmds(addrs_1, (sizeof addrs_1/sizeof(uint8_t)), pkgs_1, ((sizeof pkgs_1)/sizeof(PKG)));

    uint8_t addrs_2[1] = {128};
    PKG pkgs_2[2];
    pkgs_2[0] = {0x00, SET,    CMD_OFF, "SET CMD_OFF"};

    pushCmds(addrs_2, (sizeof addrs_2/sizeof(uint8_t)), pkgs_2, ((sizeof pkgs_2)/sizeof(PKG)));
}

void pushCmds(uint8_t *aAddrs, size_t limitAddrs, PKG *pkgs, size_t limitPkgs)
{
    UseTTY tty;

    bool res = tty.openPort("/dev/ttyUSB0", B9600);
    if(!res)
    {
        printf("Невозможно открыть COM порт\n");
        return;
    }

    for (size_t j = 0; j < limitAddrs; j++)
    {
        for (size_t r = 0; r < limitPkgs; r++)
        {
            PKG m_pkg = pkgs[r];
            m_pkg.addr = aAddrs[j];
            tty.sendData(&m_pkg.addr, 1);
            tty.sendData(&m_pkg.cmd,  1);
            tty.sendData(&m_pkg.data, 1);

            printf("----------------------------------\n");
            SHOW(uint8_t, m_pkg.addr); SHOW(uint8_t, m_pkg.cmd); SHOW(uint8_t, m_pkg.data);
            printf("%s\n", m_pkg.str);

            u_char rbuff[3];
            size_t i = 0;
            while (i < 3)
            {
                ssize_t s = tty.readData(&rbuff[i], 1);
                if (s < 1)
                {
                    printf("Нет ответа\n");
                    return;
                }
                i++;
            }

            SHOW(uint8_t, rbuff[0]); SHOW(uint8_t, rbuff[1]); SHOW(uint8_t, rbuff[2]);
            printf("\n");
            sleep(INTERVAL);
        }
    }
    tty.closeCom();
}
