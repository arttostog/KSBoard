#include <ksboard.h>

void delay(unsigned int milliseconds) {
    SYS_TICK->load = LSI_FREQUENCY - 1;
    SYS_TICK->val = 0;
    SYS_TICK->ctrl = SYS_TICK_CTRL_ENABLE;
    
    while (milliseconds)
        if (SYS_TICK->ctrl & SYS_TICK_CTRL_COUNTFLAG)
            --milliseconds;
    
    SYS_TICK->ctrl = 0;
}

void pin_config(volatile mdr_port_t *port, unsigned int port_out, const pin_config_t *config) {
    port_out &= 15;
    
    port->oe = (port->oe & ~(1 << port_out)) | ((config->is_output & 1) << port_out);

    port->func = (port->func & ~(3 << (port_out * 2))) | ((config->function & 3) << (port_out * 2));

    port->analog = (port->analog & ~(1 << port_out)) | ((config->is_digital & 1) << port_out);

    port->pull = (port->pull & ~((1 << port_out) + (1 << (port_out + 16)))) | (((config->enable_pull_down & 1) << port_out) + ((config->enable_pull_up & 1) << (port_out + 16)));

    port->pd = (port->pd & ~((1 << port_out) + (1 << (port_out + 16)))) | (((config->pd_mode & 1) << port_out) + ((config->shm_mode & 1) << (port_out + 16)));

    port->pwr = (port->pwr * ~(3 << (port_out * 2))) | ((config->power_mode & 3) << (port_out * 2));

    port->gfen = (port->gfen & ~(1 << port_out)) | ((config->use_filter & 1) << port_out);
}

unsigned int pin_digital_read(volatile mdr_port_t *port, unsigned int port_out) {
    return (port->rxtx & (1 << port_out)) >> port_out;
}

void pin_digital_write(volatile mdr_port_t *port, unsigned int port_out, unsigned int data) {
    port->rxtx = (port->rxtx & ~(1 << port_out)) | ((data & 1) << port_out);
}

// unsigned int pin_analog_read(volatile mdr_port_t *port, unsigned int port_out) {
//     return 0;
// }

// void pin_analog_write(volatile mdr_port_t *port, unsigned int port_out, unsigned int data) {

// }