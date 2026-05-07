# Prepare System

Supported operating systems:

- Ubuntu 24.04 AMD64 (tested) 
- Ubuntu 22.04 AMD64 (supported)
- Ubuntu 20.04 AMD64 (supported)


Prepare/Use Docker setup as in the previous tutorials. 


## Make sure that your OS is running a X-Server

- <https://askubuntu.com/questions/1410256/how-do-i-use-the-x-window-manager-instead-of-wayland-on-ubuntu-22-04>


Open the config file
```bash
# For Ubuntu 22.04 and up
sudo nano /etc/gdm3/custom.conf
```

and change
```
WaylandEnable=true
```

to 
```
WaylandEnable=false
```

Then restart the OS.


## Pull the Docker image 

```bash
# Pull image
docker login gitlab.lrz.de:5005
docker pull gitlab.lrz.de:5005/hsa/students/docker/avr/avr:focal-vscode
docker tag gitlab.lrz.de:5005/hsa/students/docker/avr/avr:focal-vscode avr:focal-vscode
```

