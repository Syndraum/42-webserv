#ifndef INCLUDES_HPP
# define INCLUDES_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>

# include "response_codes.hpp"
# include "Request.hpp"
// # include "Server.hpp"

using namespace std;
class Request;

int		parse_request(istream &fd, Request *request);

#endif