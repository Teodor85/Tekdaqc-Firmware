/*
 * Copyright 2013 Tenkiv, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */

/**
 * @file Tekdaqc_CommandInterpreter.h
 * @brief Header file for the Tekdaqc_CommandInterpreter algorithm.
 *
 * Contains public definitions and data types for the Tekdaqc_CommandInterpreter.
 *
 * @author Jared Woolston (jwoolston@tenkiv.com)
 * @since v1.0.0.0
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TEKDAQC_COMMAND_INTERPRETER_H_
#define TEKDAQC_COMMAND_INTERPRETER_H_

/* Define to provide proper behavior with C++ compilers ----------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/*--------------------------------------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------------------------------------*/

#include "Tekdaqc_Config.h"
#include "Tekdaqc_Debug.h"
#include "Analog_Input.h"
#include "Digital_Input.h"
#include "Digital_Output.h"
#include <string.h>

/** @addtogroup tekdaqc_firmware Tekdaqc Firmware
 * @{
 */

/** @addtogroup command_interpreter Command Interpreter
  * @{
  */

/*--------------------------------------------------------------------------------------------------------*/
/* EXPORTED CONSTANTS */
/*--------------------------------------------------------------------------------------------------------*/

/*
 * The following section defines the strings for all possible parameters. The source file can then
 * pull them into the various arrays as needed.
 */

/**
 * @def PARAMETER_INPUT
 * @brief String constant definition for the INPUT parameter.
 */
#define PARAMETER_INPUT 		"INPUT"

/**
 * @def PARAMETER_RATE
 * @brief String constant definition for the RATE parameter.
 */
#define PARAMETER_RATE			"RATE"

/**
 * @def PARAMETER_GAIN
 * @brief String constant definition for the GAIN parameter.
 */
#define PARAMETER_GAIN			"GAIN"

/**
 * @def PARAMETER_BUFFER
 * @brief String constant definition for the BUFFER parameter.
 */
#define PARAMETER_BUFFER		"BUFFER"

/**
 * @def PARAMETER_NUMBER
 * @brief String constant definition for the NUMBER parameter.
 */
#define PARAMETER_NUMBER		"NUMBER"

/**
 * @def PARAMETER_NAME
 * @brief String constant definition for the NAME parameter.
 */
#define PARAMETER_NAME			"NAME"

/**
 * @def PARAMETER_OUTPUT
 * @brief String constant definition for the OUTPUT parameter.
 */
#define PARAMETER_OUTPUT		"OUTPUT"

/**
 * @def PARAMETER_STATE
 * @brief String constant definition for the STATE parameter.
 */
#define PARAMETER_STATE			"STATE"

/**
 * @def PARAMETER_VALUE
 * @brief String constant definition for the VALUE parameter.
 */
#define PARAMETER_VALUE			"VALUE"

/**
 * @def NUM_COMMANDS
 * @brief The total number of commands known by this board.
 */
#define NUM_COMMANDS 28

/**
 * @def TELNET_EOF
 * @brief The character which signifies the EOF character for Telnet.
 */
#define TELNET_EOF ((char) '\r')

/*--------------------------------------------------------------------------------------------------------*/
/* EXPORTED TYPES */
/*--------------------------------------------------------------------------------------------------------*/

/**
 * @brief Enumeration of all commands known by this board.
 * This is an enumeration of all commands known by this board. Because we are explicitly relying
 * on the assigned ordinal value, we define it to prevent any issues with other compilers. */
typedef enum {
	COMMAND_LIST_ANALOG_INPUTS = 0,
	COMMAND_READ_ADC_REGISTERS = 1,
	COMMAND_READ_ANALOG_INPUT = 2,
	COMMAND_ADD_ANALOG_INPUT = 3,
	COMMAND_REMOVE_ANALOG_INPUT = 4,
	COMMAND_CHECK_ANALOG_INPUT = 5,
	COMMAND_SYSTEM_GCAL = 6,
	COMMAND_SYSTEM_CAL = 7,
	COMMAND_LIST_DIGITAL_INPUTS = 8,
	COMMAND_READ_DIGITAL_INPUT = 9,
	COMMAND_ADD_DIGITAL_INPUT = 10,
	COMMAND_REMOVE_DIGITAL_INPUT = 11,
	COMMAND_LIST_DIGITAL_OUTPUTS = 12,
	COMMAND_SET_DIGITAL_OUTPUT = 13,
	COMMAND_READ_DIGITAL_OUTPUT = 14,
	COMMAND_ADD_DIGITAL_OUTPUT = 15,
	COMMAND_REMOVE_DIGITAL_OUTPUT = 16,
	COMMAND_CLEAR_DIG_OUTPUT_FAULT = 17,
	COMMAND_DISCONNECT = 18,
	COMMAND_UPGRADE = 19,
	COMMAND_IDENTIFY = 20,
	COMMAND_SAMPLE = 21,
	COMMAND_HALT = 22,
	COMMAND_SET_RTC = 23,
	COMMAND_SET_USER_MAC = 24,
	COMMAND_SET_STATIC_IP = 25,
	COMMAND_GET_CALIBRATION_STATUS = 26,
	COMMAND_NONE = 27
} Command_t;

