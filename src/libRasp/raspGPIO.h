//
//  Raspberry Pi GPIO module
//      xkozima@myu.ac.jp
#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

//  gpio_init: GPIO 初期化（最初に１度だけ呼び出すこと）
void gpio_init();

//  ピン機能（BCM2835）
#define GPIO_INPUT    0x0       //  入力
#define GPIO_OUTPUT   0x1       //  出力
#define GPIO_ALT0     0x4
#define GPIO_ALT1     0x5
#define GPIO_ALT2     0x6
#define GPIO_ALT3     0x7
#define GPIO_ALT4     0x3
#define GPIO_ALT5     0x2

//  gpio_configure: ピン機能を設定する（ピンを使用する前に必ず設定）
//      pin : (P1) 2,3,4,7,8,9,10,11,14,15,17,18,22,23,24,25,27
//            (P5) 28,29,30,31
//      mode: GPIO_INPUT, _OUTPUT, _ALT0, _ALT1, _ALT2, _ALT3, _ALT4, _ALT5
void gpio_configure(int pin, int mode);

//  gpio_set/clear: ピンをセット (3.3V)，クリア (0V)
void gpio_set(int pin);
void gpio_clear(int pin);

//  gpio_read: ピンの読み取り（3.3V->1, 0V->0)
int gpio_read (int pin);

//  プルアップ・プルダウン機能
#define GPIO_PULLNONE 0x0
#define GPIO_PULLDOWN 0x1
#define GPIO_PULLUP   0x2

//  gpio_configure_pull: プルアップ抵抗またはプルダウン抵抗の設定
void gpio_configure_pull(int pin, int pullmode);

#endif
