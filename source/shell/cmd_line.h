#ifndef CMD_LINE_H
#define CMD_LINE_H

#include <stdint.h>

#define CMD_LINE_MAX_LEN 12
#define CMD_TBL_NOT_FOUND 0x00
#define CMD_TOO_LONG 0x01
#define CMD_NOT_FOUND 0x02
#define CMD_SUCCESS 0x03

typedef uint32_t (*p_func_t)(uint8_t *cmd);

typedef struct {
    uint8_t *cmd;
    p_func_t func;
    uint8_t * info;
} cmd_line_t;

uint8_t parse_cmd_line(cmd_line_t* table, uint8_t *cmd);


#endif