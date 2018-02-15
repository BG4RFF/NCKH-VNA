/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2016 Semtech

Description: Tx Continuous Wave implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include <string.h>
#include "board.h"
#include "radio.h"

#if defined( REGION_AS923 )

#define RF_FREQUENCY                                923000000 // Hz

#elif defined( REGION_AU915 )

#define RF_FREQUENCY                                915000000 // Hz

#elif defined( REGION_CN779 )

#define RF_FREQUENCY                                779000000 // Hz

#elif defined( REGION_EU868 )

#define RF_FREQUENCY                                868000000 // Hz

#elif defined( REGION_KR920 )

#define RF_FREQUENCY                                920000000 // Hz

#elif defined( REGION_IN865 )

#define RF_FREQUENCY                                865000000 // Hz

#elif defined( REGION_US915 )

#define RF_FREQUENCY                                915000000 // Hz

#elif defined( REGION_US915_HYBRID )

#define RF_FREQUENCY                                915000000 // Hz

#else

    #error "Please define a frequency band in the compiler options."

#endif

#define TX_OUTPUT_POWER                             0        // 14 dBm
#define TX_TIMEOUT                                  10       // seconds (MAX value)

//uint32_t freq [] = {868000000,869000000,870000000,871000000,872000000,873000000};
uint32_t freq = 868000000;
uint8_t cur_freq [9], temp[4],ledstate = 1 ;

/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

/*!
 * \brief Function executed on Radio Tx Timeout event
 */
void OnRadioTxTimeout( void )
{
    // Restarts continuous wave transmission when timeout expires
    Radio.SetTxContinuousWave(freq , TX_OUTPUT_POWER, TX_TIMEOUT );
}

void Update(void);

/**
 * Main application entry point.
 */
int main( void )
{
    // Target board initialization
    BoardInitMcu( );
    //BoardInitPeriph( );
	for (int i = 0; i < 3 ; ++i)
	{
		GpioWrite( &Led1, 1 );
		Delay(1);
		GpioWrite( &Led1, 0 );
		Delay(1);
	}
    // Radio initialization
    RadioEvents.TxTimeout = OnRadioTxTimeout;
    Radio.Init( &RadioEvents );

    Radio.SetTxContinuousWave( 868000000, TX_OUTPUT_POWER, TX_TIMEOUT );

    // Blink LEDs just to show some activity
		GpioWrite( &Led1, 0 );
    while( 1 )
    {
     
    }
}

void Update(void)
{
	Radio.SetTxContinuousWave( freq, TX_OUTPUT_POWER, TX_TIMEOUT );
	GpioWrite( &Led1, ledstate );
	if (ledstate ==1)
		ledstate = 0;
	else ledstate = 1;
	
	UartPutBuffer(&Uart1, "frequency : ", 12) ;

	sprintf(cur_freq, "%d\r\n", freq);
	UartPutBuffer(&Uart1,cur_freq, 11);
		 
//	UartPutBuffer(&Uart1, "index : ", 8);
//	
//	sprintf(temp, "%d\r\n", indexs );
//	if (indexs > 9)
//		UartPutBuffer(&Uart1, temp, 3);
//	else 
//		UartPutBuffer(&Uart1, temp, 4);
		 
}
