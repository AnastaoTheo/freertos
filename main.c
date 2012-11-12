
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


// The error routine that is called if the driver library encounters an error.
#ifdef DEBUG
void __error__(char *pcFilename, unsigned long ulLine) {
	return ;
}
#endif

// This hook is called by FreeRTOS when an stack overflow error is detected.
void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
		;
}

// Initialize FreeRTOS and start the initial set of tasks.
int main(void) {

    // Set the clocking to run at 50 MHz from the PLL.
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);

    // Initialize the UART and configure it for 115,200, 8-N-1 operation.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioInit(0);

    // Print demo introduction.
	UARTprintf("This is an empty project using FreeRTOS\n");
	UARTprintf("This was brought to you by Cristovao Rufino <cristovaozr@gmail.com>\n");

	// Start tasks here


    // Start the scheduler.  This should not return.
    vTaskStartScheduler();

	UARTprintf("Something nasty happened because vTaskStartScheduler() returned!\n");
    while(1)
		;
}
