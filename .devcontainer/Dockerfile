FROM ubuntu:latest
RUN apt-get -y update && apt-get install -y
RUN apt-get -y install git
RUN apt-get -y install g++
WORKDIR /usr/src/
COPY ./ ./
CMD ["bash"]