/**
 * @brief Data structure for maintaining the state of the command interpreter.
 */
typedef struct {
	char command_buffer[MAX_COMMANDLINE_LENGTH]; /**< A buffer which stores the currently being built command. */
	uint16_t buffer_position; /**< The current write position in the command buffer. */
} Tekdaqc_CommandInterpreter_t;

/*--------------------------------------------------------------------------------------------------------*/
/* EXPORTED PARAMETER LISTS */
/*--------------------------------------------------------------------------------------------------------*/

/**
 * @def NUM_LIST_ANALOG_INPUTS_PARAMS
 * @brief The number of parameters for the LIST_ANALOG_INPUTS command.
 */
#define NUM_LIST_ANALOG_INPUTS_PARAMS 0
/* Prototype the LIST_ANALOG_INPUTS command params array */
extern const char* LIST_ANALOG_INPUTS_PARAMS[NUM_LIST_ANALOG_INPUTS_PARAMS];

/**
 * @def NUM_READ_ADC_REGISTERS_PARAMS
 * @brief The number of parameters for the READ_ADC_REGISTERS command.
 */
#define NUM_READ_ADC_REGISTERS_PARAMS 0
/* Prototype the READ_ADC_REGISTERS command params array */
extern const char* READ_ADC_REGISTERS_PARAMS[NUM_READ_ADC_REGISTERS_PARAMS];

/**
 * @def NUM_READ_ANALOG_INPUT_PARAMS
 * @brief The number of parameters for the READ_ANALOG_INPUT command.
 */
#define NUM_READ_ANALOG_INPUT_PARAMS 2
/* Prototype the READ_ANALOG_INPUT command params array */
extern const char* READ_ANALOG_INPUT_PARAMS[NUM_READ_ANALOG_INPUT_PARAMS];

/**
 * @def NUM_ADD_ANALOG_INPUT_PARAMS
 * @brief The number of parameters for the ADD_ANALOG_INPUT command.
 */
#define NUM_ADD_ANALOG_INPUT_PARAMS 5
/* Prototype the ADD_ANALOG_INPUT command params array */
extern const char* ADD_ANALOG_INPUT_PARAMS[NUM_ADD_ANALOG_INPUT_PARAMS];

/**
 * @def NUM_REMOVE_ANALOG_INPUT_PARAMS
 * @brief The number of parameters for the REMOVE_ANALOG_INPUT command.
 */
#define NUM_REMOVE_ANALOG_INPUT_PARAMS 1
/* Prototype the REMOVE_ANALOG_INPUT command params array */
extern const char* REMOVE_ANALOG_INPUT_PARAMS[NUM_REMOVE_ANALOG_INPUT_PARAMS];

/**
 * @def NUM_CHECK_ANALOG_INPUT_PARAMS
 * @brief The number of parameters for the CHECK_ANALOG_INPUT command.
 */
#define NUM_CHECK_ANALOG_INPUT_PARAMS 1
/* Prototype the CHECK_ANALOG_INPUT command params array */
extern const char* CHECK_ANALOG_INPUT_PARAMS[NUM_CHECK_ANALOG_INPUT_PARAMS];

/**
 * @def NUM_SYSTEM_GCAL_PARAMS
 * @brief The number of parameters for the SYSTEM_GCAL command.
 */
#define NUM_SYSTEM_GCAL_PARAMS 4
/* Prototype the SYSTEM_GCAL command params array */
extern const char* SYSTEM_GCAL_PARAMS[NUM_SYSTEM_GCAL_PARAMS];

/**
 * @def NUM_SYSTEM_CAL_PARAMS
 * @brief The number of parameters for the SYSTEM_CAL command.
 */
#define NUM_SYSTEM_CAL_PARAMS 3
/* Prototype the SYSTEM_CAL command params array */
extern const char* SYSTEM_CAL_PARAMS[NUM_SYSTEM_CAL_PARAMS];

