//
//  Raspberry Pi SPI module
//      xkozima@myu.ac.jp
#ifndef SPI_H
#define SPI_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>

#define SPI_DEVICE    "/dev/spidev0.0"  //  SPI デバイス（デフォルト）
#define SPI_SPEED     8000000           //  クロック 8MHz（デフォルト）
#define SPI_BITS      8                 //  ビット数（8bit のみ可能）

class SPI {
public:
    //  init: 最初に１回だけ呼び出す（でバイス名・クロック周波数を与える）
    void init ();
    void init (const char *device, int clockInHz);
    //  quit: SPI を使い終わったら呼び出す（礼儀正しい人のみ）
    void quit ();
    //  sendBuffer: 大きなバイト配列の送信
    void sendBuffer (unsigned char *data, int len);
    //  sendN: Ｎバイトデータの送信（n <= 2048）
    void sendN (unsigned char *data, int n);
    //  send1: １バイトデータの単発送信
    int send1 (unsigned char data);
    //  receiveN: Ｎバイトデータの受信
    void sendRecN (unsigned char *send, unsigned char *rec, int n);
private:
    //  ファイルディスクリプタ / クロック(Hz)
    int fd;
    int clock;
    //  満載のブロック数 / 積み残しブロックのバイト数
    int numFullBlocks, lastBlockSize;
    //  SPI 転送の構造体
    struct spi_ioc_transfer *trStruct;
};

#endif
