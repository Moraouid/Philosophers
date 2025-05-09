# Philosophers

A project focused on implementing the classic **Dining Philosophers Problem** using threads and mutexes, written in C.

## Table of Contents

- [About the Project](#about-the-project)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)

## About the Project

The **Dining Philosophers Problem** is a synchronization problem that illustrates the challenges of resource sharing among multiple threads. This implementation uses threads and mutexes to ensure proper synchronization and avoid deadlocks.

## Getting Started

Follow these instructions to get a copy of the project up and running on your local machine.

### Prerequisites

- A C compiler (e.g., `gcc`)
- `make` (for building the project)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Moraouid/Philosophers.git
   cd Philosophers
2. Compile the project:
   ```bash
   cd Philo
   make

## Usage
Run the program with the following command:
  ```bash
  ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

**Arguments**

**number_of_philosophers**: The number of philosophers and forks.
**time_to_die**: Time (in milliseconds) a philosopher can go without eating before dying.
**time_to_eat**: Time (in milliseconds) it takes for a philosopher to eat.
**time_to_sleep**: Time (in milliseconds) a philosopher spends sleeping.
**number_of_times_each_philosopher_must_eat** (optional): If all philosophers eat this many times, the simulation stops.

**Example**
To simulate 5 philosophers with specific timings:
```bash
  ./philo 5 800 200 200
```





  
