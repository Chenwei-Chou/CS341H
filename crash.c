#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	system("sudo pkill -x clientd");
	system("sudo pkill -x client");
	system("sudo systemctl stop httpd.service");
	return 0;
}
