#include "JSONObject.h"

int __jsoneq(const char *json, jsmntok_t *tok, const char *s)
{
    if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
        strncmp(json + tok->start, s, tok->end - tok->start) == 0)
    {
        return 0;
    }
    return -1;
}

JSONObject *JSONObject_CreateObject(void)
{
    JSONObject *returnObject = (JSONObject *)malloc(sizeof(JSONObject));

    returnObject->tokens_counter = 0;
    jsmn_init(&(returnObject->parser));

    return returnObject;
}

JSONObject_OperationResultCode JSONObject_Parse(JSONObject *json_object, const char *json_string)
{
    json_object->json_string = json_string;
    json_object->tokens_counter = jsmn_parse(&(json_object->parser), json_string, strlen(json_string), (json_object->tokens), sizeof(json_object->tokens) / sizeof((json_object->tokens)[0]));

    if (json_object->tokens_counter < 0)
    {
        return OPERATION_FAIL;
    }
    else if (json_object->tokens_counter < 1 || (json_object->tokens)[0].type != JSMN_OBJECT)
    {
        return OPERATION_FAIL;
    }
    else
    {
        return OPERATION_SUCCESS;
    }
}

const char *JSONObject_GetOperationResultName(JSONObject_OperationResultCode code)
{
    static const char *JSONObject_OperationResultCodeName[] = {
        "OPERATION_FAIL",
        "OPERATION_SUCCESS"};

    return JSONObject_OperationResultCodeName[code];
}

JSONObject_OperationResultCode JSONObject_GetString(JSONObject *json_object, const char *key, char **returnValue)
{
    int i = 1;
    *returnValue = (char *)malloc(sizeof(char) * NUM_OF_MAX_STRING_BUFFER);

    for (i = 1; i < json_object->tokens_counter; i++)
    {
        if (__jsoneq(json_object->json_string, &(json_object->tokens[i]), key) == 0)
        {
            sprintf(*returnValue, "%.*s", json_object->tokens[i + 1].end - json_object->tokens[i + 1].start, json_object->json_string + json_object->tokens[i + 1].start);
            break;
        }
    }

    if (i == json_object->tokens_counter)
    {
        return OPERATION_FAIL;
    }
    else
    {
        return OPERATION_SUCCESS;
    }
}

JSONObject_OperationResultCode JSONObject_GetFloat(JSONObject *json_object, const char *key, float *returnValue)
{
    char *strValue;
    JSONObject_OperationResultCode res = JSONObject_GetString(json_object, key, &strValue);

    if (res == OPERATION_SUCCESS)
    {
        *returnValue = atof(strValue);
        return OPERATION_SUCCESS;
    }
    else
    {
        return OPERATION_FAIL;
    }
}

JSONObject_OperationResultCode JSONObject_GetInt(JSONObject *json_object, const char *key, int *returnValue)
{
    char *strValue;
    JSONObject_OperationResultCode res = JSONObject_GetString(json_object, key, &strValue);

    if (res == OPERATION_SUCCESS)
    {
        *returnValue = atoi(strValue);
        return OPERATION_SUCCESS;
    }
    else
    {
        return OPERATION_FAIL;
    }
}

JSONObject_OperationResultCode JSONObject_GetLong(JSONObject *json_object, const char *key, long *returnValue)
{
    char *strValue;
    JSONObject_OperationResultCode res = JSONObject_GetString(json_object, key, &strValue);

    if (res == OPERATION_SUCCESS)
    {
        *returnValue = atol(strValue);
        return OPERATION_SUCCESS;
    }
    else
    {
        return OPERATION_FAIL;
    }
}

JSONObject_OperationResultCode JSONObject_GetBool(JSONObject *json_object, const char *key, __boolType *returnValue)
{
    char *strValue;
    JSONObject_OperationResultCode res = JSONObject_GetString(json_object, key, &strValue);

    if (res == OPERATION_SUCCESS)
    {
        if (strcmp(strValue, "true") == 0)
        {
            *returnValue = __boolTrueValue;
        }
        else if (strcmp(strValue, "false") == 0)
        {
            *returnValue = __boolFalseValue;
        }
        else
        {
            return OPERATION_FAIL;
        }

        return OPERATION_SUCCESS;
    }
    else
    {
        return OPERATION_FAIL;
    }
}
