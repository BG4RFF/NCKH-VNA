#include "ADC_Driver.h"

void ADC_init(void)
{
    SysCtlPeripheralEnable(AD_868_ADC_SYSCTL_PERIPH);
    while (!SysCtlPeripheralReady(AD_868_ADC_SYSCTL_PERIPH))
    {
    }

    SysCtlPeripheralEnable(AD_2400_ADC_SYSCTL_PERIPH);
    while (!SysCtlPeripheralReady(AD_2400_ADC_SYSCTL_PERIPH))
    {
    }

    SysCtlPeripheralEnable(AD_868_ADC_AIN_SYSCTL_PERIPH);
    while (!SysCtlPeripheralReady(AD_868_ADC_AIN_SYSCTL_PERIPH))
    {
    }

    SysCtlPeripheralEnable(AD_2400_ADC_AIN_SYSCTL_PERIPH);
    while (!SysCtlPeripheralReady(AD_2400_ADC_AIN_SYSCTL_PERIPH))
    {
    }

    GPIOPinTypeADC(AD_868_AIN_PORT_BASE, AD_868_AIN_PIN);
    GPIOPinTypeADC(AD_2400_AIN_PORT_BASE, AD_2400_AIN_PIN);

    ADCSequenceConfigure(AD_868_ADC_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(AD_868_ADC_BASE, 3, 0, AD_868_ADC_CHANNEL | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(AD_868_ADC_BASE, 3);

    ADCSequenceConfigure(AD_2400_ADC_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(AD_2400_ADC_BASE, 3, 0, AD_2400_ADC_CHANNEL | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(AD_2400_ADC_BASE, 3);
}

double ADC_read868(void)
{
    uint32_t returnValue = 0;
    double voltage = 0, dBm = 0;

    ADCProcessorTrigger(AD_868_ADC_BASE, 3);
    while (!ADCIntStatus(AD_868_ADC_BASE, 3, false))
    {
    }
    ADCIntClear(AD_868_ADC_BASE, 3);
    ADCSequenceDataGet(AD_868_ADC_BASE, 3, &returnValue);

    voltage = __AdcValueToVoltage(returnValue);
    dBm = __VoltageToDBm(voltage);

    return dBm;
}

double ADC_read2400(void)
{
    uint32_t returnValue = 0;
    double voltage = 0, dBm = 0;

    ADCProcessorTrigger(AD_2400_ADC_BASE, 3);
    while (!ADCIntStatus(AD_2400_ADC_BASE, 3, false))
    {
    }
    ADCIntClear(AD_2400_ADC_BASE, 3);
    ADCSequenceDataGet(AD_2400_ADC_BASE, 3, &returnValue);

    voltage = __AdcValueToVoltage(returnValue);
    dBm = __VoltageToDBm(voltage);

    return dBm;
}

double __AdcValueToVoltage(uint32_t AdcValue)
{
    double returnValue = REFERENCE_VOLTAGE * (AdcValue / 4095.0);
	  return returnValue;
}

double __VoltageToDBm(double voltage)
{
    double returnValue = (100 / 3.0) * voltage - 30;
    if (returnValue < -30)
    {
        returnValue = -30;
    }

    if (returnValue > 30)
    {
        returnValue = 30;
    }

    return returnValue;
}
