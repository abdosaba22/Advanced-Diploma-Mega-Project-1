#include <HLED_Interface.h>
#include <HLED_Private.h>
#include <MGPIO_Interface.h>

/* config LED one */
//HLED_t LEDGreen=
//{
//.LedPort = LED_GPORT,
//.LedPin  = LED_GPIN,
//.LedMode = LED_GMODE,
//.conn_type=LED_SourceConnnec,
//};

/* config LED one */
HLED_t LEDRed=
{
.LedPort = LED_RPORT,
.LedPin  = LED_RPIN,
.LedMode = LED_RMODE,
.conn_type=LED_SourceConnnec,
};

