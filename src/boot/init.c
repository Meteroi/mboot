/* ----------------------------------------------------------------------------
 *		 
 *        mboot for Lophilo embedded system
 *		
 * ----------------------------------------------------------------------------
 */

#include <string.h>

#include "types.h"
#include "trace.h"
#include "option.h"
#include "mboot.h"
#include "media.h"
#include "sha204.h"

#include "sfr.h"
#include "board.h"
#include "system.h"
#include "twi.h"
#include "fpga.h"
#include "leds.h"
#include "uart.h"
#include "emac.h"
#include "rtc.h"

#include "init.h"

static void Init_EMIF(void);
static void mbootBanner(void);

int main(void)
{
	BTNDIS_P();
	Init_EMIF();
	Init_LEDS();
	Init_TIMER();
	Init_FPGA();
	Init_UART();
	Init_TWI(100000);
	
	mbootBanner();
	
	Init_RTC();
	Init_Media();
	Init_SHA204();
	Init_EMAC();
	SYS_UNRESET();
	
	mboot();

	while(1);
	// return 0;
}

static void Init_EMIF(void)
{
	rSMC_SETUP(0) = (0 << 24) + (0 << 16) + (0 << 8) + (0 << 0);
	rSMC_PULSE(0) = (0 << 24) + (6 << 16) + (0 << 8) + (2 << 0);
	rSMC_CYCLE(0) = (0 << 23) + (6 << 16) + (0 << 7) + (4 << 0);
	rSMC_MODE(0) = (0 << 28) + (0 << 24) + (1 << 20) + (8 << 16) + (2 << 12) + (0 << 8) + (2 << 4) + (1 << 1) + (1 << 0);
	
	rSMC_SETUP(1) = (0 << 24) + (0 << 16) + (0 << 8) + (0 << 0);
	rSMC_PULSE(1) = (0 << 24) + (6 << 16) + (0 << 8) + (2 << 0);
	rSMC_CYCLE(1) = (0 << 23) + (6 << 16) + (0 << 7) + (4 << 0);
	rSMC_MODE(1) = (0 << 28) + (0 << 24) + (1 << 20) + (8 << 16) + (2 << 12) + (0 << 8) + (2 << 4) + (1 << 1) + (1 << 0);
	
	rSMC_SETUP(2) = (0 << 24) + (0 << 16) + (0 << 8) + (0 << 0);
	rSMC_PULSE(2) = (0 << 24) + (6 << 16) + (0 << 8) + (2 << 0);
	rSMC_CYCLE(2) = (0 << 23) + (6 << 16) + (0 << 7) + (4 << 0);
	rSMC_MODE(2) = (0 << 28) + (0 << 24) + (1 << 20) + (8 << 16) + (2 << 12) + (0 << 8) + (2 << 4) + (1 << 1) + (1 << 0);
	
	rSMC_SETUP(3) = (0 << 24) + (0 << 16) + (0 << 8) + (0 << 0);
	rSMC_PULSE(3) = (0 << 24) + (6 << 16) + (0 << 8) + (2 << 0);
	rSMC_CYCLE(3) = (0 << 23) + (6 << 16) + (0 << 7) + (4 << 0);
	rSMC_MODE(3) = (0 << 28) + (0 << 24) + (1 << 20) + (8 << 16) + (2 << 12) + (0 << 8) + (2 << 4) + (1 << 1) + (1 << 0);
}

static void mbootBanner(void)
{
	ShellAllClear();
	
	SHELL_INF("        __                      __"); 
	SHELL_INF("       /\\ \\                    /\\ \\__"); 
	SHELL_INF("___ ___\\ \\ \\____    ___     ___\\ \\ ,_\\"); 
	SHELL_INF(" __` __`\\ \\ '__`\\  / __`\\  / __`\\ \\ \\/"); 
	SHELL_INF(" \\/\\ \\/\\ \\ \\ \\_\\ \\/\\ \\_\\ \\/\\ \\_\\ \\ \\ \\_"); 
	SHELL_INF("\\_\\ \\_\\ \\_\\ \\_,__/\\ \\____/\\ \\____/\\ \\__\\"); 
	SHELL_INF("/_/\\/_/\\/_/\\/___/  \\/___/  \\/___/  \\/__/"); 
	
	// Above banner is generated by: http://www.network-science.de/ascii/
	// HTML-Frontend (c) 1996-2012 by Jorg Seyfferth
	
	SHELL_EMPTY();
	SHELL_INF("Lophilo-mboot ver%s-(%s)", MBOOT_VER, __DATE__);
	SHELL_INF("By Shyu Lee and Ricky Ng-Adam");
	SHELL_BNNER();
	SHELL_EMPTY();
}
