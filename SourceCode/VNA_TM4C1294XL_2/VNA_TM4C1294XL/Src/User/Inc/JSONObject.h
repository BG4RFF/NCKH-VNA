#ifndef __JSON_OBJECT__
#define __JSON_OBJECT__

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsmn.h"

/* Defines */
#define NUM_OF_MAX_TOKEN 128
#define NUM_OF_MAX_STRING_BUFFER 255

#ifdef __cplusplus
#define __boolType bool
#define __boolTrueValue true
#define __boolFalseValue false
#else
#define __boolType int
#define __boolTrueValue 1
#define __boolFalseValue 0
#endif /* __cplusplus */

/* Data types */
typedef struct JSONObjectStruct
{
    const char *json_string;
    jsmn_parser parser;
    jsmntok_t tokens[NUM_OF_MAX_TOKEN];
    int tokens_counter;
} JSONObject;

typedef enum {
    OPERATION_FAIL = 0,
    OPERATION_SUCCESS
} JSONObject_OperationResultCode;

/* Methods */
int __jsoneq(const char *json, jsmntok_t *tok, const char *s);
JSONObject *JSONObject_CreateObject(void);
JSONObject_OperationResultCode JSONObject_Parse(JSONObject *json_object, const char *json_string);
const char *JSONObject_GetOperationResultName(JSONObject_OperationResultCode code);
JSONObject_OperationResultCode JSONObject_GetString(JSONObject *json_object, const char *key, char **returnValue);
JSONObject_OperationResultCode JSONObject_Getdouble(JSONObject *json_object, const char *key, double *returnValue);
JSONObject_OperationResultCode JSONObject_GetInt(JSONObject *json_object, const char *key, int *returnValue);
JSONObject_OperationResultCode JSONObject_GetLong(JSONObject *json_object, const char *key, long *returnValue);
JSONObject_OperationResultCode JSONObject_GetBool(JSONObject *json_object, const char *key, __boolType *returnValue);
#endif /* __JSON_OBJECT__ */
