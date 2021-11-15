#!/bin/bash

sudo apt update
sudo apt install -y php-cgi
PHP_CONFIG_FILE=$(php --ini | grep "Loaded Configuration File" | rev | cut -d" " -f1 | rev | sed s/"cli"/"cgi"/g)
sudo sed -i -e s/";cgi.force_redirect = 1"/"cgi.force_redirect = 0"/g $PHP_CONFIG_FILE
