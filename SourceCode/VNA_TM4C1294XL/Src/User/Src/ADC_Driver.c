#include "ADC_Driver.h"

void ADC_init(void)
{
    SysCtlPeripheralEnable(VMAG_ADC_SYSCTL_PERIPH);
    while (!SysCtlPeripheralReady(VMAG_ADC_SYSCTL_PERIPH))
    {
    }

    SysCtlPeripheralEnable(VPHS_ADC_SYSCTL_PERIPH);
    while (!SysCtlPeripheralReady(VPHS_ADC_SYSCTL_PERIPH))
    {
    }

    SysCtlPeripheralEnable(VMAG_ADC_AIN_SYSCTL_PERIPH);
    while (!SysCtlPeripheralReady(VMAG_ADC_AIN_SYSCTL_PERIPH))
    {
    }

    SysCtlPeripheralEnable(VPHS_ADC_AIN_SYSCTL_PERIPH);
    while (!SysCtlPeripheralReady(VPHS_ADC_AIN_SYSCTL_PERIPH))
    {
    }

    GPIOPinTypeADC(VMAG_AIN_PORT_BASE, VMAG_AIN_PIN); // AIN3
    GPIOPinTypeADC(VPHS_AIN_PORT_BASE, VPHS_AIN_PIN); // AIN2

    ADCSequenceConfigure(VMAG_ADC_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(VMAG_ADC_BASE, 3, 0, VMAG_ADC_CHANNEL | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(VMAG_ADC_BASE, 3);

    ADCSequenceConfigure(VPHS_ADC_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(VPHS_ADC_BASE, 3, 0, VPHS_ADC_CHANNEL | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(VPHS_ADC_BASE, 3);
}

double ADC_readMag(void)
{
    uint32_t returnValue = 0;

    ADCProcessorTrigger(VMAG_ADC_BASE, 3);
    while (!ADCIntStatus(VMAG_ADC_BASE, 3, false))
    {
    }
    ADCIntClear(VMAG_ADC_BASE, 3);
    ADCSequenceDataGet(VMAG_ADC_BASE, 3, &returnValue);

    double tmp = (returnValue / 4096.0);
    double Voltage = ((double)3.3) * tmp;
    return (Voltage * 60 / 1.8) - 30;
}

double ADC_readPhs(void)
{
    uint32_t returnValue = 0;

    ADCProcessorTrigger(VPHS_ADC_BASE, 3);
    while (!ADCIntStatus(VPHS_ADC_BASE, 3, false))
    {
    }
    ADCIntClear(VPHS_ADC_BASE, 3);
    ADCSequenceDataGet(VPHS_ADC_BASE, 3, &returnValue);

    double Voltage = REFERENCE_VOLTAGE * (returnValue / 4096.0);
    return (180 - (Voltage * 100));
}
