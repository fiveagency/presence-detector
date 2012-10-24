#ifndef __SPI_H
#define __SPI_H

#define  SPInet_ReadWrite  SPI1_ReadWrite
#define  SPInet_Init   SPI1_Init

void	SPI1_Init(void);
unsigned char	SPI1_ReadWrite(unsigned char writedat);

#endif
