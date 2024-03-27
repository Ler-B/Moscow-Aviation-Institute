#include <iostream>
#include <string>
#include <zmq.h> 
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include <cstdlib>

enum Instruction{
    CREATE,
    EXEC,
    PING,
    REMOVE
};

struct Message {
    int id;
    int com;
    bool kill;
    int num[100];
    int size;
};

void Push(Message * mes, void * sock_push) {
    zmq_msg_t zmqMessage;
    assert(zmq_msg_init_size(&zmqMessage, sizeof(Message)) != -1);
    assert(memcpy(zmq_msg_data(&zmqMessage), mes, sizeof(Message)) != NULL);
    assert(zmq_msg_send(&zmqMessage, sock_push, 0) != -1);
    assert(zmq_msg_close(&zmqMessage) != -1);
}

int main() {
    int id;
    void * context_push;
    void * sock_push;
    void * context_pull;
    void * sock_pull;
    int r_push;
    int r_pull;
    bool parent = false;
	std::cout << "Starting server..." << std::endl;
    std::string message;
    while (std::cin >> message && message != "break") { 
        bool fl = false;
        if (message == "create" && !parent) {
            parent = true;
            Message m;
            m.com = CREATE;
            std::cin >> m.id;
            id = m.id;
            m.kill = false;
            context_push = zmq_ctx_new();  
            assert (context_push != NULL);
            sock_push = zmq_socket(context_push, ZMQ_PUSH);
            assert (sock_push != NULL);
            context_pull = zmq_ctx_new();
            assert (context_pull != NULL);
            sock_pull = zmq_socket(context_pull, ZMQ_PULL);
            assert (sock_pull != NULL);
            std::string port = "tcp://*:" + std::to_string(4000 + m.id);
            assert(zmq_bind(sock_push, port.c_str()) != -1);
            assert(zmq_bind(sock_pull, "tcp://*:3999") != -1);

            int id_fork = fork();
            if (id_fork == -1) {
                std::cout << "error fork" << m.id << std::endl;
                exit(EXIT_FAILURE);
            } else if (id_fork == 0) {
                execl("client", std::to_string(m.id).c_str(), NULL);
            } else {
                Push(&m, sock_push);
            }
        } else
        if (message == "create" && parent) {
            Message m;
            m.com = CREATE;
            std::cin >> m.id;
            m.kill = false;
            Push(&m, sock_push);
        } else 
        if (message == "exec") {
            Message m;
            m.com = EXEC;
            std::cin >> m.id >> m.size;
            
            m.kill = false;
            for (int i = 0; i < m.size; ++i) {
                std::cin >> m.num[i];
            }
            Push(&m, sock_push);
        } else
        if (message == "ping") {
            Message m;
            m.com = PING;
            std::cin >> m.id;
            m.kill = false;
            Push(&m, sock_push);
        } else 
        if (message == "remove") {
            Message m;
            m.com = REMOVE;
            std::cin >> m.id;
            m.kill = false;
            Push(&m, sock_push);
        } else {
            std::cout << "Incorrect command entered" << std::endl;
            fl = true;
        }
        if (!fl) {
            zmq_msg_t message_from_client;
            assert(zmq_msg_init(&message_from_client) != -1);
            assert(zmq_msg_recv(&message_from_client, sock_pull, 0) != -1);
            char * mes = (char *)zmq_msg_data(&message_from_client);
            std::cout << "Message from client: " << mes << std::endl;
            assert(zmq_msg_close(&message_from_client) != -1);
        }
    }

    Message m;
    m.kill = true;
    zmq_msg_t zmqMessage;
    assert(zmq_msg_init_size(&zmqMessage, sizeof(Message)) != -1);
    assert(memcpy(zmq_msg_data(&zmqMessage), &m, sizeof(Message)) != NULL);
    assert(zmq_msg_send(&zmqMessage, sock_push, 0) != -1);
    assert(zmq_msg_close(&zmqMessage) != -1);

    assert(zmq_close(sock_push) != -1);
    assert(zmq_ctx_destroy(context_push) != -1);
    assert(zmq_close(sock_pull) != -1);
    assert(zmq_ctx_destroy(context_pull) != -1);
    return 0;
}