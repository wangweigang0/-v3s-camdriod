/* Copyright (c) 2008 -2014 Espressif System.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *
 *  sdio stub code for RK
 */

//#include <mach/gpio.h>
//#include <mach/iomux.h>
#include <mach/sys_config.h>

#define ESP8089_DRV_VERSION "2.26"

static int wifi_sdc_id = -1;

extern void wifi_pm_power(int on);
extern void sunxi_mci_rescan_card(unsigned id, unsigned insert);
extern int sunxi_mci_check_r1_ready_with_id(int id, unsigned ms);


void sif_platform_rescan_card(unsigned insert)
{
	if (wifi_sdc_id != -1)
		sunxi_mci_rescan_card(wifi_sdc_id,insert);
}

void sif_platform_reset_target(void)
{
	printk("=======================================================\n");
	printk("==== sif_platform_reset_target ====\n");
	printk("=======================================================\n");
}

void sif_platform_target_poweroff(void)
{
	printk("=======================================================\n");
	printk("==== Dislaunching Wi-Fi driver! (Powered by Rockchip) ====\n");
	printk("=======================================================\n");
	printk("Espressif ESP8089 SDIO WiFi driver (Powered by Rockchip, Ver2.26(01/22/2016),Drv: %s) exit.\n", ESP8089_DRV_VERSION);

	wifi_pm_power(0);
	mdelay(100);
}

void sif_platform_target_poweron(void)
{
	script_item_u val;
	script_item_value_type_e type;

	printk("=======================================================\n");
	printk("==== Launching Wi-Fi driver! (Powered by Rockchip) ====\n");
	printk("=======================================================\n");
	printk("Espressif ESP8089 SDIO WiFi driver (Powered by Rockchip, Ver2.25(01/22/2016),Drv: %s) init.\n", ESP8089_DRV_VERSION);

	type = script_get_item("wifi_para", "wifi_sdc_id", &val);
	if (SCIRPT_ITEM_VALUE_TYPE_INT != type) {
		printk(KERN_ERR"%s:get wifi_sdc_id error!!\n",__func__);
		return;
	} 

	wifi_sdc_id = val.val;

	wifi_pm_power(1);
	mdelay(100);
}

void sif_platform_target_speed(int high_speed)
{
	printk(KERN_ERR"%s\n!!!!!!!!!!!!!!!!",__func__);
}

void sif_platform_check_r1_ready(struct esp_pub *epub)
{
	if (sunxi_mci_check_r1_ready_with_id(wifi_sdc_id,1000))
		printk(KERN_ERR"%s\n error!!,__func__");
}


#ifdef ESP_ACK_INTERRUPT
//extern void sdmmc_ack_interrupt(struct mmc_host *mmc); libing

void sif_platform_ack_interrupt(struct esp_pub *epub)
{
        struct esp_sdio_ctrl *sctrl = NULL;
        struct sdio_func *func = NULL;

		printk(KERN_ERR"%s\n!!!!!!!!!!!!!!!!",__func__);
		
       // ASSERT(epub != NULL);
        sctrl = (struct esp_sdio_ctrl *)epub->sif;
        func = sctrl->func;
       // ASSERT(func != NULL);

       // sdmmc_ack_interrupt(func->card->host);libing

}
#endif //ESP_ACK_INTERRUPT

