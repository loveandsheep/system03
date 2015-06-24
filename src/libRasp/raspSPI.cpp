//
//  raspSPI: SPI (Serial Peripheral Interface) module
//      xkozima@myu.ac.jp
#include "raspSPI.h"

#define SPI_BLOCKSIZE 2048              //  ブロック転送サイズ（画像等）
#define SPI_DELAY     0

//  SPI モジュールの初期化（最初に１回だけ呼び出す: "/dev/spidev0.0", 8MHz）
void SPI::init ()
{
    init("/dev/spidev0.0", 8000000);
}
//  マニュアル初期化
//  ex) spi_init("/dev/spidev0.1", 1000000);  //  1MHz clock
void SPI::init (const char *device, int clockInHz)
{
    int  ret;
    if (device == NULL) device = SPI_DEVICE;
    if (clockInHz == 0) clock = SPI_SPEED; else clock = clockInHz;
    //  SPI デバイスを開く
    fd = open(device, O_RDWR);
    if (fd < 0) {
        printf("error: cannot open %s (SPI::init)\n", SPI_DEVICE);
        exit(-1);
    }
    //  転送モード 0 を送信・受信に設定（オマジナイ）
    unsigned char mode = SPI_MODE_3;
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret < 0) {
        printf("error: cannot set WR_MODE to %d (SPI::init)\n", mode);
        close(fd);
        exit(-1);
    }
    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret < 0) {
        printf("error: cannot set RD_MODE to %d (SPI::init)\n", mode);
        close(fd);
        exit(-1);
    }
    //  ビット数を送信・受信に設定（8bit しか受け付けない）
    unsigned char bits = SPI_BITS;
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret < 0) {
        printf("error: cannot set WR_BITS_PER_WORD to %d (SPI::init)\n", bits);
        close(fd);
        exit(-1);
    }
    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret < 0) {
        printf("error: cannot set RD_BITS_PER_WORD to %d (SPI::init)\n", bits);
        close(fd);
        exit(-1);
    }
}

//  SPI を使い終わったら呼び出す（礼儀正しい人のみ）
void SPI::quit ()
{
    close(fd);
    free(trStruct);
}

//  １バイトデータの単発送信
void SPI::send1 (unsigned char data)
{
    //  setup a block
    static unsigned char tdata[1];
    tdata[0] = data;
    struct spi_ioc_transfer tr[1];
    tr[0].tx_buf = (unsigned int) tdata;
    tr[0].rx_buf = (unsigned int) NULL;
    tr[0].len    = 1;
    tr[0].speed_hz      = clock;
    tr[0].delay_usecs   = SPI_DELAY;
    tr[0].bits_per_word = SPI_BITS;
    tr[0].cs_change     = 0;
    //  send this byte
    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), tr);
    if (ret < 0) {
        printf("error: cannot send spi message (SPI::send1)\n");
//        exit(-1);
    }
}
    
//  Ｎバイトデータの送信（N <= SPI_BUFFERSIZE）
void SPI::sendN (unsigned char *data, int n)
{
    //  setup a block
    struct spi_ioc_transfer tr[1];
    tr[0].tx_buf = (unsigned int) data;
    tr[0].rx_buf = (unsigned int) NULL;
    tr[0].len    = n;
    tr[0].speed_hz      = clock;
    tr[0].delay_usecs   = SPI_DELAY;
    tr[0].bits_per_word = SPI_BITS;
    tr[0].cs_change     = 0;
    //  send this byte
    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), tr);
    if (ret < 0) {
        printf("error: cannot send spi message (SPI::sendN)\n");
//        exit(-1);
    }
}

//  大きなバイト配列の送信
void SPI::sendBuffer (unsigned char *buffer, int len)
{
    //  ブロック数の計算
    int numFullBlocks = len / SPI_BLOCKSIZE;
    int lastBlockSize = len % SPI_BLOCKSIZE;
    //  転送ブロック（満載）を送信
    int i;
    unsigned char *bufPointer = buffer;
    for (i = 0; i < numFullBlocks; i++) {
        sendN(bufPointer, SPI_BLOCKSIZE);
        bufPointer += SPI_BLOCKSIZE;
    }
    //  積み残し分の転送ブロックを送信（必要に応じて）
    if (lastBlockSize) {
        //  積み残しあり
        sendN(bufPointer, lastBlockSize);
    }
}

//  sendRecN: Ｎバイトデータの送信と受信（2048バイトまで）
void SPI::sendRecN (unsigned char *send, unsigned char *rec, int n)
{
    //  setup a block
    struct spi_ioc_transfer tr[1];
    tr[0].tx_buf = (unsigned int) send;
    tr[0].rx_buf = (unsigned int) rec;
    tr[0].len    = n;
    tr[0].speed_hz      = clock;
    tr[0].delay_usecs   = SPI_DELAY;
    tr[0].bits_per_word = SPI_BITS;
    tr[0].cs_change     = 0;
    //  send this byte
    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), tr);
    if (ret < 0) {
        printf("error: cannot send spi message (SPI::sendRecN)\n");
        exit(-1);
    }
}

//
