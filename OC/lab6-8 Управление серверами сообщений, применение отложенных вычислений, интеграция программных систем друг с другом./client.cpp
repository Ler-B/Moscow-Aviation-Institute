#include <iostream>
#include <string>
#include <zmq.h> 
#include <unistd.h>
#include <assert.h>
#include <cstdlib>
#include <sys/types.h>

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

void Error(std::string str, void * sock_push) {
    std::string mes_to_server = "Error: " + str + "\0";
    zmq_msg_t zmqMessage;
    assert(zmq_msg_init_size(&zmqMessage, sizeof(char) * mes_to_server.size() + 1) != -1);
    assert(memcpy(zmq_msg_data(&zmqMessage), mes_to_server.c_str() , sizeof(char) * mes_to_server.size() + 1) != NULL);
    assert(zmq_msg_send(&zmqMessage, sock_push, 0) != -1);
    assert(zmq_msg_close(&zmqMessage) != -1);
}
void Ok(int id, void * sock_push) {
    std::string mes_to_server = "Ok: " + std::to_string(id) + "\0";
    zmq_msg_t zmqMessage;
    assert(zmq_msg_init_size(&zmqMessage, sizeof(char) * mes_to_server.size() + 1) != -1);
    assert(memcpy(zmq_msg_data(&zmqMessage), mes_to_server.c_str() , sizeof(char) * mes_to_server.size() + 1) != NULL);
    assert(zmq_msg_send(&zmqMessage, sock_push, 0) != -1);
    assert(zmq_msg_close(&zmqMessage) != -1);
}
void Ok(int id, int rez, void * sock_push) {
    std::string mes_to_server = "Ok: " + std::to_string(id) + " : " + std::to_string(rez) + "\0";
    zmq_msg_t zmqMessage;
    assert(zmq_msg_init_size(&zmqMessage, sizeof(char) * mes_to_server.size() + 1) != -1);
    assert(memcpy(zmq_msg_data(&zmqMessage), mes_to_server.c_str() , sizeof(char) * mes_to_server.size() + 1) != NULL);
    assert(zmq_msg_send(&zmqMessage, sock_push, 0) != -1);
    assert(zmq_msg_close(&zmqMessage) != -1);
}
void Ok(void * sock_push) {
    std::string mes_to_server = "Ok\0";
    zmq_msg_t zmqMessage;
    assert(zmq_msg_init_size(&zmqMessage, sizeof(char) * mes_to_server.size() + 1) != -1);
    assert(memcpy(zmq_msg_data(&zmqMessage), mes_to_server.c_str() , sizeof(char) * mes_to_server.size() + 1) != NULL);
    assert(zmq_msg_send(&zmqMessage, sock_push, 0) != -1);
    assert(zmq_msg_close(&zmqMessage) != -1);
}
void Push(Message * mes, void * sock_push) {
    zmq_msg_t zmqMessage;
    assert(zmq_msg_init_size(&zmqMessage, sizeof(Message)) != -1);
    assert(memcpy(zmq_msg_data(&zmqMessage), mes, sizeof(Message)) != NULL);
    assert(zmq_msg_send(&zmqMessage, sock_push, 0) != -1);
    assert(zmq_msg_close(&zmqMessage) != -1);
}

