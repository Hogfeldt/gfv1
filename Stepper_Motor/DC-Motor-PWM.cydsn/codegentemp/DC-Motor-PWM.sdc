# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Ase\Semester3\GFV\Git_repos\gfv1\Stepper_Motor\DC-Motor-PWM.cydsn\DC-Motor-PWM.cyprj
# Date: Thu, 21 Feb 2019 09:48:01 GMT
#set_units -time ns
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {UART_1_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 53 105} -nominal_period 2166.6666666666665 [list [get_pins {ClockBlock/dclk_glb_0}]]


# Component constraints for C:\Ase\Semester3\GFV\Git_repos\gfv1\Stepper_Motor\DC-Motor-PWM.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Ase\Semester3\GFV\Git_repos\gfv1\Stepper_Motor\DC-Motor-PWM.cydsn\DC-Motor-PWM.cyprj
# Date: Thu, 21 Feb 2019 09:47:56 GMT