/**
 * @def NUM_LIST_DIGITAL_INPUTS_PARAMS
 * @brief The number of parameters for the LIST_DIGITAL_INPUTS command.
 */
#define NUM_LIST_DIGITAL_INPUTS_PARAMS 0
/* Prototype the LIST_DIGITAL_INPUTS command params array */
extern const char* LIST_DIGITAL_INPUTS_PARAMS[NUM_LIST_DIGITAL_INPUTS_PARAMS];

/**
 * @def NUM_READ_DIGITAL_INPUT_PARAMS
 * @brief The number of parameters for the READ_DIGITAL_INPUT command.
 */
#define NUM_READ_DIGITAL_INPUT_PARAMS 2
/* Prototype the READ_DIGITAL_INPUT command params array */
extern const char* READ_DIGITAL_INPUT_PARAMS[NUM_READ_DIGITAL_INPUT_PARAMS];

/**
 * @def NUM_ADD_DIGITAL_INPUT_PARAMS
 * @brief The number of parameters for the ADD_DIGITAL_INPUT command.
 */
#define NUM_ADD_DIGITAL_INPUT_PARAMS 2
/* Prototype the ADD_DIGITAL_INPUT command params array */
extern const char* ADD_DIGITAL_INPUT_PARAMS[NUM_ADD_DIGITAL_INPUT_PARAMS];

/**
 * @def NUM_REMOVE_DIGITAL_INPUT_PARAMS
 * @brief The number of parameters for the REMOVE_DIGITAL_INPUT command.
 */
#define NUM_REMOVE_DIGITAL_INPUT_PARAMS 1
/* Prototype the REMOVE_DIGITAL_INPUT command params array */
extern const char* REMOVE_DIGITAL_INPUT_PARAMS[NUM_REMOVE_DIGITAL_INPUT_PARAMS];

/**
 * @def NUM_LIST_DIGITAL_OUTPUTS_PARAMS
 * @brief The number of parameters for the LIST_DIGITAL_OUTPUTS command.
 */
#define NUM_LIST_DIGITAL_OUTPUTS_PARAMS 0
/* Prototype the LIST_DIGITAL_OUTPUTS command params array */
extern const char* LIST_DIGITAL_OUTPUTS_PARAMS[NUM_LIST_DIGITAL_OUTPUTS_PARAMS];

/**
 * @def NUM_SET_DIGITAL_OUTPUT_PARAMS
 * @brief The number of parameters for the SET_DIGITAL_OUTPUT command.
 */
#define NUM_SET_DIGITAL_OUTPUT_PARAMS 2
/* Prototype the SET_DIGITAL_OUTPUT command params array */
extern const char* SET_DIGITAL_OUTPUT_PARAMS[NUM_SET_DIGITAL_OUTPUT_PARAMS];

/**
 * @def NUM_READ_DIGITAL_OUTPUT_PARAMS
 * @brief The number of parameters for the READ_DIGITAL_OUTPUT command.
 */
#define NUM_READ_DIGITAL_OUTPUT_PARAMS 2
/* Prototype the READ_DIGITAL_OUTPUT command params array */
extern const char* READ_DIGITAL_OUTPUT_PARAMS[NUM_READ_DIGITAL_OUTPUT_PARAMS];

/**
 * @def NUM_ADD_DIGITAL_OUTPUT_PARAMS
 * @brief The number of parameters for the ADD_DIGITAL_OUTPUT command.
 */
#define NUM_ADD_DIGITAL_OUTPUT_PARAMS 2
/* Prototype the ADD_DIGITAL_OUTPUT command params array */
extern const char* ADD_DIGITAL_OUTPUT_PARAMS[NUM_ADD_DIGITAL_OUTPUT_PARAMS];

/**
 * @def NUM_REMOVE_DIGITAL_OUTPUT_PARAMS
 * @brief The number of parameters for the REMOVE_DIGITAL_OUTPUT command.
 */
#define NUM_REMOVE_DIGITAL_OUTPUT_PARAMS 1
/* Prototype the REMOVE_DIGITAL_OUTPUT command params array */
extern const char* REMOVE_DIGITAL_OUTPUT_PARAMS[NUM_REMOVE_DIGITAL_OUTPUT_PARAMS];

/**
 * @def NUM_CLEAR_DIG_OUTPUT_FAULT_PARAMS
 * @brief The number of parameters for the CLEAR_DIG_OUTPUT_FAULT command.
 */
