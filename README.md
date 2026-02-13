# genetic-algorithm-university-classroom-scheduling-problem
The primary goal of this project is to design and implement a Genetic Algorithm (GA) to solve the University Classroom Scheduling Problem using a simplified UniTime-style formulation.

## Project Dependencies:
- Docker

## How to build (try sudo or some form of root access in front of the commands if you need it):

```bash
docker build -t ga:v0.0 .
```

## How to run:

For the first time:

```bash
docker run -it --name geneticalgo ga:v0.0
```

To run the existing container:

```bash
docker start -ia geneticalgo
```
## To clean up:

For cleaning containers:

```bash
docker container prune
```

For cleaning images:

```bash
docker image prune
```

