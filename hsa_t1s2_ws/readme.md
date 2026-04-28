# Prepare System

Install one of the following operating systems:
- Ubuntu 24.04 AMD64 (tested)
- Ubuntu 22.04 AMD64 (supported) 
- Ubuntu 20.04 AMD64 (supported)


NOTE: 

- Docker in Windows (WSL) or Docker in MacOS will NOT work. 
- If you do not have a native Ubuntu OS you can try to use VirtualBox.
- We only support AMD64. ARM64 or other architectures (e.g. WIN ARM Surface, Apple M1, M2, M3 etc.) are NOT supported, even when running VirtualBox.


## Install and Setup Docker

1) Uninstall old versions: https://docs.docker.com/engine/install/ubuntu/#uninstall-old-versions
2) Install using the apt repository: https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository
3) Manage Docker as a non-root user: https://docs.docker.com/engine/install/linux-postinstall/#manage-docker-as-a-non-root-user



## Install and Setup VS Code

1) Install VS Code: https://code.visualstudio.com/docs/setup/linux#_debian-and-ubuntu-based-distributions
2) Install the Dev Containers Extension: https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers
    - Install `Dev Containers`


## Pull the Docker image 

```bash
# Pull image
docker pull gitlab.lrz.de:5005/hsa/students/docker/avr/avr:focal-vscode
docker tag gitlab.lrz.de:5005/hsa/students/docker/avr/avr:focal-vscode avr:focal-vscode
```

