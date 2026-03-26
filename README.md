*This project has been created as part of the 42 curriculum by aadeikal.*

## Description

This project is a C implementation of the **Dining Philosophers** problem, a classic synchronization
challenge in computer science. The goal is to model a table of philosophers whose only actions are to
think, eat, and sleep, without any of them starving.

The simulation involves:
-   A number of philosophers sitting around a circular table.
-   A large bowl of spaghetti that they share.
-   A number of forks equal to the number of philosophers.
-   To eat, a philosopher must acquire two forks : the one on their left and the one on their right.
-   When a philosopher finishes eating, they release the forks and proceed to sleep. Upon waking, they begin to think.

The simulation ends when a philosopher dies from starvation or when an optional meal count is reached
by all philosophers. This project uses POSIX threads (`pthreads`) to represent each philosopher and
mutexes to protect the forks from being used by more than one philosopher at a time. The primary
challenge is to implement a deadlock-free and data-race-free solution where no philosopher ever
starves.

## Instructions

### Compilation

To compile the program, navigate to the project directory and run the `make` command:

```bash
make
```

This will generate the `philo` executable.

### Execution

Run the program from your shell with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Argument Details:**

-   `number_of_philosophers`: The total number of philosophers and forks.
-   `time_to_die` (in milliseconds): The time a philosopher can go without eating. If they do not
start a meal within this duration, they die.
-   `time_to_eat` (in milliseconds): The duration a philosopher spends eating.
-   `time_to_sleep` (in milliseconds): The duration a philosopher spends sleeping.
-   `[number_of_times_each_philosopher_must_eat]` (optional): If provided, the simulation will stop
once every philosopher has eaten at least this many times.

**Examples:**

```bash
# A simulation with 5 philosophers
./philo 5 800 200 200

# A simulation with 4 philosophers that stops after each has eaten 7 times
./philo 4 410 200 200 7
```

### Cleaning Up

To remove all compiled object files and the final executable, run:

```bash
make fclean
```

## Resources

### Project-related Topics

-   [**Wikipedia: Dining Philosophers Problem**](https://en.wikipedia.org/wiki/Dining_philosophers_problem): A detailed overview of the problem, its history, and common solutions.
-   [**GeeksforGeeks: Dining Philosopher’s Problem Using Semaphores**](https://www.geeksforgeeks.org/dining-philosophers-problem-using-semaphores/): An article explaining a common approach to solving the problem.
-   [**POSIX Threads Programming**](https://hpc-tutorials.llnl.gov/posix/): A tutorial from Lawrence Livermore National Laboratory on using pthreads.
