FROM gcc:15-trixie
WORKDIR /home/code
COPY . .
RUN g++ -o program.exe main-ga.cpp
CMD ["./program.exe"]

