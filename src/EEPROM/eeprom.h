#ifndef _EEPROM_H_
#define _EEPROM_H_

int8_t EscreverNaEEprom (uint16_t endereco, uint8_t dado);

int8_t LerDadosDaEEprom (uint16_t endereco, uint8_t *dado);

#endif