FROM gcc:15-trixie
WORKDIR /home/code
COPY . .
WORKDIR /home/code/src
RUN g++ -o program.exe main-ga.cpp csvparser.cpp chromosome.cpp fitness.cpp elitism.cpp tournament.cpp -lpthread
CMD ["./program.exe"]

