@echo off

REM stm32 flash download script(tested under WinXP). Call this Script and pass the directory where the
REM .bin file is located as a parameter, e.g. flash_download C:\MyProjects\STM32Test. The .bin file
REM is expected to be called main.bin, in case of a different name just change the line below where
REM the STMFlashLoader is invoked. In Eclipse a convenient way to pass the project location is to use
REM the ${project_loc} variable when calling thi sscript as an External Tool.

REM enter stm32 boot mode

cd D:\UAV\mAP\tomC\eclipseIDE\workspace\
java -jar ftdi_control.jar enterbootmode

echo invoking STMFlashloader to write binary file %1\main\main.bin to flash

C:\Programme\STMicroelectronics\Software\FlashLoaderDemonstrator\STMFlashLoader.exe -c --pn 4 --br 460800 -i STM32_High-density_512K -e --all -d --a 8000000  --fn %1\bin\main.bin

REM leave stm32 boot mode, and reset the stm32 device

cd D:\UAV\mAP\tomC\eclipseIDE\workspace\
java -jar ftdi_control.jar leavebootmode