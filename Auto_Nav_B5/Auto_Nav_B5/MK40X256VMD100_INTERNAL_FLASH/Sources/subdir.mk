################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/CameraInterface.c" \
"../Sources/Clock.c" \
"../Sources/FlexTimer.c" \
"../Sources/FlexTimer_Motor.c" \
"../Sources/FlexTimer_Servo.c" \
"../Sources/K40_TOWER_BOARD_SUPPORT.c" \
"../Sources/LineDetect.c" \
"../Sources/LineDetect_init.c" \
"../Sources/Pwm_Motor.c" \
"../Sources/Pwm_Servo.c" \
"../Sources/SysTick.c" \
"../Sources/adc16.c" \
"../Sources/arm_cm4.c" \
"../Sources/arm_pid_init_f32.c" \
"../Sources/arm_pid_reset_f32.c" \
"../Sources/main.c" \
"../Sources/readADC.c" \

C_SRCS += \
../Sources/CameraInterface.c \
../Sources/Clock.c \
../Sources/FlexTimer.c \
../Sources/FlexTimer_Motor.c \
../Sources/FlexTimer_Servo.c \
../Sources/K40_TOWER_BOARD_SUPPORT.c \
../Sources/LineDetect.c \
../Sources/LineDetect_init.c \
../Sources/Pwm_Motor.c \
../Sources/Pwm_Servo.c \
../Sources/SysTick.c \
../Sources/adc16.c \
../Sources/arm_cm4.c \
../Sources/arm_pid_init_f32.c \
../Sources/arm_pid_reset_f32.c \
../Sources/main.c \
../Sources/readADC.c \

OBJS += \
./Sources/CameraInterface.obj \
./Sources/Clock.obj \
./Sources/FlexTimer.obj \
./Sources/FlexTimer_Motor.obj \
./Sources/FlexTimer_Servo.obj \
./Sources/K40_TOWER_BOARD_SUPPORT.obj \
./Sources/LineDetect.obj \
./Sources/LineDetect_init.obj \
./Sources/Pwm_Motor.obj \
./Sources/Pwm_Servo.obj \
./Sources/SysTick.obj \
./Sources/adc16.obj \
./Sources/arm_cm4.obj \
./Sources/arm_pid_init_f32.obj \
./Sources/arm_pid_reset_f32.obj \
./Sources/main.obj \
./Sources/readADC.obj \

C_DEPS += \
./Sources/CameraInterface.d \
./Sources/Clock.d \
./Sources/FlexTimer.d \
./Sources/FlexTimer_Motor.d \
./Sources/FlexTimer_Servo.d \
./Sources/K40_TOWER_BOARD_SUPPORT.d \
./Sources/LineDetect.d \
./Sources/LineDetect_init.d \
./Sources/Pwm_Motor.d \
./Sources/Pwm_Servo.d \
./Sources/SysTick.d \
./Sources/adc16.d \
./Sources/arm_cm4.d \
./Sources/arm_pid_init_f32.d \
./Sources/arm_pid_reset_f32.d \
./Sources/main.d \
./Sources/readADC.d \

OBJS_QUOTED += \
"./Sources/CameraInterface.obj" \
"./Sources/Clock.obj" \
"./Sources/FlexTimer.obj" \
"./Sources/FlexTimer_Motor.obj" \
"./Sources/FlexTimer_Servo.obj" \
"./Sources/K40_TOWER_BOARD_SUPPORT.obj" \
"./Sources/LineDetect.obj" \
"./Sources/LineDetect_init.obj" \
"./Sources/Pwm_Motor.obj" \
"./Sources/Pwm_Servo.obj" \
"./Sources/SysTick.obj" \
"./Sources/adc16.obj" \
"./Sources/arm_cm4.obj" \
"./Sources/arm_pid_init_f32.obj" \
"./Sources/arm_pid_reset_f32.obj" \
"./Sources/main.obj" \
"./Sources/readADC.obj" \

OBJS_OS_FORMAT += \
./Sources/CameraInterface.obj \
./Sources/Clock.obj \
./Sources/FlexTimer.obj \
./Sources/FlexTimer_Motor.obj \
./Sources/FlexTimer_Servo.obj \
./Sources/K40_TOWER_BOARD_SUPPORT.obj \
./Sources/LineDetect.obj \
./Sources/LineDetect_init.obj \
./Sources/Pwm_Motor.obj \
./Sources/Pwm_Servo.obj \
./Sources/SysTick.obj \
./Sources/adc16.obj \
./Sources/arm_cm4.obj \
./Sources/arm_pid_init_f32.obj \
./Sources/arm_pid_reset_f32.obj \
./Sources/main.obj \
./Sources/readADC.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/CameraInterface.obj: ../Sources/CameraInterface.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/CameraInterface.args" -o "Sources/CameraInterface.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/Clock.obj: ../Sources/Clock.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/Clock.args" -o "Sources/Clock.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/FlexTimer.obj: ../Sources/FlexTimer.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/FlexTimer.args" -o "Sources/FlexTimer.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/FlexTimer_Motor.obj: ../Sources/FlexTimer_Motor.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/FlexTimer_Motor.args" -o "Sources/FlexTimer_Motor.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/FlexTimer_Servo.obj: ../Sources/FlexTimer_Servo.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/FlexTimer_Servo.args" -o "Sources/FlexTimer_Servo.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/K40_TOWER_BOARD_SUPPORT.obj: ../Sources/K40_TOWER_BOARD_SUPPORT.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/K40_TOWER_BOARD_SUPPORT.args" -o "Sources/K40_TOWER_BOARD_SUPPORT.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/LineDetect.obj: ../Sources/LineDetect.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/LineDetect.args" -o "Sources/LineDetect.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/LineDetect_init.obj: ../Sources/LineDetect_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/LineDetect_init.args" -o "Sources/LineDetect_init.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Pwm_Motor.obj: ../Sources/Pwm_Motor.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/Pwm_Motor.args" -o "Sources/Pwm_Motor.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Pwm_Servo.obj: ../Sources/Pwm_Servo.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/Pwm_Servo.args" -o "Sources/Pwm_Servo.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SysTick.obj: ../Sources/SysTick.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/SysTick.args" -o "Sources/SysTick.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/adc16.obj: ../Sources/adc16.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/adc16.args" -o "Sources/adc16.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/arm_cm4.obj: ../Sources/arm_cm4.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/arm_cm4.args" -o "Sources/arm_cm4.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/arm_pid_init_f32.obj: ../Sources/arm_pid_init_f32.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/arm_pid_init_f32.args" -o "Sources/arm_pid_init_f32.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/arm_pid_reset_f32.obj: ../Sources/arm_pid_reset_f32.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/arm_pid_reset_f32.args" -o "Sources/arm_pid_reset_f32.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/main.args" -o "Sources/main.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/readADC.obj: ../Sources/readADC.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/readADC.args" -o "Sources/readADC.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


