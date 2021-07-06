/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:58:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/02 15:50:10 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"
#include "BuilderCore.hpp"
#include "Reader.hpp"
// #include "CsvReader.hpp"
// #include "Extension.hpp"

int		main(int argc, char *argv[])
{
	std::string path_config_file = "default.conf";
	
	// Extension * ext = Extension::get_intance();
	// std::cout << "TEST : " << ext->get_reader()["html"] << std::endl;

	if (argc > 2)
	{
		std::cerr << "Error: too much arguemnt" <<std::endl;
		return (2);
	}
	if (argc == 2)
		path_config_file = argv[1];
	
	Reader reader(path_config_file);
	try
	{
		reader.open();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: Configuration file: " << path_config_file << " not found" << std::endl;
		return (1);
	}
	Core core = Core();
	try
	{
		BuilderCore builder_core(reader.get_ifs(), &core);
		builder_core.parse_mine_type();
		builder_core.print_debug();
	}
	catch(const std::exception& e)
	{
		// std::cerr << e.what() << '\n';
		return (3);
	}
	
	core.start();
}
