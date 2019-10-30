/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
CAN_TxHeaderTypeDef     TxMeg;
CAN_RxHeaderTypeDef     RxMeg;
uint32_t* pmailboxfeedback;
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 36;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_8TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_6TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = ENABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();
  
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**CAN1 GPIO Configuration    
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_TX_IRQn, 4, 0);
    HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();
  
    /**CAN1 GPIO Configuration    
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX 
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void CAN_Filter_Init(CAN_HandleTypeDef* hcan)
{
		CAN_FilterTypeDef  sFilterConfig; 
		sFilterConfig.FilterBank = 0;                       //过滤器0  
		sFilterConfig.FilterMode =  CAN_FILTERMODE_IDMASK;  //设为掩码模式      
		sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;    		  
		sFilterConfig.FilterIdHigh = 0X2460;   //基本ID放入到STID中    
		sFilterConfig.FilterIdLow  = 0X0000 ;    		  
		sFilterConfig.FilterMaskIdHigh =0Xffff; 
		sFilterConfig.FilterMaskIdLow  =0Xffff;   
		sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;    //接收到的报文放入到FIFO0中   
		sFilterConfig.FilterActivation = ENABLE;  	//激活过滤器  
		sFilterConfig.SlaveStartFilterBank  = 0; 
	  if ( HAL_CAN_ConfigFilter(hcan, &sFilterConfig)!= HAL_OK)
		{
			Error_Handler();
		}
}
void CAN_User_Init(CAN_HandleTypeDef* hcan )   //用户初始化函数
{   
		CAN_Filter_Init(hcan);
	  if ( HAL_CAN_Start(hcan)!= HAL_OK) //开启CAN   
		{
			Error_Handler();
		}
	  if ( HAL_CAN_ActivateNotification(hcan,CAN_IT_TX_MAILBOX_EMPTY)!= HAL_OK)
		{
			Error_Handler();
		}

/* Receive Interrupts */
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO0_MSG_PENDING)!= HAL_OK)
		{
			Error_Handler();
		}
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO0_FULL)!= HAL_OK)
		{
			Error_Handler();
		}
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO0_OVERRUN)!= HAL_OK)
		{
			Error_Handler();
		}
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO1_MSG_PENDING)!= HAL_OK)
		{
			Error_Handler();
		}
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO1_FULL)!= HAL_OK)
		{
			Error_Handler();
		}
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO1_OVERRUN)!= HAL_OK)
		{
			Error_Handler();
		}

/* Operating Mode Interrupts */
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_WAKEUP)!= HAL_OK)
		{
			Error_Handler();
		}
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_SLEEP_ACK)!= HAL_OK)
		{
			Error_Handler();
		}

/* Error Interrupts */
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_ERROR_WARNING)!= HAL_OK)
		{
			Error_Handler();
		}
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_ERROR_PASSIVE)!= HAL_OK)
		{
			Error_Handler();
		}
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_BUSOFF)!= HAL_OK)
		{
			Error_Handler();
		}
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_LAST_ERROR_CODE)!= HAL_OK)
		{
			Error_Handler();
		}
	  if(HAL_CAN_ActivateNotification(hcan,CAN_IT_ERROR)!= HAL_OK)
		{
			Error_Handler();
		}
		
}

//发送数据函数
HAL_StatusTypeDef CANx_SendNormalData(CAN_HandleTypeDef* hcan,uint32_t ID,uint8_t *pData,uint16_t Len)
{	    
	uint16_t SendTimes,SendCNT=0;	
	uint8_t  FreeTxNum=0;	
	TxMeg.StdId=ID;	
	TxMeg.IDE=CAN_ID_STD;//CAN_ID_EXT;  
	TxMeg.RTR=CAN_RTR_DATA;	
	if(!hcan || ! pData ||!Len)  return HAL_ERROR;	
	SendTimes=Len/8+(Len%8?1:0);	
	TxMeg.DLC=8;	
	while(SendTimes--)
	{	
		if(0==SendTimes)
		{			
			if(Len%8)TxMeg.DLC=Len%8;
		}		
		do
		{			
			FreeTxNum=HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);		
		}
		while(0==FreeTxNum);	
		HAL_Delay(1);   //没有延时很有可能会发送失败		
		if(HAL_CAN_AddTxMessage(&hcan1,&TxMeg,pData+SendCNT,pmailboxfeedback)!=HAL_OK)		
		{			
			Error_Handler();
		}		
		SendCNT+=8;	
	}
	return HAL_OK;
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
