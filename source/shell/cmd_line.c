#include "cmd_line.h"
#include <stdio.h>
#include <string.h>

uint32_t led(uint8_t *cmd){
    printf("led function called with cmd: %s\n", cmd);
    return 1;
}


uint32_t test(uint8_t *cmd){
    printf("test function called with cmd: %s\n", cmd);
    return 1;
}

cmd_line_t cmd_line[] = {
    {"led", led , "led info"},
    {"test", test, "test info"},
    {NULL, NULL, NULL}
};


uint8_t parse_cmd_line(cmd_line_t* table, uint8_t *cmd){
    uint8_t chr[CMD_LINE_MAX_LEN];
    uint8_t* p_cmd = cmd;
    uint8_t cmd_idx = 0;
    uint8_t table_idx =0;
    if(table == NULL || cmd == NULL || table == (cmd_line_t*)0x00){
        return CMD_TBL_NOT_FOUND;
    }

    while(*p_cmd){
        if(*p_cmd == ' '||*p_cmd == '\n' || *p_cmd == '\t' || *p_cmd == '\r' || *p_cmd == '\0'){
            break;
        }
        else{
            chr[cmd_idx++] = *(p_cmd++);
            if(cmd_idx >= CMD_LINE_MAX_LEN){
                return CMD_TOO_LONG;
            }
        }
    }

    chr[cmd_idx] = '\0';

    while(table[table_idx].cmd != NULL){
        if(strcmp((const char*)chr, (const char*) table[table_idx].cmd)==0){
            table[table_idx].func(cmd);
            return CMD_SUCCESS;
        }
        table_idx++;
    }

    return CMD_NOT_FOUND;
}

int main(){

    uint8_t cmd[CMD_LINE_MAX_LEN] = "led on";
    parse_cmd_line(cmd_line, cmd);

    uint8_t test[CMD_LINE_MAX_LEN] = "test";
    parse_cmd_line(cmd_line, test);
}

