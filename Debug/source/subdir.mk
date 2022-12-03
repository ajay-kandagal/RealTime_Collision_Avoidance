################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/i2c.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/timer.c \
../source/vl53l0x.c 

C_DEPS += \
./source/i2c.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/timer.d \
./source/vl53l0x.d 

OBJS += \
./source/i2c.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/timer.o \
./source/vl53l0x.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\ajayk\Documents\MCUXpressoIDE_11.6.0_8187\workspace\RealTime_Collision_Avoidance\board" -I"C:\Users\ajayk\Documents\MCUXpressoIDE_11.6.0_8187\workspace\RealTime_Collision_Avoidance\source" -I"C:\Users\ajayk\Documents\MCUXpressoIDE_11.6.0_8187\workspace\RealTime_Collision_Avoidance" -I"C:\Users\ajayk\Documents\MCUXpressoIDE_11.6.0_8187\workspace\RealTime_Collision_Avoidance\drivers" -I"C:\Users\ajayk\Documents\MCUXpressoIDE_11.6.0_8187\workspace\RealTime_Collision_Avoidance\CMSIS" -I"C:\Users\ajayk\Documents\MCUXpressoIDE_11.6.0_8187\workspace\RealTime_Collision_Avoidance\utilities" -I"C:\Users\ajayk\Documents\MCUXpressoIDE_11.6.0_8187\workspace\RealTime_Collision_Avoidance\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/i2c.d ./source/i2c.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/timer.d ./source/timer.o ./source/vl53l0x.d ./source/vl53l0x.o

.PHONY: clean-source