int main(int argc, char * argv[]) {
    int id;
    bool par = false;
    bool left = false;
    bool right = false;
    int id_left;
    int id_right;
    if (argc < 1) {
        std::cout << "ERROR";
        return 1;
    } else {
        id = atoi(argv[0]);
    }
    void * context_pull = zmq_ctx_new();
    assert (context_pull != NULL);
    void * sock_pull = zmq_socket(context_pull, ZMQ_PULL);
    assert (sock_pull != NULL);
    std::string port = "tcp://127.0.0.1:" + std::to_string(4000 + id);
    assert(zmq_connect(sock_pull, port.c_str()) != -1);
    void * context_push = zmq_ctx_new();
    assert (context_push != NULL);
    void * sock_push = zmq_socket(context_push, ZMQ_PUSH);
    assert (sock_push != NULL);
    assert(zmq_connect(sock_push, "tcp://127.0.0.1:3999") != -1);

    void * context_push_right;
    void * sock_push_right;

    void * context_push_left;
    void * sock_push_left;

    while(!false) {
        zmq_msg_t message;
        assert(zmq_msg_init(&message) != -1);
        assert(zmq_msg_recv(&message, sock_pull, 0) != -1);
        Message * mes = (Message *)zmq_msg_data(&message);
        assert(zmq_msg_close(&message) != -1);
        if (mes->kill) {
            if (left) {
                Push(mes, sock_push_left);
                assert(zmq_close(sock_push_left) != -1);
                assert(zmq_ctx_destroy(context_push_left) != -1);
            }
            if (right) {
                Push(mes, sock_push_right);
                assert(zmq_close(sock_push_right) != -1);
                assert(zmq_ctx_destroy(context_push_right) != -1); 
            }     
            break;
        }
        if (mes->id == id) {
            if (mes->com == CREATE) {
                if (par) {
                    Error("Already exists", sock_push);
                } else {
                    par = true;
                    Ok(getpid(), sock_push);
                }
            } else
            if (mes->com == EXEC) {
                int rez = 0;
                for (int i = 0; i < mes->size; ++i) {
                    rez += mes->num[i];
                }
                Ok(getpid(), rez, sock_push);
            } else 
            if (mes->com == PING) {
                Ok(getpid(), sock_push);
            } else
            if (mes->com == REMOVE) {
                std::cout << "eror remove" << std::endl;
            }
        } else if (mes->id > id) {
            if (mes->com == CREATE && !right) {
                right = true;
                id_right = mes->id;
                assert((context_push_right = zmq_ctx_new()) != NULL);
                assert((sock_push_right = zmq_socket(context_push_right, ZMQ_PUSH)) != NULL);
                std::string port_right = "tcp://*:" + std::to_string(4000 + id_right);  
                assert(zmq_bind(sock_push_right, port_right.c_str()) != -1);
                int id_fork = fork();
                if (id_fork == -1) {
                    std::cout << "error fork" << id << std::endl;
                    exit(EXIT_FAILURE);
                } else if (id_fork == 0) {
                    execl("client", std::to_string(id_right).c_str(), NULL);
                } else {
                    Push(mes, sock_push_right);
                }
            } else 
            if (mes->com == EXEC && !right) {
                Error("Not found", sock_push);
            } else 
            if (mes->com == PING && !right) {
                Error("Not found", sock_push);
            } else 
            if (mes->com == REMOVE) {
                if (!right) {
                    Error("Not found", sock_push);
                } else {
                    if (id_right == mes->id) {
                        mes->kill = true;
                        right = false;
                        Push(mes, sock_push_right);
                        assert(zmq_close(sock_push_right) != -1);
                        assert(zmq_ctx_destroy(context_push_right) != -1);
                        Ok(sock_push);
                    } else {
                        Push(mes, sock_push_right);
                    }
                }
            } else {
                Push(mes, sock_push_right);
            }
        } else {
            if (mes->com == CREATE && !left) {
                left = true;
                id_left = mes->id;
                assert((context_push_left = zmq_ctx_new()) != NULL);
                assert((sock_push_left = zmq_socket(context_push_left, ZMQ_PUSH)) != NULL);
                std::string port_left = "tcp://*:" + std::to_string(4000 + id_left);  
                assert(zmq_bind(sock_push_left, port_left.c_str()) != -1);
                int id_fork = fork();
                if (id_fork == -1) {
                    std::cout << "error fork" << id << std::endl;
                    exit(EXIT_FAILURE);
                } else if (id_fork == 0) {
                    execl("client", std::to_string(id_left).c_str(), NULL);
                } else {
                   Push(mes, sock_push_left);
                }
            } else 
            if (mes->com == EXEC && !left) {
                Error("Not found", sock_push);
            } else 
            if (mes->com == PING && !left) {
                Error("Not found", sock_push);
            } else 
            if (mes->com == REMOVE) {
                if (!left) {
                    Error("Not found", sock_push);
                } else {
                    if (id_left == mes->id) {
                        mes->kill = true;
                        right = false;
                        Push(mes, sock_push_left);
                        assert(zmq_close(sock_push_left) != -1);
                        assert(zmq_ctx_destroy(context_push_left) != -1);
                        Ok(sock_push);
                    } else {
                        Push(mes, sock_push_right);
                    }
                }
            } else {
                Push(mes, sock_push_left);
            }
        }
    }
    assert(zmq_close(sock_push) != -1);
    assert(zmq_ctx_destroy(context_push) != -1);
    assert(zmq_close(sock_pull) != -1);
    assert(zmq_ctx_destroy(context_pull) != -1);
    return 0;
}