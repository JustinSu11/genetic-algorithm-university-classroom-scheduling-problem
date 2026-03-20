FROM gcc:15-trixie
WORKDIR /home/code
COPY . .
WORKDIR /home/code/src
RUN g++ -o program.exe main-ga.cpp csvparser.cpp readcsv.cpp chromosome.cpp fitness.cpp -lpthread
CMD ["./program.exe"]

