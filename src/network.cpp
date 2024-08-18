#include "network.h"

using namespace network;

Client::Client(sf::IpAddress serverIp) {
	this->serverIp = serverIp;

	this->initListener();
	this->initConnection();
}

Client::~Client() {
	this->listener.unbind();
}

// Inits
void Client::initListener() {
	if (this->listener.bind(CLIENT_PORT) != sf::Socket::Done) {
		std::cerr << "CLIENT::INITLISTENER" << std::endl;
		exit(1);
	}
	this->listener.setBlocking(false);
	std::cout << "Client started at PORT " << CLIENT_PORT << "!" << std::endl;
}

void Client::initConnection() {
	packet pkt;
	pkt.msg_type = INIT_CONN;

	if (this->socket.send(&pkt, sizeof(pkt), this->serverIp, SERVER_PORT) != sf::Socket::Done) {
		std::cerr << "Failed to init connection to server <<" << this->serverIp << ">>!" << std::endl;
	}
}

// Funcs
void Client::actionDispatcher(void *data) {
}

// Core
void Client::listen() {
	char data[sizeof(packet)];
	std::size_t recv;
	sf::IpAddress ip;
	unsigned short port;
	if (this->listener.receive(data, sizeof(packet), recv, ip, port) == sf::Socket::Done && ip == this->serverIp) {
		this->actionDispatcher(data);
	}
}

void Client::send(sf::Vector2f pos) {
	packet pkt;
	pkt.msg_type = TRNS_DATA;
	pkt.pos = pos;

	this->socket.send(&pkt, sizeof(pkt), this->serverIp, SERVER_PORT);
}

Server::Server() {
	this->initListener();
}

Server::~Server() {
	this->listener.unbind();
}

// Inits
void Server::initListener() {
	if (this->listener.bind(SERVER_PORT) != sf::Socket::Done) {
		std::cerr << "SERVER::INITLISTENER" << std::endl;
		exit(1);
	}
	this->listener.setBlocking(false);
	std::cout << "Server started at PORT " << SERVER_PORT << "!" << std::endl;
}

// Funcs
void Server::actionDispatcher(void *data, sf::IpAddress ip) {
	packet *pkt = (packet *) data;
	switch (pkt->msg_type) {
		case CLOSE_CONN:
			for (int i = 0; i < this->clients.size(); i++) {
				if (this->clients[i].ip == ip) {
					this->clients.erase(this->clients.begin() + i);
					std::cout << "Host <" << ip << "> disconnected!" << std::endl;
				}
			}
			break;
		case INIT_CONN:
			std::cout << "Init connection from <" << ip << ">!" << std::endl;
			if (this->clients.size() < 3) {
				for (auto it: this->clients) {
					if (it.ip == ip) {
						break;
					}
				}
				client_data cd;
				cd.ip = ip;
				cd.time = time(NULL);
				this->clients.push_back(cd);
				std::cout << "Successfully connected <" << ip << ">!" << std::endl;
			}
			break;
		case TRNS_DATA:
			for (auto it: this->clients) {
				if (it.ip == ip) {
					packet *pkt = (packet *) data;
					it.pos = pkt->pos;
				}
			}
			break;
		default:
			break;
	}
}

// Accessors
std::vector<client_data> Server::getClients() {
	return this->clients;
}

// Core
void Server::listen() {
	char data[sizeof(packet)];
	std::size_t recv;
	sf::IpAddress ip;
	unsigned short port;
	if (this->listener.receive(data, sizeof(packet), recv, ip, port) == sf::Socket::Done) {
		this->actionDispatcher(data, ip);
	}
}
