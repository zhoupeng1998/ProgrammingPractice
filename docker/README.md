
build with Dockerfile:

```
docker build -t <name> <path>
docker build -t zhoupeng1998/mycontainer:v1 .
```

run
    
    `docker run -itd -p <local_port>:<container_port> [-p <local_port_2>:<container_port_2>] <name>`

tag

    `docker tag <name> <username>/<tag>`

push

    `docker push <username>/<tag>`


attach to a running container

    `docker exec -it <container_id> bash`

attach to a running container, with root user

    `docker exec -it -u root <container_id> bash`