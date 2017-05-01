/* fsrinit.c - fsrinit */

#include <xinu.h>

/*--------------------------------------------------------------------------------
 * fsrinit  -  Force sensitive resistor (Pressure sensor) initialization function
 *--------------------------------------------------------------------------------
 */
int32	fsrinit (
		 struct	dentry *devptr
		)
{

	kprintf("Initialising FSR\n");
	kprintf("devnum : %d\n",devptr->dvnum);


        uint32 cm_wkup_adc_tsc_clkctrl_orig = *(uint32*)(CM_WKUP+CM_WKUP_ADC_TSC_CLKCTRL);
	kprintf("cm wakeup start adc tsc clk ctrl%x\n",cm_wkup_adc_tsc_clkctrl_orig);

        uint32 cm_wkup_adc_tsc_clkctrl_new = setbit(cm_wkup_adc_tsc_clkctrl_orig,2-1);
        kprintf("Setting new value to %x\n",cm_wkup_adc_tsc_clkctrl_new);
        *(uint32*)(CM_WKUP+CM_WKUP_ADC_TSC_CLKCTRL)=cm_wkup_adc_tsc_clkctrl_new;
        kprintf("cm wakeup start adc tsc clk ctrl NEw%x\n",*(uint32*)(CM_WKUP+CM_WKUP_ADC_TSC_CLKCTRL));

        uint32 adc_tsc_ctrl_orig = *(uint32 *)(ADC_TSC+CTRL);
        kprintf("orignal val of adc_tsc_ctrl is %x\n",adc_tsc_ctrl_orig);

        uint32 adc_tsc_ctrl_new = setbit(adc_tsc_ctrl_orig,3-1);
        *(uint32 *)(ADC_TSC+CTRL) = adc_tsc_ctrl_new;
        kprintf("new val of adc_tsc_ctrl is %x\n",*(uint32 *)(ADC_TSC+CTRL));


        uint32 stepconfig1_orig = *(uint32 *)(ADC_TSC+STEPCONFIG1);
        kprintf("Step config 1 is %x\n",stepconfig1_orig);

        *(uint32 *)(ADC_TSC+STEPCONFIG1) = setbit(stepconfig1_orig,1-1);
        uint32 stepconfig1_new = *(uint32 *)(ADC_TSC+STEPCONFIG1);
        kprintf("Step config 1 is %x\n",stepconfig1_new);

       // setting step delay
        uint32 stepdelay1_orig = *(uint32 *)(ADC_TSC+STEPDELAY1);
        kprintf("Step delay 1 is %x\n",stepdelay1_orig);

        *(uint32 *)(ADC_TSC+STEPDELAY1) = (0x0F)<<24;
        uint32 stepdelay1_new = *(uint32 *)(ADC_TSC+STEPDELAY1);
	kprintf("Step delay 1 is %x\n",stepdelay1_new);


        kprintf("Now enabling ADC : \n");
	adc_tsc_ctrl_orig = *(uint32 *)(ADC_TSC+CTRL);
        adc_tsc_ctrl_new = setbit(adc_tsc_ctrl_orig,1-1);

        *(uint32 *)(ADC_TSC+CTRL) = adc_tsc_ctrl_new;
        kprintf("new val of adc_tsc_ctrl is %x\n",*(uint32 *)(ADC_TSC+CTRL));


	kprintf("FSR initialized\n");
	return OK;
}
