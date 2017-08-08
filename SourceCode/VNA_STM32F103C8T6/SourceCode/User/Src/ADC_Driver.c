#include "ADC_Driver.h"

void ADC_init(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  /* PCLK2 is the APB2 clock */
  /* ADCCLK = PCLK2/6 = 72/6 = 12MHz*/
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);

  /* Enable ADC1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  ADC_DeInit(ADC1);

  /* ADC1 Configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;

  ADC_Init(ADC1, &ADC_InitStructure);
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */
  ADC_ResetCalibration(ADC1);

  /* Check the end of ADC1 reset calibration register */
  while (ADC_GetResetCalibrationStatus(ADC1))
    ;

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);

  /* Check the end of ADC1 calibration */
  while (ADC_GetCalibrationStatus(ADC1))
    ;
}

uint16_t ADC_readADC1(uint8_t channel)
{
  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);

  /* Start the conversion */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

  /* Wait until conversion completion */
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
    ;

  /* Get the conversion value */
  return ADC_GetConversionValue(ADC1);
}

float ADC_readMag(void)
{
	uint16_t ADC_Value = ADC_readADC1(VMAG);
	float Voltage = _ADC_to_voltage(ADC_Value);
  return ((Voltage * 60/1.8) - 30);
}

float ADC_readPhs(void)
{
	uint16_t ADC_Value = ADC_readADC1(VMAG);
	float Voltage = _ADC_to_voltage(ADC_Value);
  return (180 - (Voltage * 100));
}

float _ADC_to_voltage(uint16_t adc_value)
{
	return (adc_value * 3.3 / 4096);
}
