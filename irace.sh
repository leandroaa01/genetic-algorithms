#!/bin/bash

sudo apt update && sudo apt install --no-install-recommends software-properties-common dirmngr -y
wget -qO- https://cloud.r-project.org/bin/linux/ubuntu/marutter_pubkey.asc | sudo gpg --dearmor -o /usr/share/keyrings/r-project.gpg
echo "deb [signed-by=/usr/share/keyrings/r-project.gpg] https://cloud.r-project.org/bin/linux/ubuntu noble-cran40/" | sudo tee /etc/apt/sources.list.d/r-project.list
sudo apt update
sudo apt install r-base r-base-dev -y
sudo apt install libuv1-dev -y