#define NUM_CLEAR_DIG_OUTPUT_FAULT_PARAMS 1
/* Prototype the CLEAR_DIG_OUTPUT_FAULT command params array */
extern const char* CLEAR_DIG_OUTPUT_FAULT_PARAMS[NUM_CLEAR_DIG_OUTPUT_FAULT_PARAMS];

/**
 * @def NUM_DISCONNECT_PARAMS
 * @brief The number of parameters for the DISCONNECT command.
 */
#define NUM_DISCONNECT_PARAMS 0
/* Prototype the DISCONNECT command params array */
extern const char* DISCONNECT_PARAMS[NUM_DISCONNECT_PARAMS];

/**
 * @def NUM_UPGRADE_PARAMS
 * @brief The number of parameters for the UPGRADE command.
 */
#define NUM_UPGRADE_PARAMS 0
/* Prototype the UPGRADE command params array */
extern const char* UPGRADE_PARAMS[NUM_UPGRADE_PARAMS];

/**
 * @def NUM_IDENTIFY_PARAMS
 * @brief The number of parameters for the IDENTIFY command.
 */
#define NUM_IDENTIFY_PARAMS 0
/* Prototype the IDENTIFY command params array */
extern const char* IDENTIFY_PARAMS[NUM_IDENTIFY_PARAMS];

/**
 * @def NUM_SAMPLE_PARAMS
 * @brief The number of parameters for the SAMPLE command.
 */
#define NUM_SAMPLE_PARAMS 1
/* Prototype the SAMPLE command params array */
extern const char* SAMPLE_PARAMS[NUM_SAMPLE_PARAMS];

/**
 * @def NUM_HALT_PARAMS
 * @brief The number of parameters for the HALT command.
 */
#define NUM_HALT_PARAMS 0
/* Prototype the HALT command params array */
extern const char* HALT_PARAMS[NUM_HALT_PARAMS];

/**
 * @def NUM_SET_RTC_PARAMS
 * @brief The number of parameters for the SET_RTC command.
 */
#define NUM_SET_RTC_PARAMS 1
/* Prototype the SET_RTC command params array */
extern const char* SET_RTC_PARAMS[NUM_SET_RTC_PARAMS];

/**
 * @def NUM_SET_USER_MAC_PARAMS
 * @brief The number of parameters for the SET_USER_MAC command.
 */
#define NUM_SET_USER_MAC_PARAMS 1
/* Prototype the SET_USER_MAC command params array */
extern const char* SET_USER_MAC_PARAMS[NUM_SET_USER_MAC_PARAMS];

/**
 * @def NUM_SET_STATIC_IP_PARAMS
 * @brief The number of parameters for the SET_STATIC_IP command.
 */
#define NUM_SET_STATIC_IP_PARAMS 1
/* Prototype the SET_STATIC_IP command params array */
extern const char* SET_STATIC_IP_PARAMS[NUM_SET_STATIC_IP_PARAMS];

/**
 * @def NUM_GET_CALIBRATION_STATUS_PARAMS
 * @brief The number of parameters for the GET_CALIBRATION_STATUS command.
 */
#define NUM_GET_CALIBRATION_STATUS_PARAMS 0
/* Prototype the GET_CALIBRATION_STATUS command params array */
extern const char* GET_CALIBRATION_STATUS_PARAMS[NUM_GET_CALIBRATION_STATUS_PARAMS];

/**
 * @def NUM_NONE_PARAMS
 * @brief The number of parameters for the NONE command.
 */
#define NUM_NONE_PARAMS 0
/* Prototype the NONE command params array */
extern const char* NONE_PARAMS[NUM_NONE_PARAMS];

/*--------------------------------------------------------------------------------------------------------*/
/* PUBLIC METHODS */
/*--------------------------------------------------------------------------------------------------------*/

/**
 * @brief Instantiates and allocates the command interpreter
 */
void CreateCommandInterpreter(void);

/**
 * @brief Adds a character to the command parser's buffer.
 */
void Command_AddChar(const char character);

/**
 * @brief Clears the entire contents of the command parser's buffer.
 */
void ClearCommandBuffer(void);

/**
 * @brief Gets the index of the specified argument from the list of parameters.
 */
int8_t GetIndexOfArgument(char keys[][MAX_COMMANDPART_LENGTH], const char* target, uint8_t total);

/**
 * @brief Retrieve the last set function error.
 */
Tekdaqc_Function_Error_t GetLastFunctionError(void);


#ifdef __cplusplus
}
#endif

/**
 * @}
 */

/**
 * @}
 */

#endif /* TEKDAQC_COMMAND_INTERPRETER_H_ */
