# Building the Docker image from source

```
cd /tmp
wget https://raw.githubusercontent.com/dti-research/frankr/master/docker/Dockerfile
docker build -t dtiresearch/frankr -f Dockerfile .
```

Be adwised that building MoveIt from source takes a while and that there will be a lot of CMake deprecation warnings.
