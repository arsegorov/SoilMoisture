#ifndef __SERVER_H__
#define __SERVER_H__

const int SERVER_PORT = 8080;

void server_setup();
void listen_for_clients(float sensor_val, String local_time, String last_time_sync);

#endif
