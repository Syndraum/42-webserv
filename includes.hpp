#ifndef INCLUDES_HPP
# define INCLUDES_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>

# include "response_codes.hpp"
# include "Request.hpp"
// # include "Server.hpp"

# include "ASocket.hpp"

using namespace std;
class Request;

int		parse_request(Request *request, ASocket & socket);

#endif
