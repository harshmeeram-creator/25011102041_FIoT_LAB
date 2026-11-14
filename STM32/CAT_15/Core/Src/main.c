
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : BME280 Sensor + USART1 Wemos + USART2 Debug
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bme280.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

struct bme280_dev bme;
struct bme280_settings bme_settings;
struct bme280_data comp_data;

static uint8_t bme_i2c_addr = BME280_I2C_ADDR_PRIM;

int8_t bme_status;

double temperature;
double pressure;
double humidity;

char uart_buffer[150];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */

int8_t user_i2c_read(uint8_t reg_addr,
                     uint8_t *reg_data,
                     uint32_t len,
                     void *intf_ptr);

int8_t user_i2c_write(uint8_t reg_addr,
                      const uint8_t *reg_data,
                      uint32_t len,
                      void *intf_ptr);

void user_delay_us(uint32_t period, void *intf_ptr);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int8_t user_i2c_read(uint8_t reg_addr,
                     uint8_t *reg_data,
                     uint32_t len,
                     void *intf_ptr)
{
    uint8_t dev_addr = *(uint8_t *)intf_ptr;

    if (HAL_I2C_Mem_Read(&hi2c1,
                         (uint16_t)(dev_addr << 1),
                         reg_addr,
                         I2C_MEMADD_SIZE_8BIT,
                         reg_data,
                         (uint16_t)len,
                         HAL_MAX_DELAY) == HAL_OK)
    {
        return BME280_OK;
    }

    return BME280_E_COMM_FAIL;
}

int8_t user_i2c_write(uint8_t reg_addr,
                      const uint8_t *reg_data,
                      uint32_t len,
                      void *intf_ptr)
{
    uint8_t dev_addr = *(uint8_t *)intf_ptr;

    if (HAL_I2C_Mem_Write(&hi2c1,
                          (uint16_t)(dev_addr << 1),
                          reg_addr,
                          I2C_MEMADD_SIZE_8BIT,
                          (uint8_t *)reg_data,
                          (uint16_t)len,
                          HAL_MAX_DELAY) == HAL_OK)
    {
        return BME280_OK;
    }

    return BME280_E_COMM_FAIL;
}

void user_delay_us(uint32_t period, void *intf_ptr)
{
    HAL_Delay((period + 999U) / 1000U);
}

/* Send the same message to both serial ports */
void send_uart_message(char *message, uint16_t length)
{
    HAL_UART_Transmit(&huart2,
                      (uint8_t *)message,
                      length,
                      HAL_MAX_DELAY);

    HAL_UART_Transmit(&huart1,
                      (uint8_t *)message,
                      length,
                      HAL_MAX_DELAY);
}

/* USER CODE END 0 */

/**
  * @brief The application entry point.
  */
int main(void)
{
    HAL_Init();

    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    /* USER CODE BEGIN 2 */

    /* Configure BME280 I2C communication */
    bme.intf_ptr = &bme_i2c_addr;
    bme.intf = BME280_I2C_INTF;
    bme.read = user_i2c_read;
    bme.write = user_i2c_write;
    bme.delay_us = user_delay_us;

    /* Initialize BME280 sensor */
    bme_status = bme280_init(&bme);

    if (bme_status != BME280_OK)
    {
        int len = snprintf(uart_buffer,
                           sizeof(uart_buffer),
                           "BME280 initialization failed: %d\r\n",
                           (int)bme_status);

        send_uart_message(uart_buffer, (uint16_t)len);

        while (1)
        {
        }
    }

    /* Configure sensor oversampling settings */
    bme_settings.osr_h = BME280_OVERSAMPLING_1X;
    bme_settings.osr_p = BME280_OVERSAMPLING_1X;
    bme_settings.osr_t = BME280_OVERSAMPLING_1X;

    bme_settings.filter = BME280_FILTER_COEFF_OFF;
    bme_settings.standby_time = BME280_STANDBY_TIME_1000_MS;

    bme_status = bme280_set_sensor_settings(
                    BME280_SEL_OSR_PRESS |
                    BME280_SEL_OSR_TEMP |
                    BME280_SEL_OSR_HUM |
                    BME280_SEL_FILTER,
                    &bme_settings,
                    &bme);

    if (bme_status != BME280_OK)
    {
        int len = snprintf(uart_buffer,
                           sizeof(uart_buffer),
                           "BME280 settings failed: %d\r\n",
                           (int)bme_status);

        send_uart_message(uart_buffer, (uint16_t)len);

        while (1)
        {
        }
    }

    /* Set BME280 to normal operating mode */
    bme_status = bme280_set_sensor_mode(
                    BME280_POWERMODE_NORMAL,
                    &bme);

    if (bme_status != BME280_OK)
    {
        int len = snprintf(uart_buffer,
                           sizeof(uart_buffer),
                           "BME280 mode setting failed: %d\r\n",
                           (int)bme_status);

        send_uart_message(uart_buffer, (uint16_t)len);

        while (1)
        {
        }
    }

    send_uart_message("BME280 initialized successfully\r\n", 34);

    /* USER CODE END 2 */

    /* Infinite loop */
    while (1)
    {
        /* Read temperature, pressure and humidity */
        bme_status = bme280_get_sensor_data(
                        BME280_ALL,
                        &comp_data,
                        &bme);

        if (bme_status == BME280_OK)
        {
            temperature = comp_data.temperature;
            pressure = comp_data.pressure;
            humidity = comp_data.humidity;

            /* Convert values for UART output */
            int32_t temp_x100 =
                (int32_t)(temperature * 100.0);

            int32_t temp_abs =
                (temp_x100 < 0) ? -temp_x100 : temp_x100;

            int32_t pressure_x100 =
                (int32_t)(pressure + 0.5);

            int32_t humidity_x100 =
                (int32_t)(humidity * 100.0 + 0.5);

            int len = snprintf(
                uart_buffer,
                sizeof(uart_buffer),
                "Temperature: %s%ld.%02ld C | Pressure: %ld.%02ld hPa | Humidity: %ld.%02ld %%\r\n",
                (temp_x100 < 0) ? "-" : "",
                (long)(temp_abs / 100),
                (long)(temp_abs % 100),
                (long)(pressure_x100 / 100),
                (long)(pressure_x100 % 100),
                (long)(humidity_x100 / 100),
                (long)(humidity_x100 % 100)
            );

            /* Send sensor readings to PuTTY and Wemos */
            send_uart_message(uart_buffer, (uint16_t)len);
        }
        else
        {
            send_uart_message("BME280 data read failed\r\n", 25);
        }

        HAL_Delay(1000);
    }
}

/**
  * @brief System Clock Configuration
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 84;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                  RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct,
                            FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief I2C1 Initialization Function
  */
static void MX_I2C1_Init(void)
{
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief USART1 Initialization Function
  */
static void MX_USART1_UART_Init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief USART2 Initialization Function
  */
static void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief GPIO Initialization Function
  */
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief Error Handler
  */
void Error_Handler(void)
{
    __disable_irq();

    while (1)
    {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif
