#include <system/ksb_ports.h>

void port_out_config(volatile mdr_port_t *port, uint8_t port_out, const port_out_config_t *config) {
    port_out &= 15;

    port->func = (port->func & ~(3 << (port_out * 2))) | (config->mode & 3) << port_out * 2;
    port->pwr = (port->pwr & ~(3 << (port_out * 2))) | (config->pwr & 3) << port_out * 2;

    port->oe = (port->oe & ~(1 << port_out)) | (config->oe & 1) << port_out;
    port->analog = (port->analog & ~(1 << port_out)) | (config->analog_en & 1) << port_out;
    port->gfen = (port->gfen & ~(1 << port_out)) | (config->gfen & 1) << port_out;

    port->pull = (port->pull & ~((1 << port_out) + (1 << (port_out + 16)))) | (((config->pull_down & 1) << port_out) + ((config->pull_up & 1) << (port_out + 16)));
    port->pd = (port->pd & ~((1 << port_out) + (1 << (port_out + 16)))) | (((config->port_pd & 1) << port_out) + ((config->port_shm & 1) << (port_out + 16)));
}

uint8_t digital_read(volatile mdr_port_t *port, uint8_t port_out) {
    return (port->rxtx >> (port_out & 15)) & 1;
}

void digital_write(volatile mdr_port_t *port, uint8_t port_out, uint8_t data) {
    port_out &= 15;
    port->rxtx = (port->rxtx & ~(1 << port_out)) | (data & 1) << port_out;
}

// size_t analog_read(uint8_t port_out) {
//     MDR_ADC->adc2_cfg = 1 | (port_out & 31) << 4;
//     MDR_ADC->adc2_cfg |= 1 << 1; // Если не разделять, то настройки не применятся
//     delay_microseconds(250); // TODO: Надо бы высчитать общее время преобразования
//     size_t read_result = MDR_ADC->adc2_result;
//     MDR_ADC->adc2_cfg = 0;
//     return read_result;
// }

// void analog_write(size_t data) {
//     MDR_DAC->dac2_data = data & 2047;
//     MDR_DAC->cfg = 1 << 3;
// }