#include "Extension.hpp"

Extension * Extension::_extension= 0;

Extension::Extension(void) : _csv_reader("./config/mine_type.csv")
{
	try
	{
		std::cout << "open" << std::endl;
		_csv_reader.open();
		_csv_reader
			.parse_categeries()
			.set_key_name("Name")
			.parse_content()
			;
		_csv_reader.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Warning: mine_type ressource is missing or incorrect" << std::endl;
	}
}

Extension::~Extension(void)
{
}

std::string
Extension::get_extension(const std::string & path)
{
	size_t posistion = path.rfind(".");

	if (posistion == std::string::npos)
		return ("");
	return (path.substr(posistion + 1));
}

std::string
Extension::get_mine_type(const std::string & ext, CsvReader & csv)
{
	std::string mine_type = csv[ext];
	if (mine_type.empty())
		mine_type = "application/octet-stream";
	return (mine_type);
}

Extension *
Extension::get_instance(void)
{
	if (_extension == 0)
		_extension = new Extension();
	return (_extension);
}

void
Extension::delete_instance(void)
{
	if (_extension != 0)
	{
		delete _extension;
		_extension = 0;
	}
}