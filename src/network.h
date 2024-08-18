#pragma once

#include "pch.h"
#include "Player.h"

namespace network {
	const unsigned short CLIENT_PORT = 64000;
	const unsigned short SERVER_PORT = 64111;

	enum msg_type {
		CLOSE_CONN	= 0x1,
		INIT_CONN	= 0x2,
		
		TRNS_DATA	= 0x3,
	};

	struct packet {
		char msg_type;
		sf::Vector2f pos;
	};

	struct client_data {
		sf::IpAddress		ip;
		sf::Vector2f		pos;
		Player			*player;
		unsigned int		time;
	};

	class Client {
	private:
		sf::UdpSocket		listener;
		sf::UdpSocket		socket;
		sf::IpAddress		serverIp;

		// Inits
		void			initListener();
		void			initConnection();

		// Funcs
		void			actionDispatcher(void *data);
	public:
		Client(sf::IpAddress serverIp);
		virtual ~Client();

		// Core
		void			listen();
		void			send(sf::Vector2f pos);
	};

	class Server {
	private:
		sf::UdpSocket				listener;
		std::vector<client_data>		clients;

		// Inits
		void					initListener();

		// Funcs
		void					actionDispatcher(void *data, sf::IpAddress ip);
	public:
		Server();
		virtual ~Server();

		// Accessors
		std::vector<client_data>		getClients();

		// Core
		void					listen();
	};
};
