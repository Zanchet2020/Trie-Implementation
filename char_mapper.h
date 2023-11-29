#ifndef CHAR_MAPPER_H_
#define CHAR_MAPPER_H_

#define NUMBER_OF_CHARACTERS 62

unsigned int map_char(char chr){
    if(chr >= '0' && chr <= '9'){
        return chr - '0';
    } else if(chr >= 'A' && chr <= 'Z'){
        return (chr - 'A') + map_char('9') + 1;
    } else if(chr >= 'a' && chr <= 'z'){
        return (chr - 'a') + map_char('Z') + 1;
    }
}

#endif