#include "base.h"
#include "usr_mgmt.h"

int main(int argc, char *argv[])
{
    int srv_fd, cli_fd;
    char cli_pipe_name[20];
    login_t cli_log;
    cli_info_t cli_data;

    mkfifo(SRV_FIFO , 0600);
    srv_fd = open(SRV_FIFO, O_RDWR);

    do {
        read(srv_fd, &cli_data, sizeof(cli_data));
        read(srv_fd, &cli_log, sizeof(cli_log));
        printf("%s-%s", cli_log.usr, cli_log.pss );

        sprintf(cli_pipe_name , CLI_FIFO, cli_data.pid );
        cli_fd = open(cli_pipe_name, O_WRONLY|O_CREAT, 0600);

        cli_log.auth = usr_auth(cli_log.usr, cli_log.pss);
        printf("%s\n", cli_log.auth ? "[LOGIN SUCCESFULL]" : "[LOGIN FAILED]");
        write(cli_fd, &cli_log.auth, sizeof(cli_log.auth));
    } while( !cli_log.auth  );

    close(cli_fd);
    close(srv_fd);
    unlink(cli_pipe_name);
    exit(0);
}
