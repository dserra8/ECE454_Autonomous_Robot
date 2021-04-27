################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/A0.c \
../Generated_Code/AS1.c \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/AdcLdd1.c \
../Generated_Code/CLK.c \
../Generated_Code/Cpu.c \
../Generated_Code/Main_Control.c \
../Generated_Code/Motor_Control.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PwmLdd1.c \
../Generated_Code/PwmLdd2.c \
../Generated_Code/PwmLdd3.c \
../Generated_Code/SI.c \
../Generated_Code/SI_CLK.c \
../Generated_Code/Servo_Control.c \
../Generated_Code/TU1.c \
../Generated_Code/TU2.c \
../Generated_Code/TU3.c \
../Generated_Code/TU4.c \
../Generated_Code/TU5.c \
../Generated_Code/TimerIntLdd1.c \
../Generated_Code/TimerIntLdd2.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/A0.o \
./Generated_Code/AS1.o \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/CLK.o \
./Generated_Code/Cpu.o \
./Generated_Code/Main_Control.o \
./Generated_Code/Motor_Control.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/PwmLdd2.o \
./Generated_Code/PwmLdd3.o \
./Generated_Code/SI.o \
./Generated_Code/SI_CLK.o \
./Generated_Code/Servo_Control.o \
./Generated_Code/TU1.o \
./Generated_Code/TU2.o \
./Generated_Code/TU3.o \
./Generated_Code/TU4.o \
./Generated_Code/TU5.o \
./Generated_Code/TimerIntLdd1.o \
./Generated_Code/TimerIntLdd2.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/A0.d \
./Generated_Code/AS1.d \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/AdcLdd1.d \
./Generated_Code/CLK.d \
./Generated_Code/Cpu.d \
./Generated_Code/Main_Control.d \
./Generated_Code/Motor_Control.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PwmLdd1.d \
./Generated_Code/PwmLdd2.d \
./Generated_Code/PwmLdd3.d \
./Generated_Code/SI.d \
./Generated_Code/SI_CLK.d \
./Generated_Code/Servo_Control.d \
./Generated_Code/TU1.d \
./Generated_Code/TU2.d \
./Generated_Code/TU3.d \
./Generated_Code/TU4.d \
./Generated_Code/TU5.d \
./Generated_Code/TimerIntLdd1.d \
./Generated_Code/TimerIntLdd2.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Daniel Serrano/Documents/KDSWorkspace/LineCamera2/Static_Code/PDD" -I"C:/Users/Daniel Serrano/Documents/KDSWorkspace/LineCamera2/Static_Code/IO_Map" -I"C:/Users/Daniel Serrano/Documents/KDSWorkspace/LineCamera2/Sources" -I"C:/Users/Daniel Serrano/Documents/KDSWorkspace/LineCamera2/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


