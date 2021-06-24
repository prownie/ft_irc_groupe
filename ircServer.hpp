#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP
#include "args.hpp"
#include "user.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <vector>
#include <sstream>
#include <map>
#include "user.hpp"
#include <cstring>

#define MAX_FDS 1000
#define DATA_BUFFER 10000
#define SERVER_NAME "ft_irc.com"
class ircServer
{
private:
	ircServer();
	Args _args;
	int		create_tcp_server_socket();
	struct pollfd _pollfds[MAX_FDS];
	int	_nb_fds;
	std::map<int, User> _userList;
	//_channels map = <name,pair<user_list, password
	std::map<std::string, std::pair<std::vector<int>, std::string> > _channels;
public:
	ircServer(Args args);
	ircServer(ircServer const & src);
	ircServer & operator=(ircServer const & rhs);
	~ircServer();
	void	config();
	void	run();
	void	processRequest(std::string & request, int fd);
	int		whichCommand(std::string & request);
	int		checkPassword(User user);
	void	parseRequest(std::string request, int fd);
	void	send_to_fd(std::string code, std::string message, User const & user,
			int fd, bool dispRealName);
	void	joinMsgChat(User user, std::string channel, int fd) const;
	std::string	getNbUsers() const;
	std::string	getNbChannels() const;
	/* Command functions*/
	void 	passCommand(std::string & request, int fd);
	void 	nickCommand(std::string & request, int fd);
	void 	userCommand(std::string & request, int fd);
	void 	joinCommand(std::string & request, int fd);
	void 	operCommand(std::string & request, int fd);
	void 	quitCommand(std::string & request, int fd);
	void 	privmsgCommand(std::string & request, int fd);
	void 	lusersCommand(std::string & request, int fd);
	void 	motdCommand(std::string & request, int fd);
};
#endif

/*  /connect 127.0.0.1/8002 -password=bla    */
