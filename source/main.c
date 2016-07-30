/* 
 * File:   main.c
 * Author: noboru
 *
 * Created on 2016/07/21, 18:32
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "pca9685.h"

#define I2C_ADDRESS 0x40    // I2Cアドレス
#define PIN_BASE    300     // I2Cアクセス用ID?
#define HERTZ       1000    // I2C速度
#define MAX_PWM     4096    // PWM最大値

#define NUM_RGB_LED 5       // RGB LED数

//////////////////////////////////
// メイン
// CGI動作
int main( void )
{
    int i;
    int fd;             // I2Cファイルディスクリプタ
    int led_num;        // 引数1のLED番号
    long param_val;     // 引数2の数値
    int led_r_pwm;      // 赤LEDのPWM値
    int led_g_pwm;      // 緑LEDのPWM値
    int led_b_pwm;      // 青LEDのPWM値

    int param_len;      // 引数の長さ
    char* param_str;    // 引数の文字列

    // CGIレスポンスのヘッダー
    printf("Content-Type:text/html;charset=utf-8\n\n");
    // 引数チェック
    // クエリのチェック CGIは xxx.cgi?nnn,mmm GETで呼ばれる
    param_str = getenv("QUERY_STRING");
    param_len = strlen( param_str ); 
//    printf( "引数は%d文字:%s \r\n",param_len, param_str );
    if( param_len < 1 )
    {
        printf("Error parameter length %d\r\n",param_len );
        return -1;
    }

    //引数から数値を得る
    sscanf( param_str,"%d,%lx", &led_num, &param_val );
    // 引数1:LED番号0..(NUM_RGB_LED-1)または-1, -1はすべてのLED(初期化)
    // 引数2:RGB値 0xrrggbb
    // LED番号チェック
    if( led_num >= NUM_RGB_LED )
    {
        printf("Error LED Number %d\r\n",led_num );
        return -1;
    }
    // 引数2から各R,G,B値
    led_b_pwm = ( ( param_val & 0x0000ff )       ) * 8;
    led_g_pwm = ( ( param_val & 0x00ff00 ) >> 8  ) * 8;
    led_r_pwm = ( ( param_val & 0xff0000 ) >> 16 ) * 8;
    // LED番号が-1?
    if( led_num == -1 )
    {
        // PCA9685初期化
        fd = pca9685Setup( PIN_BASE, I2C_ADDRESS, HERTZ );
        if (fd < 0)
        {
            printf("Error PCA9685 setup %d\r\n",fd );
            return -1;
        }
        else
        {
            pca9685PWMReset( fd );
//            printf("PCA9685 RESET \r\n");
            // 5 RGB LED pwm set
            for( i = 0; i < NUM_RGB_LED; i++ )
            {

                pca9685PWMWrite( fd, i*3+0, 0, led_b_pwm );
                pca9685PWMWrite( fd, i*3+1, 0, led_g_pwm );
                pca9685PWMWrite( fd, i*3+2, 0, led_r_pwm );
            }
            printf("PCA9685 setup ok %d\r\n",fd );
            return 0;
        }
    }

    // 個別LEDの設定
    // I2Cのfile descriptor
    fd = wiringPiI2CSetup( I2C_ADDRESS );
    if( fd < 0 )
    {
        printf("BAD File Descriptor %d\r\n",fd );
        return fd;
    }
    else
    {
        pca9685PWMWrite( fd, led_num*3+0, 0, led_b_pwm );
        pca9685PWMWrite( fd, led_num*3+1, 0, led_g_pwm );
        pca9685PWMWrite( fd, led_num*3+2, 0, led_r_pwm );
        printf("%d:%03x,%03x,%03x \r\n",led_num,led_r_pwm,led_g_pwm,led_b_pwm );
    }
    return 0;
}
