#include "spammodule.h"

int main(){
	printf("\n\n---------------------------------\n");
	system("python /home/brolim/projetos/karmonitor/embedded_python/python/serial_connection.py");
	char * number;
//    number = getenv("KAR_NUMBER");
//    printf("no C ---> %s\n", number);
    system("echo $KAR_NUMBER");
	printf("---------------------------------\n\n");
}
