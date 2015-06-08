//
//  raspGPIO: Raspberry Pi GPIO module
//      xkozima@myu.ac.jp
#include "raspGPIO.h"

//  レジスタブロックの物理アドレス
#define PERI_BASE     0x3F000000
#define GPIO_BASE     (PERI_BASE + 0x200000)
#define BLOCK_SIZE    4096

//  GPIO 関連レジスタ (volatile＝必ず実メモリにアクセスさせる)
static volatile unsigned int *Gpio;

//  GPIO 初期化（最初に１度だけ呼び出すこと）
void gpio_init()
{
    //  既に初期化済なら何もしない
    if (Gpio) return;
    //  ここから GPIO 初期化
    int fd;
    void *gpio_map;
    //  /dev/mem（物理メモリデバイス）を開く（sudo が必要）
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf("error: cannot open /dev/mem (gpio_init)\n");
        exit(-1);
    }
    //  mmap で GPIO（物理メモリ）を gpio_map（仮想メモリ）に対応づける
    gpio_map = mmap(NULL, BLOCK_SIZE,
                    PROT_READ | PROT_WRITE, MAP_SHARED,
                    fd, GPIO_BASE );
    if ((int) gpio_map == -1) {
        printf("error: cannot map /dev/mem on the memory (gpio_init)\n");
        exit(-1);
    }
    //  mmap 後は不要な fd をクローズ
    close(fd);
    //  gpio[index]: 整数 uint32 の配列としてレジスタへのアクセスを確立
    Gpio = (unsigned int *) gpio_map;
}

//  ピン機能の設定（ピンを使用する前に必ず設定）
//      pin : (P1) 2,3,4,7,8,9,10,11,14,15,17,18,22,23,24,25,27
//            (P5) 28,29,30,31
//      mode: GPIO_INPUT, _OUTPUT, _ALT0, _ALT1, _ALT2, _ALT3, _ALT4, _ALT5
void gpio_configure(int pin, int mode)
{
    //  ピン番号チェック
    if (pin < 0 || pin > 31) {
        printf("error: pin number out of range (gpio_configure)\n");
        exit(-1);
    }
    //  レジスタ番号（index）と３ビットマスクを生成
    int index = pin / 10;
    unsigned int mask = ~(0x7 << ((pin % 10) * 3));
    //  GPFSEL0/1 の該当する FSEL (3bit) のみを書き換え
    Gpio[index] = (Gpio[index] & mask) | ((mode & 0x7) << ((pin % 10) * 3));
}

//  ピンをセット (3.3V)，クリア (0V)
void gpio_set(int pin)
{
    //  ピン番号チェック（スピードを追求するなら省略してもよい）
    if (pin < 0 || pin > 31) {
        printf("error: pin number out of range (gpio_set)\n");
        exit(-1);
    }
    //  ピンに１を出力（3.3V 出力）
    Gpio[7] = 0x1 << pin;   //  GPSET0
}
void gpio_clear(int pin)
{
    //  ピン番号チェック（スピードを追求するなら省略してもよい）
    if (pin < 0 || pin > 31) {
        printf("error: pin number out of range (gpio_clear)\n");
        exit(-1);
    }
    //  ピンに０を出力（0V 出力）
    Gpio[10] = 0x1 << pin;  //  GPCLR0
}

//  ピン状態の読み取り（3.3V->1, 0V->0）
int gpio_read (int pin)
{
    //  ピン番号チェック（スピードを追求するなら省略してもよい）
    if (pin < 0 || pin > 31) {
        printf("error: pin number out of range (gpio_read)\n");
        exit(-1);
    }
    //  ピンの電圧を返す（入力/出力を問わず 3.3V なら 1，0V なら 0）
    return (Gpio[13] & (0x1 << pin)) != 0;  //  GPLEV0
}

//  プルアップ/ダウン抵抗の設定
//      pullmode: GPIO_PULLNONE/PULLDOWN/PULLUP
void gpio_configure_pull (int pin, int pullmode)
{
    //  ピン番号チェック
    if (pin < 0 || pin > 31) {
        printf("error: pin number out of range (gpio_configure_pull)\n");
        exit(-1);
    }
    //  プルモード (2bit)を書き込む NONE/DOWN/UP
    Gpio[37] = pullmode & 0x3;  //  GPPUD
    usleep(1);
    //  ピンにクロックを供給（前後にウェイト）
    Gpio[38] = 0x1 << pin;      //  GPPUDCLK0
    usleep(1);
    //  プルモード・クロック状態をクリアして終了
    Gpio[37] = 0;
    Gpio[38] = 0;
}

//
