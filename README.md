# Philosophers

The dining philosophers problem - A solution using mutexes and threads in C language.

## 📋 About The Project

Philosophers is a solution to the classic "Dining Philosophers Problem". This project aims to solve concurrency problems such as race conditions and deadlocks using threads and mutexes.

## 🎯 Problem Definition

N philosophers sit around a table. Each philosopher has a plate of spaghetti and a fork on each side. Philosophers think and eat. To eat, they need two forks. The challenge:

- Philosophers must not die from starvation
- No deadlock should occur
- No data races should happen
- Each philosopher should eat enough

## 🛠️ Technologies Used

- **C Language** (98.3%)
- **Makefile** (1.7%)
- POSIX Threads (pthread)
- Mutex (mutual exclusion)

## 📦 Installation

### Compilation

```bash
make        # Compile the program
make clean  # Clean object files
make fclean # Clean all compilation outputs
make re     # Recompile
```

## 💻 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters:

1. **number_of_philosophers**: Number of philosophers (also number of forks)
2. **time_to_die**: Time in milliseconds before a philosopher dies from starvation
3. **time_to_eat**: Time in milliseconds it takes for a philosopher to eat
4. **time_to_sleep**: Time in milliseconds a philosopher spends sleeping
5. **[number_of_times_each_philosopher_must_eat]**: (Optional) Minimum times each philosopher must eat

### Examples:

```bash
# 5 philosophers, 800ms die, 200ms eat, 200ms sleep
./philo 5 800 200 200

# 4 philosophers, 410ms die, 200ms eat, 200ms sleep, each must eat 5 times
./philo 4 410 200 200 5

# No deaths should occur
./philo 4 310 200 100
```

## 🔍 Program Output

The program generates logs in the following format:

```
[timestamp_in_ms] [philosopher_id] has taken a fork
[timestamp_in_ms] [philosopher_id] is eating
[timestamp_in_ms] [philosopher_id] is sleeping
[timestamp_in_ms] [philosopher_id] is thinking
[timestamp_in_ms] [philosopher_id] died
```

## 🧠 Solution Approach

### Thread Management
- Each philosopher runs as a separate thread
- Main thread monitors all philosophers
- Continuous death checking

### Mutex Usage
- Each fork is protected by a mutex
- Separate mutex for print operations
- Critical sections protected to prevent data races

### Deadlock Prevention
- Acquiring forks in a specific order
- Special handling for single philosopher case
- Timeout mechanism

## 📚 Key Concepts

### Thread
- Independent units running in parallel
- `pthread_create()`, `pthread_join()` functions

### Mutex (Mutual Exclusion)
- Controls access to shared resources
- `pthread_mutex_lock()`, `pthread_mutex_unlock()`

### Race Condition
- Two or more threads accessing the same resource
- Solved with mutexes

### Deadlock
- Threads waiting for each other
- Prevented with careful design

## ⚠️ Important Notes

- All mallocs must be checked
- No memory leaks
- No data races
- Death must be detected within 10ms
- No global variables (except for bonus)

## 🔍 42 Norm

This project complies with 42 school's **Norm** standards:
- Maximum 25 lines per function
- Maximum 80 characters per line
- Maximum 4 parameters per function

## 📝 Test Scenarios

```bash
# No deaths should occur
./philo 5 800 200 200
./philo 4 410 200 200

# One philosopher should die
./philo 4 310 200 100

# No deaths + each must eat 7 times
./philo 4 410 200 200 7

# Single philosopher - should die
./philo 1 800 200 200
```

## 👤 Developer

**TroubledKezoo1**

Project Link: [https://github.com/TroubledKezoo1/Philosophers](https://github.com/TroubledKezoo1/Philosophers)

## 📖 Resources

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [42 School - Philosophers](https://harm-smits.github.io/42docs/projects/philosophers)

---

*42 School - Philosophers Project*