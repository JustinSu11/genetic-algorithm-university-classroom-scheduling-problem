FROM gcc:15-trixie
WORKDIR /home/code
COPY . .
WORKDIR /home/code/src
RUN make
CMD ["make", "run"]


