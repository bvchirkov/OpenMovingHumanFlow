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

// Взято с сайта http://dekud.blogspot.com/2013/12/com-linux-com-com-linux.html
// File created 26.06.2019

#pragma once

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

class UseTTY
{
private:
    int F_ID = -1; ///< Иднетификатор файлового дескриптора

public:
	UseTTY() = default;
	~UseTTY() = default;

public:
    /**
     * @brief openPort Открыть COM порт
     * @param COM_name Путь к устройству, например: /dev/ttyS0 или  /dev/ttyUSB0 - для USB
     * @param speed скорость, например: B9600, B57600, B115200
     * @return false - порт не открылся, true - открылся
     */
    bool		openPort(const char *COM_name, speed_t speed);
    /**
     * @brief readData Прочитать данные из COM порта
     * @param buff Буфер для принятых данных
     * @param size Количество запрашиваемых байт
     * @return Return the number read, -1 for errors or 0 for EOF
     */
	ssize_t		readData(u_char *buff, u_int size);
    /**
     * @brief sendData Отправить в COM порт данные
     * @param buff Буфер данных для отправки
     * @param len Количество отправляемых байт
     * @return Return the number written, or -1.
     */
    ssize_t		sendData(const u_char *buff, u_int len);
    /**
     * @brief closeCom Закрыть COM порт
     */
	void		closeCom();
};

bool UseTTY::openPort(const char *COM_name, speed_t speed)
{
	F_ID = open(COM_name, O_RDWR | O_NOCTTY);
	if(F_ID == -1)
	{
		char *errmsg = strerror(errno);
		printf("%s\n", errmsg);
		return false;
	}

	struct termios options;     /*структура для установки порта*/
	tcgetattr(F_ID, &options);  /*читает пораметры порта*/

	cfsetispeed(&options, speed); /*установка скорости порта*/
	cfsetospeed(&options, speed); /*установка скорости порта*/

	options.c_cc[VTIME]    = 20; /*Время ожидания байта 20*0.1 = 2 секунды */
	options.c_cc[VMIN]     = 0;  /*минимальное число байт для чтения*/

	options.c_cflag &= ~PARENB; /*бит четности не используется*/
	options.c_cflag &= ~CSTOPB; /*1 стоп бит */
	options.c_cflag &= ~CSIZE;  /*Размер байта*/
	options.c_cflag |= CS8;     /*8 бит*/

	options.c_lflag = 0;
	options.c_oflag &= ~OPOST; /*Обязательно отключить постобработку*/

	tcsetattr(F_ID, TCSANOW, &options); /*сохронения параметров порта*/

	return true;
}

ssize_t UseTTY::readData(u_char *buff, u_int size)
{
	ssize_t n = read(F_ID, buff, size);
	if(n == -1)
	{
		char *errmsg = strerror(errno);
		printf("%s\n", errmsg);
	}
	return n;
}

ssize_t UseTTY::sendData(const u_char* buff, u_int len)
{
	ssize_t n = write(F_ID, buff, len);
	if(n == -1)
	{
		char *errmsg = strerror(errno);
		printf("%s\n", errmsg);
	}
	return n;
}

void UseTTY::closeCom(void)
{
	close(F_ID);
	F_ID = -1;
}


/*----------------------------------------------------------------------------
Пример использования usetty.hpp
#include "usetty.hpp"
#include <thread>
#include <iostream>

int main()
{
    UseTTY tty;

    bool res = tty.openPort("/dev/ttyUSB0", B9600);
    if(!res)
    {
        printf("Невозможно открыть COM порт\n");
        return 0;
    }

    const std::bitset<8> id[2] = {3, 7};
    const std::bitset<8> code[3] = {CODE_LEFT, CODE_RIGHT, CODE_STOP};
    u_char cmds[6];
    size_t k = 0;
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            cmds[k] = static_cast<u_char>(((code[j] << 5) | id[i]).to_ulong());
            std::cout << ((code[j] << 5) | id[i]) << '\t' << cmds[k] << std::endl;
            k++;
        }
    }

    for (size_t i = 0; i < 6; i++)
    {
        tty.sendData(&cmds[i], 1);

        u_char rbuff;
        ssize_t s = tty.readData(&rbuff, 1);
        if (s < 1)
        {
            printf("Нет ответа\n");
            return 0;
        }
        std::cout << rbuff << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    tty.closeCom();
    return 0;
}
----------------------------------------------------------------------------*/
