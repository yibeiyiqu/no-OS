/***************************************************************************//**
 *   @file   ad7606.h
 *   @brief  Header file for the ad7606 Driver.
 *   @author Stefan Popa (stefan.popa@analog.com)
********************************************************************************
 * Copyright 2019(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/
#ifndef AD7606_H_
#define AD7606_H_

enum ad7606_supported_device_ids {
	ID_AD7605_4,
	ID_AD7606_4,
	ID_AD7606_6,
	ID_AD7606_8
};

enum ad7606_range {
	AD7606_RANGE_5V,
	AD7606_RANGE_10V
};

enum ad7606_osr {
	AD7606_OSR_1,
	AD7606_OSR_2,
	AD7606_OSR_4,
	AD7606_OSR_8,
	AD7606_OSR_16,
	AD7606_OSR_32,
	AD7606_OSR_64
};

struct ad7606_chip_info {
	uint8_t num_channels;
	bool has_oversampling;
};

struct ad7606_dev {
	/* SPI */
	spi_desc *spi_desc;
	/* GPIO */
	gpio_desc *gpio_reset;
	gpio_desc *gpio_convst;
	gpio_desc *gpio_busy;
	gpio_desc *gpio_range;
	gpio_desc *gpio_os0;
	gpio_desc *gpio_os1;
	gpio_desc *gpio_os2;
	/* Device Settings */
	uint8_t device_id;
	/* Buffer to store the conv result */
	uint8_t	data[16];
};

struct ad7606_init_param {
	/* SPI */
	spi_init_param spi_init;
	/* GPIO */
	int8_t	gpio_reset;
	int8_t	gpio_convst;
	int8_t	gpio_busy;
	int8_t	gpio_range;
	int8_t	gpio_os0;
	int8_t	gpio_os1;
	int8_t	gpio_os2;
	/* Device Settings */
	uint8_t device_id;
	enum ad7606_range range;
	enum ad7606_osr osr;
};

int32_t ad7606_spi_read_bulk(struct ad7606_dev *dev);
int32_t ad7606_spi_read_samples(struct ad7606_dev *dev,
				uint8_t channel,
				uint16_t *adc_data);
int32_t ad7606_reset(struct ad7606_dev *dev);
int32_t ad7606_request_gpios(struct ad7606_dev *dev,
			     struct ad7606_init_param *init_param);
int32_t ad7606_set_os_ratio(struct ad7606_dev *dev,
			    enum ad7606_osr osr);
int32_t ad7606_init(struct ad7606_dev **device,
		    struct ad7606_init_param *init_param);
int32_t ad7606_remove(struct ad7606_dev *dev);
#endif /* AD7606_H_ */
