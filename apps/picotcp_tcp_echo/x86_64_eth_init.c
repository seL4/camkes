/*
 * Copyright 2019, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <camkes.h>
#include <utils/util.h>
#include <ethdrivers/raw.h>
#include <ethdrivers/intel.h>


int ethif_init(struct eth_driver *eth_driver, ps_io_ops_t *io_ops)
{
    ethif_intel_config_t *eth_config = calloc(1, sizeof(ethif_intel_config_t) + sizeof(ps_irq_t));
    *eth_config = (ethif_intel_config_t) {
        /* Ethdriver component dataport */
        .bar0 = (void *)EthDriver,
        .prom_mode = (uint8_t) promiscuous_mode,
        .num_irqs = 1
    };

    eth_config->irq_info[0] = (ps_irq_t) {
        .type = PS_IOAPIC, .ioapic = { .ioapic = 0, .pin = 20,
                                       .level = 1, .polarity = 1,
                                       .vector = 20
                                     }
    };

    int error = ethif_e82574_init(eth_driver, *io_ops, eth_config);
    if (error) {
        ZF_LOGF("ERROR init ethernet");
        return error;
    }

    return 0;
}

static int init_device(ps_io_ops_t *io_ops)
{

    struct eth_driver *eth_driver;
    int error = ps_calloc(&io_ops->malloc_ops, 1, sizeof(*eth_driver), (void **)&eth_driver);
    if (error) {
        ZF_LOGE("Failed to allocate struct for ethdriver");
        return error;
    }

    error = ethif_init(eth_driver, io_ops);
    if (error) {
        ZF_LOGE("Failed to initialize ethernet driver");
        return error;
    }
    return 0;
}


CAMKES_PRE_INIT_MODULE_DEFINE(ethdriver_setup, init_device);

