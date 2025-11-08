#include <system/ksb_ports.h>

void port_out_config(volatile mdr_port_t *port, bit_depth_t port_out, const port_out_config_t *config) {
    port_out &= 15;

    port->func = (port->func & ~(3 << (port_out * 2))) | (config->function & 3) << port_out * 2;
    port->pwr = (port->pwr & ~(3 << (port_out * 2))) | (config->power_mode & 3) << port_out * 2;

    port->oe = (port->oe & ~(1 << port_out)) | (config->is_output & 1) << port_out;
    port->analog = (port->analog & ~(1 << port_out)) | (config->is_digital & 1) << port_out;
    port->gfen = (port->gfen & ~(1 << port_out)) | (config->use_filter & 1) << port_out;

    port->pull = (port->pull & ~((1 << port_out) + (1 << (port_out + 16)))) | (((config->enable_pull_down & 1) << port_out) + ((config->enable_pull_up & 1) << (port_out + 16)));
    port->pd = (port->pd & ~((1 << port_out) + (1 << (port_out + 16)))) | (((config->pd_mode & 1) << port_out) + ((config->shm_mode & 1) << (port_out + 16)));
}

bit_depth_t digital_read(volatile mdr_port_t *port, bit_depth_t port_out) {
    return (port->rxtx >> port_out) & 1;
}

void digital_write(volatile mdr_port_t *port, bit_depth_t port_out, bit_depth_t data) {
    port->rxtx = (port->rxtx & ~(1 << port_out)) | (data & 1) << port_out;
}

bit_depth_t analog_read(bit_depth_t port_out) {
    MDR_ADC->adc2_cfg = 1 | (port_out & 31) << 4;
    MDR_ADC->adc2_cfg |= 1 << 1; // Если не разделять, то настройки не применятся
    delay_microseconds(250); // TODO: Надо бы высчитать общее время преобразования
    bit_depth_t read_result = MDR_ADC->adc2_result;
    MDR_ADC->adc2_cfg = 0;
    return read_result;
}

void analog_write(bit_depth_t data) {
    MDR_DAC->dac2_data = data & 2047;
    MDR_DAC->cfg = 1 << 3;
}